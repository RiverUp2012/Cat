
#include "../WinLib.h"
#include "../Include/WinLibPrivate.h"
#include "../Include/GameLibPrivate.h"

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

static wlQueryFullProcessImageNameW gQueryFullProcessImageNameW = 0;
static wlGetModuleFileNameExW gGetModuleFileNameExW = 0;

wlProcess::wlProcess() {
	mProcessHandle = 0;
	mProcessID = 0;
}

wlProcess::~wlProcess() {
	close();
}

bool wlProcess::openByProcessID(const unsigned long processID, const int features) {
	DWORD desiredAccess = 0;
	if (!mProcessHandle) {
		if (features & WL_PROCESS_FEATURE_TERMINATE) desiredAccess |= PROCESS_TERMINATE;
		if (features & WL_PROCESS_FEATURE_QUERY_INFO) desiredAccess |= PROCESS_QUERY_INFORMATION;
		if (features & WL_PROCESS_FEATURE_VM_OPERATION) desiredAccess |= (PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE);
		mProcessHandle = (void *)OpenProcess(desiredAccess, FALSE, processID);
		if (mProcessHandle) {
			mProcessID = processID;
			return true;
		}
		else {
			throw glException(L"OpenProcess", GetLastError());
		}
	}
	return false;
}

void wlProcess::close(void) {
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
			throw glException(L"TerminateProcess", GetLastError());
		}
	}
	return ret;
}

bool wlProcess::getImageFileNameW(glStringW & imageFileName) {
	wchar_t imageFileNameTemp[520] = { 0 };
	DWORD imageFileNameSize = _countof(imageFileNameTemp);
	if (mProcessHandle) {
		if (!gModuleKernel32.isAlready()) {
			if (gModuleKernel32.createW(L"kernel32.dll")) {
				gQueryFullProcessImageNameW = (wlQueryFullProcessImageNameW)
					gModuleKernel32.getProcAddressA("QueryFullProcessImageNameW");
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
				throw glException(L"QueryFullProcessImageNameW", GetLastError());
			}
		}
		if (!gModulePsapi.isAlready()) {
			if (gModulePsapi.createW(L"psapi.dll")) {
				gGetModuleFileNameExW = (wlGetModuleFileNameExW)
					gModulePsapi.getProcAddressA("GetModuleFileNameExW");
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
				throw glException(L"GetModuleFileNameExW", GetLastError());
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
			throw glException(L"ReadProcessMemory", GetLastError());
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
			throw glException(L"WriteProcessMemory", GetLastError());
		}
	}
	return false;
}

bool wlProcess::setPrivilegeW(const wchar_t * privilegeName, const bool enableOrDisable) {
	bool ret = false;
	HANDLE tokenHandle = 0;
	TOKEN_PRIVILEGES tokenPrivileges = { 0 };
	if (mProcessHandle) {
		if (OpenProcessToken(
			(HANDLE)mProcessHandle,
			TOKEN_ADJUST_PRIVILEGES,
			&tokenHandle)) {
			tokenPrivileges.PrivilegeCount = 1;
			if (LookupPrivilegeValueW(
				0,
				SE_DEBUG_NAME,
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
					throw glException(L"AdjustTokenPrivileges", GetLastError());
				}
			}
			else {
				throw glException(L"LookupPrivilegeValueW", GetLastError());
			}
			CloseHandle(tokenHandle);
			tokenHandle = 0;
		}
		else {
			throw glException(L"OpenProcessToken", GetLastError());
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
