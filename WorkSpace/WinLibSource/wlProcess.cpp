
#include "../WinLib.h"

typedef BOOL(WINAPI * TQueryFullProcessImageNameW)(
	HANDLE hProcess,
	DWORD dwFlags,
	LPWSTR lpExeName,
	PDWORD lpdwSize);
typedef DWORD(WINAPI * TGetModuleFileNameExW)(
	HANDLE hProcess,
	HMODULE hModule,
	LPWSTR lpFilename,
	DWORD nSize);

static TQueryFullProcessImageNameW gQueryFullProcessImageNameW = 0;
static TGetModuleFileNameExW gGetModuleFileNameExW = 0;
static wlModule gModuleKernel32;
static wlModule gModulePsapi;

wlProcess::wlProcess() {
	mProcessHandle = 0;
}

wlProcess::~wlProcess() {
	close();
}

bool wlProcess::openByProcessID(const DWORD processID, const int features) {
	DWORD desiredAccess = 0;
	if (!mProcessHandle) {
		if (features & WL_PROCESS_FEATURE_TERMINATE) desiredAccess |= PROCESS_TERMINATE;
		if (features & WL_PROCESS_FEATURE_QUERY_INFO) desiredAccess |= PROCESS_QUERY_INFORMATION;
		mProcessHandle = (void *)OpenProcess(desiredAccess, FALSE, processID);
		if (mProcessHandle) {
			return true;
		}
	}
	return false;
}

void wlProcess::close(void) {
	if (mProcessHandle) {
		CloseHandle((HANDLE)mProcessHandle);
		mProcessHandle = 0;
	}
}

bool wlProcess::terminate(void) {
	bool ret = false;
	if (mProcessHandle) {
		if (TerminateProcess((HANDLE)mProcessHandle, 0)) {
			mProcessHandle = 0;
			ret = true;
		}
	}
	return ret;
}

bool wlProcess::getImageFileNameW(sgeStringW & imageFileName) {
	wchar_t imageFileNameTemp[520] = { 0 };
	DWORD imageFileNameSize = _countof(imageFileNameTemp);
	if (mProcessHandle) {
		if (!gModuleKernel32.isAlready()) {
			if (gModuleKernel32.loadW(L"kernel32.dll")) {
				gQueryFullProcessImageNameW = (TQueryFullProcessImageNameW)
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
		}
		if (!gModulePsapi.isAlready()) {
			if (gModulePsapi.loadW(L"psapi.dll")) {
				gGetModuleFileNameExW = (TGetModuleFileNameExW)
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
		}
	}
	return false;
}
