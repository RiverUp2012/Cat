
#include "stdafx.h"
#include "CProcessCleanup.h"

// 最多可以清理多少个进程
#define MAX_PROCESS_EXE_FILE_NAME (64)
// 默认每隔多少毫秒清理一次进程（30 秒清理一次）
#define DEFAULT_CLEANUP_TIME_INTERVAL (1000 * 30)

namespace
{
	// 进程清理线程对象
	static T_OBJECT gThread = 0;
	// 用于存放需要清理的进程 exe 文件名的数组
	static T_OBJECT gProcessExeFileNameArray = 0;
	// 线程资源同步锁
	static T_OBJECT gMutex = 0;
	// 每隔多少毫秒清理一次进程
	static int gCleanupTimeInterval = DEFAULT_CLEANUP_TIME_INTERVAL;

	//
	// 进程枚举回调函数
	//
	// processId 进程 id
	// userData 用户数据
	//
	int processCallbackProc(
		const unsigned int processId,
		void * userData)
	{
		wchar_t processImageName[520] = { 0 };
		wchar_t processExeFileName[520] = { 0 };

		// 获取枚举出来的进程的完整 exe 文件名
		// 比方说：C:\\Windows\\notepad.exe

		if (gProcessExeFileNameArray &&
			TProcessQueryImageNameByProcessIdW(
			processId,
			processImageName,
			_countof(processImageName)))
		{
			OutputDebugStringW(processImageName);
			OutputDebugStringW(L"\r\n");

			// 从完整 exe 文件名中提取出 exe 文件名
			// 比方说：notepad.exe

			if (TPathExtractFileNameWithExtW(
				processImageName,
				processExeFileName,
				_countof(processExeFileName)))
			{
				// 看看是不是需要清理的进程

				for (int i = 0; i < TArrayGetCapacity(gProcessExeFileNameArray); ++i)
				{
					const wchar_t * processExeFileNameTemp = (const wchar_t *)TArrayGetAt(gProcessExeFileNameArray, i);
					if (processExeFileNameTemp &&
						0 == _wcsicmp(processExeFileName, processExeFileNameTemp))
					{
						// 如果是，杀掉该进程

						TProcessTerminate(processId);
					}
				}
			}
		}

		return T_TRUE;
	}

	//
	// 进程清理线程
	//
	static void processCleanupThread(
		T_OBJECT thread,
		void * userData)
	{
		while (true)
		{
			TMutexLock(gMutex);
			{
				// 枚举系统中当前的所有进程

				TProcessEnum(processCallbackProc, 0);
			}
			TMutexUnlock(gMutex);

			TThreadCurrentSleep(gCleanupTimeInterval);
		}
	}
}

void CProcessCleanup::startup(
	const int cleanupTimeInterval)
{
	if (!gMutex)
	{
		gMutex = TMutexCreate();
	}

	gCleanupTimeInterval = cleanupTimeInterval;
	if (gCleanupTimeInterval <= 0)
	{
		gCleanupTimeInterval = DEFAULT_CLEANUP_TIME_INTERVAL;
	}

	if (!gThread)
	{
		gThread = TThreadCreateW(processCleanupThread, 0, T_TRUE, 0);
	}
}

void CProcessCleanup::shutdown(void)
{
	if (gThread)
	{
		//TThreadWait(gThread, -1);
		TThreadKill(gThread);
		gThread = 0;
	}

	if (gProcessExeFileNameArray)
	{
		TArrayFreeAllData(gProcessExeFileNameArray, T_TRUE);
		TArrayDestroy(gProcessExeFileNameArray, 0, 0);
		gProcessExeFileNameArray = 0;
	}

	if (gMutex)
	{
		TMutexDestroy(gMutex);
		gMutex = 0;
	}
}

bool CProcessCleanup::addProcessExeFileNameW(
	const wchar_t * processExeFileName)
{
	bool ret = false;
	int index = 0;

	if (processExeFileName)
	{
		TMutexLock(gMutex);
		{
			if (!gProcessExeFileNameArray)
			{
				gProcessExeFileNameArray = TArrayCreate(MAX_PROCESS_EXE_FILE_NAME);
			}

			if (gProcessExeFileNameArray)
			{
				index = TArrayFindEmpty(gProcessExeFileNameArray, T_TRUE);
				if (index >= 0)
				{
					if (TArraySetAt(gProcessExeFileNameArray, index, TStringDuplicateW(processExeFileName)))
					{
						ret = true;
					}
				}
			}
		}
		TMutexUnlock(gMutex);
	}

	return ret;
}

void CProcessCleanup::removeAllProcessExeFileName(void)
{
	TMutexLock(gMutex);
	{
		if (gProcessExeFileNameArray)
		{
			TArrayFreeAllData(gProcessExeFileNameArray, T_TRUE);
		}
	}
	TMutexUnlock(gMutex);
}
