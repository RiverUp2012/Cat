
#include "../Include/WinLib.h"

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

namespace wl {

	static TQueryFullProcessImageNameW gQueryFullProcessImageNameW = 0;
	static TGetModuleFileNameExW gGetModuleFileNameExW = 0;
	static Module gModuleKernel32;
	static Module gModulePsapi;

	Process::Process() {

	}

	Process::~Process() {
		close();
	}

	bool Process::openByProcessID(const DWORD processID, const int features) {
		DWORD desiredAccess = 0;
		if (!mProcessHandle) {
			if (features & PROCESS_FEATURE_TERMINATE) desiredAccess |= PROCESS_TERMINATE;
			if (features & PROCESS_FEATURE_QUERY_INFO) desiredAccess |= PROCESS_QUERY_INFORMATION;
			mProcessHandle = OpenProcess(desiredAccess, FALSE, processID);
			if (mProcessHandle) {
				return true;
			}
		}
		return false;
	}

	void Process::close(void) {
		if (mProcessHandle) {
			CloseHandle(mProcessHandle);
			mProcessHandle = 0;
		}
	}

	bool Process::terminate(void) {
		bool ret = false;
		if (mProcessHandle) {
			if (TerminateProcess(mProcessHandle, 0)) {
				mProcessHandle = 0;
				ret = true;
			}
		}
		return ret;
	}

	bool Process::getImageFileNameW(std::wstring & imageFileName) {
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
					mProcessHandle,
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
					mProcessHandle,
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

} // namespace wl
