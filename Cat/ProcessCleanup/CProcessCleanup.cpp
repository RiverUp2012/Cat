
#include "stdafx.h"
#include "CProcessCleanup.h"

// ������������ٸ�����
#define MAX_PROCESS_EXE_FILE_NAME (64)
// Ĭ��ÿ�����ٺ�������һ�ν��̣�30 ������һ�Σ�
#define DEFAULT_CLEANUP_TIME_INTERVAL (1000 * 30)

namespace
{
	// ���������̶߳���
	static T_OBJECT gThread = 0;
	// ���ڴ����Ҫ����Ľ��� exe �ļ���������
	static T_OBJECT gProcessExeFileNameArray = 0;
	// �߳���Դͬ����
	static T_OBJECT gMutex = 0;
	// ÿ�����ٺ�������һ�ν���
	static int gCleanupTimeInterval = DEFAULT_CLEANUP_TIME_INTERVAL;

	//
	// ����ö�ٻص�����
	//
	// processId ���� id
	// userData �û�����
	//
	int processCallbackProc(
		const unsigned int processId,
		void * userData)
	{
		wchar_t processImageName[520] = { 0 };
		wchar_t processExeFileName[520] = { 0 };

		// ��ȡö�ٳ����Ľ��̵����� exe �ļ���
		// �ȷ�˵��C:\\Windows\\notepad.exe

		if (gProcessExeFileNameArray &&
			TProcessQueryImageNameByProcessIdW(
			processId,
			processImageName,
			_countof(processImageName)))
		{
			OutputDebugStringW(processImageName);
			OutputDebugStringW(L"\r\n");

			// ������ exe �ļ�������ȡ�� exe �ļ���
			// �ȷ�˵��notepad.exe

			if (TPathExtractFileNameWithExtW(
				processImageName,
				processExeFileName,
				_countof(processExeFileName)))
			{
				// �����ǲ�����Ҫ����Ľ���

				for (int i = 0; i < TArrayGetCapacity(gProcessExeFileNameArray); ++i)
				{
					const wchar_t * processExeFileNameTemp = (const wchar_t *)TArrayGetAt(gProcessExeFileNameArray, i);
					if (processExeFileNameTemp &&
						0 == _wcsicmp(processExeFileName, processExeFileNameTemp))
					{
						// ����ǣ�ɱ���ý���

						TProcessTerminate(processId);
					}
				}
			}
		}

		return T_TRUE;
	}

	//
	// ���������߳�
	//
	static void processCleanupThread(
		T_OBJECT thread,
		void * userData)
	{
		while (true)
		{
			TMutexLock(gMutex);
			{
				// ö��ϵͳ�е�ǰ�����н���

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
