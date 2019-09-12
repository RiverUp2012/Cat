
#include "stdafx.h"
#include "CProcessCleanupConfigFile.h"

#define CONFIG_APP_GLOBAL (L"Global")
#define CONFIG_KEY_PROCESS_COUNT (L"ProcessCount")
#define CONFIG_KEY_PROCESS_FMT (L"Process%d")

namespace {
	// 用于存放需要清理的进程 exe 文件名的数组
	static std::vector<std::wstring> gProcessExeFileNameArray;
}

void CProcessCleanupConfigFile::loadW(
	const wchar_t * configFileName) {
	wchar_t key[64] = { 0 };
	wchar_t processExeFileName[520] = { 0 };
	int processCount = 0;
	int index = 0;
	gProcessExeFileNameArray.clear();
	if (configFileName) {
		processCount = GetPrivateProfileIntW(
			CONFIG_APP_GLOBAL,
			CONFIG_KEY_PROCESS_COUNT,
			0,
			configFileName);
		for (int i = 0; i < processCount; ++i) {
			swprintf_s(key, CONFIG_KEY_PROCESS_FMT, i);
			if (GetPrivateProfileStringW(
				CONFIG_APP_GLOBAL,
				key,
				0,
				processExeFileName,
				_countof(processExeFileName),
				configFileName)) {
				gProcessExeFileNameArray.push_back(processExeFileName);
			}
		}
	}
}

void CProcessCleanupConfigFile::saveW(
	const wchar_t * configFileName) {
	wchar_t key[64] = { 0 };
	wchar_t value[64] = { 0 };
	int processCount = 0;
	if (configFileName) {
		wl::FileHelper::deleteFileW(configFileName);
		for (const auto & processExeFileName : gProcessExeFileNameArray) {
			swprintf_s(key, CONFIG_KEY_PROCESS_FMT, processCount);
			WritePrivateProfileStringW(
				CONFIG_APP_GLOBAL,
				key,
				processExeFileName.c_str(),
				configFileName);
			++processCount;
		}
		swprintf_s(value, L"%d", processCount);
		WritePrivateProfileStringW(
			CONFIG_APP_GLOBAL,
			CONFIG_KEY_PROCESS_COUNT,
			value,
			configFileName);
	}
}

const std::vector<std::wstring> & CProcessCleanupConfigFile::getProcessExeFileNameList(void) {
	return gProcessExeFileNameArray;
}

bool CProcessCleanupConfigFile::addProcessExeFileNameW(
	const wchar_t * processExeFileName) {
	if (processExeFileName) {
		gProcessExeFileNameArray.push_back(processExeFileName);
		return true;
	}
	return false;
}

bool CProcessCleanupConfigFile::removeProcessExeFileNameW(
	const wchar_t * processExeFileName) {
	if (processExeFileName) {
		for (auto iter = gProcessExeFileNameArray.begin(); iter != gProcessExeFileNameArray.end(); ++iter) {
			const auto & processExeFileNameTemp = *iter;
			if (0 == _wcsicmp(processExeFileName, processExeFileNameTemp.c_str())) {
				gProcessExeFileNameArray.erase(iter);
				return true;
			}
		}
	}
	return false;
}

void CProcessCleanupConfigFile::removeAllProcessExeFileName(void) {
	gProcessExeFileNameArray.clear();
}
