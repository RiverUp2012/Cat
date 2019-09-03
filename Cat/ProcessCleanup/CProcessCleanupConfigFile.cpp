
#include "stdafx.h"
#include "CProcessCleanupConfigFile.h"

// 最多可以清理多少个进程
#define MAX_PROCESS_EXE_FILE_NAME (64)
//
#define CONFIG_APP_GLOBAL (L"Global")
#define CONFIG_KEY_PROCESS_COUNT (L"ProcessCount")
#define CONFIG_KEY_PROCESS_FMT (L"Process%d")

namespace
{
	// 用于存放需要清理的进程 exe 文件名的数组
	static T_OBJECT gProcessExeFileNameArray = 0;
	// 用于枚举进程 exe 文件数组
	static int gCurrentProcessExeFileNameForEnum = 0;
}

void CProcessCleanupConfigFile::loadW(
	const wchar_t * configFileName)
{
	wchar_t key[64] = { 0 };
	wchar_t processExeFileName[520] = { 0 };
	int processCount = 0;
	int index = 0;

	if (gProcessExeFileNameArray)
	{
		TArrayFreeAllData(gProcessExeFileNameArray, T_TRUE);
	}

	if (!gProcessExeFileNameArray)
	{
		gProcessExeFileNameArray = TArrayCreate(MAX_PROCESS_EXE_FILE_NAME);
	}

	if (gProcessExeFileNameArray && configFileName)
	{
		processCount = GetPrivateProfileIntW(
			CONFIG_APP_GLOBAL,
			CONFIG_KEY_PROCESS_COUNT,
			0,
			configFileName);
		for (int i = 0; i < processCount; ++i)
		{
			swprintf_s(key, CONFIG_KEY_PROCESS_FMT, i);

			if (GetPrivateProfileStringW(
				CONFIG_APP_GLOBAL,
				key,
				0,
				processExeFileName,
				_countof(processExeFileName),
				configFileName))
			{
				index = TArrayFindEmpty(gProcessExeFileNameArray, T_TRUE);
				if (-1 != index)
				{
					TArraySetAt(
						gProcessExeFileNameArray,
						index,
						TStringDuplicateW(processExeFileName));
				}
			}
		}
	}
}

void CProcessCleanupConfigFile::saveW(
	const wchar_t * configFileName)
{
	wchar_t key[64] = { 0 };
	wchar_t value[64] = { 0 };
	int processCount = 0;

	if (gProcessExeFileNameArray && configFileName)
	{
		TFileSystemDeleteFileW(configFileName);

		for (int i = 0; i < TArrayGetCapacity(gProcessExeFileNameArray); ++i)
		{
			const wchar_t * processExeFileName = (const wchar_t *)TArrayGetAt(
				gProcessExeFileNameArray,
				i);
			if (processExeFileName)
			{
				swprintf_s(key, CONFIG_KEY_PROCESS_FMT, processCount);
				WritePrivateProfileStringW(
					CONFIG_APP_GLOBAL,
					key,
					processExeFileName,
					configFileName);
				++processCount;
			}
		}

		swprintf_s(value, L"%d", processCount);
		WritePrivateProfileStringW(
			CONFIG_APP_GLOBAL,
			CONFIG_KEY_PROCESS_COUNT,
			value,
			configFileName);
	}
}

bool CProcessCleanupConfigFile::firstProcessExeFileNameW(
	wchar_t * processExeFileName,
	const int processExeFileNameSize)
{
	if (gProcessExeFileNameArray &&
		processExeFileName &&
		processExeFileNameSize > 0)
	{
		gCurrentProcessExeFileNameForEnum = 0;

		while (gCurrentProcessExeFileNameForEnum < TArrayGetCapacity(gProcessExeFileNameArray))
		{
			const wchar_t * processExeFileNameTemp = (const wchar_t *)TArrayGetAt(
				gProcessExeFileNameArray,
				gCurrentProcessExeFileNameForEnum);
			if (processExeFileNameTemp)
			{
				TStringCopyW(
					processExeFileName,
					processExeFileNameTemp,
					0);

				return true;
			}

			++gCurrentProcessExeFileNameForEnum;
		}
	}

	return false;
}

bool CProcessCleanupConfigFile::nextProcessExeFileNameW(
	wchar_t * processExeFileName,
	const int processExeFileNameSize)
{
	if (gProcessExeFileNameArray &&
		processExeFileName &&
		processExeFileNameSize > 0)
	{
		++gCurrentProcessExeFileNameForEnum;

		while (gCurrentProcessExeFileNameForEnum < TArrayGetCapacity(gProcessExeFileNameArray))
		{
			const wchar_t * processExeFileNameTemp = (const wchar_t *)TArrayGetAt(
				gProcessExeFileNameArray,
				gCurrentProcessExeFileNameForEnum);
			if (processExeFileNameTemp)
			{
				TStringCopyW(
					processExeFileName,
					processExeFileNameTemp,
					0);

				return true;
			}

			++gCurrentProcessExeFileNameForEnum;
		}
	}

	return false;
}

bool CProcessCleanupConfigFile::addProcessExeFileNameW(
	const wchar_t * processExeFileName)
{
	int index = 0;

	if (!gProcessExeFileNameArray)
	{
		gProcessExeFileNameArray = TArrayCreate(MAX_PROCESS_EXE_FILE_NAME);
	}

	if (processExeFileName)
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
					return true;
				}
			}
		}
	}

	return false;
}

bool CProcessCleanupConfigFile::removeProcessExeFileNameW(
	const wchar_t * processExeFileName)
{
	if (processExeFileName && gProcessExeFileNameArray)
	{
		for (int i = 0; i < TArrayGetCapacity(gProcessExeFileNameArray); ++i)
		{
			wchar_t * processExeFileNameTemp = (wchar_t *)TArrayGetAt(
				gProcessExeFileNameArray,
				i);
			if (processExeFileNameTemp &&
				0 == _wcsicmp(processExeFileName, processExeFileNameTemp))
			{
				TFree(processExeFileNameTemp);
				processExeFileNameTemp = 0;

				TArraySetAt(gProcessExeFileNameArray, i, 0);

				return true;
			}
		}
	}

	return false;
}

void CProcessCleanupConfigFile::removeAllProcessExeFileName(void)
{
	if (gProcessExeFileNameArray)
	{
		TArrayFreeAllData(gProcessExeFileNameArray, T_TRUE);
	}
}
