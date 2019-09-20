
#include "../WinLibInclude/wlProcess.h"
#include "../WinLibInclude/wlPrivate.h"
#include "../WinLibInclude/wlEnum.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glGlobalData.h"
#include "../GameLibInclude/glDefine.h"

typedef BOOL(WINAPI * wlQueryFullProcessImageNameW)(
	HANDLE hProcess,
	DWORD dwFlags,
	LPWSTR lpExeName,
	PDWORD lpdwSize);
typedef DWORD(WINAPI * wlGetModuleFileNameExW)(
	HANDLE hProcess,
	HMODULE hModule,
	LPWSTR lpFilename,
	DWORD nSize);

namespace {
	static wlQueryFullProcessImageNameW gQueryFullProcessImageNameW = 0;
	static wlGetModuleFileNameExW gGetModuleFileNameExW = 0;
}

wlProcess::wlProcess() {
	mProcessHandle = 0;
	mProcessID = 0;
}

wlProcess::~wlProcess() {
	destroy();
}

bool wlProcess::createByProcessID(const unsigned long processID, const int features) {
	DWORD desiredAccess = 0;
	if (!mProcessHandle) {
		if (features & WL_PROCESS_FEATURE_TERMINATE) {
			desiredAccess |= PROCESS_TERMINATE;
		}
		if (features & WL_PROCESS_FEATURE_QUERY_INFO) {
			desiredAccess |= PROCESS_QUERY_INFORMATION;
		}
		if (features & WL_PROCESS_FEATURE_VM_OPERATION) {
			desiredAccess |= (PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE);
		}
		mProcessHandle = (void *)OpenProcess(desiredAccess, FALSE, processID);
		if (mProcessHandle) {
			mProcessID = processID;
			return true;
		}
		else {
			throw glWin32APIException(L"OpenProcess", GetLastError());
		}
	}
	return false;
}

void wlProcess::destroy(void) {
	if (mProcessHandle) {
		CloseHandle((HANDLE)mProcessHandle);
		mProcessHandle = 0;
	}
	mProcessID = 0;
}

bool wlProcess::terminate(void) {
	bool ret = false;
	if (mProcessHandle) {
		if (TerminateProcess((HANDLE)mProcessHandle, 0)) {
			mProcessHandle = 0;
			ret = true;
		}
		else {
			throw glWin32APIException(L"TerminateProcess", GetLastError());
		}
	}
	return ret;
}

bool wlProcess::getImageFileNameW(glStringW & imageFileName) {
	wchar_t imageFileNameTemp[520] = { 0 };
	DWORD imageFileNameSize = _countof(imageFileNameTemp);
	if (mProcessHandle) {
		if (!gModule_Kernel32.isAlready()) {
			if (gModule_Kernel32.createW(L"kernel32.dll")) {
				gQueryFullProcessImageNameW = (wlQueryFullProcessImageNameW)
					gModule_Kernel32.getProcAddressA("QueryFullProcessImageNameW");
			}
		}
		if (gQueryFullProcessImageNameW) {
			if (gQueryFullProcessImageNameW(
				(HANDLE)mProcessHandle,
				0,
				imageFileNameTemp,
				&imageFileNameSize)) {
				imageFileName = imageFileNameTemp;
				return true;
			}
			else {
				throw glWin32APIException(L"QueryFullProcessImageNameW", GetLastError());
			}
		}
		if (!gModule_Psapi.isAlready()) {
			if (gModule_Psapi.createW(L"psapi.dll")) {
				gGetModuleFileNameExW = (wlGetModuleFileNameExW)
					gModule_Psapi.getProcAddressA("GetModuleFileNameExW");
			}
		}
		if (gGetModuleFileNameExW) {
			if (gGetModuleFileNameExW(
				(HANDLE)mProcessHandle,
				0,
				imageFileNameTemp,
				imageFileNameSize)) {
				imageFileName = imageFileNameTemp;
				return true;
			}
			else {
				throw glWin32APIException(L"GetModuleFileNameExW", GetLastError());
			}
		}
	}
	return false;
}

bool wlProcess::vmRead(const void * vmAddress, void * buffer, const int bytesToRead) {
	SIZE_T bytesReaded = 0;
	if (mProcessHandle && vmAddress && buffer && bytesToRead > 0) {
		if (ReadProcessMemory(
			(HANDLE)mProcessHandle,
			vmAddress,
			buffer,
			bytesToRead,
			&bytesReaded)) {
			return true;
		}
		else {
			throw glWin32APIException(L"ReadProcessMemory", GetLastError());
		}
	}
	return false;
}

bool wlProcess::vmWrite(void * vmAddress, const void * buffer, const int bytesToWrite) {
	SIZE_T bytesWrited = 0;
	if (mProcessHandle && vmAddress && buffer && bytesToWrite > 0) {
		if (WriteProcessMemory(
			(HANDLE)mProcessHandle,
			vmAddress,
			buffer,
			bytesToWrite,
			&bytesWrited)) {
			return true;
		}
		else {
			throw glWin32APIException(L"WriteProcessMemory", GetLastError());
		}
	}
	return false;
}

bool wlProcess::setPrivilegeW(const wchar_t * privilegeName, const bool enableOrDisable) {
	bool ret = false;
	HANDLE tokenHandle = 0;
	TOKEN_PRIVILEGES tokenPrivileges = { 0 };
	glStringW seDebugNameW;
	if (mProcessHandle) {
		if (OpenProcessToken(
			(HANDLE)mProcessHandle,
			TOKEN_ADJUST_PRIVILEGES,
			&tokenHandle)) {
			tokenPrivileges.PrivilegeCount = 1;
			GL_T2W(SE_DEBUG_NAME, seDebugNameW, ret);
			if (ret) {
				if (LookupPrivilegeValueW(
					0,
					seDebugNameW,
					&tokenPrivileges.Privileges[0].Luid)) {
					tokenPrivileges.Privileges[0].Attributes = enableOrDisable ? SE_PRIVILEGE_ENABLED : SE_PRIVILEGE_REMOVED;
					if (AdjustTokenPrivileges(
						tokenHandle,
						FALSE,
						&tokenPrivileges,
						sizeof(tokenPrivileges),
						0,
						0)) {
						ret = true;
					}
					else {
						throw glWin32APIException(L"AdjustTokenPrivileges", GetLastError());
					}
				}
				else {
					throw glWin32APIException(L"LookupPrivilegeValueW", GetLastError());
				}
			}
			CloseHandle(tokenHandle);
			tokenHandle = 0;
		}
		else {
			throw glWin32APIException(L"OpenProcessToken", GetLastError());
		}
	}
	return ret;
}

void * wlProcess::getProcessHandle(void) const {
	return mProcessHandle;
}

unsigned long wlProcess::getProcesseID(void) const {
	return mProcessID;
}
