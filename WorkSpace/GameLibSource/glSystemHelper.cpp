
#include "../GameLibInclude/glSystemHelper.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glStruct.h"
#include "../GameLibInclude/glDefine.h"
#include "../GameLibInclude/glGlobalData.h"

typedef BOOL(WINAPI * glVerifyVersionInfoW)(
	LPOSVERSIONINFOEXW lpVersionInformation,
	DWORD dwTypeMask,
	DWORDLONG dwlConditionMask);
typedef ULONGLONG(NTAPI * glVerSetConditionMask)(
	ULONGLONG ConditionMask,
	ULONG TypeMask,
	UCHAR Condition);
typedef BOOL(WINAPI * glGetVersionExW)(
	LPOSVERSIONINFOW lpVersionInformation);
typedef BOOL(WINAPI * glIsWow64Process)(
	HANDLE hProcess,
	PBOOL Wow64Process);

namespace {
	static glVerifyVersionInfoW gVerifyVersionInfoW = 0;
	static glVerSetConditionMask gVerSetConditionMask = 0;
	static glGetVersionExW gGetVersionExW = 0;
	static glIsWow64Process gIsWow64Process = 0;

	//
	// @brief 判断当前操作系统的主版本号、副版本号以及 Service Pack 主版本号是否大于或等于指定值
	// @desc
	//
	// 需要注意的是，该函数是判断是否大于或等于，而不是判断是否等于
	// 对于低版本的操作系统，传递高版本的版本号参数给该函数时，该函数总是返回真
	// 所以，用户在调用该函数的时候，应该先从最高版本的操作系统版本号开始判断
	// 比方说，Windows XP 的版本号是 5.1，Windows Vista 的版本号是 6.0，而 Windows 7 的版本号是 6.1
	// 那么，在 Windows 7 操作系统下，下述调用都将返回真：
	//
	// glIsWinVerOrGreater(5, 1, 0) // 当前操作系统是 Win7，版本号大于等于 5.1，返回真
	// glIsWinVerOrGreater(6, 0, 0) // 当前操作系统是 Win7，版本号大于等于 6.0，返回真
	// glIsWinVerOrGreater(6, 1, 0) // 当前操作系统是 Win7，版本号大于等于 6.1，返回真
	//
	static int glIsWinVerOrGreater(
		const short int verMajor,
		const short int verMinor,
		const short int servicePackMajor,
		bool & result) {
		OSVERSIONINFOEXW osVerInfo = { 0 };
		DWORDLONG conditionMask = 0;
		if (!gModule_Kernel32.isAlready()) {
			gModule_Kernel32.createW(L"kernel32.dll");
		}
		if (gModule_Kernel32.isAlready()) {
			if (!gVerifyVersionInfoW) {
				gVerifyVersionInfoW = (glVerifyVersionInfoW)
					gModule_Kernel32.getProcAddressA("VerifyVersionInfoW");
			}
			if (!gVerSetConditionMask) {
				gVerSetConditionMask = (glVerSetConditionMask)
					gModule_Kernel32.getProcAddressA("VerSetConditionMask");
			}
		}
		if (gVerifyVersionInfoW && gVerSetConditionMask) {
			osVerInfo.dwOSVersionInfoSize = sizeof(osVerInfo);
			osVerInfo.dwMajorVersion = verMajor;
			osVerInfo.dwMinorVersion = verMinor;
			osVerInfo.wServicePackMajor = servicePackMajor;
			conditionMask = gVerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL);
			conditionMask = gVerSetConditionMask(conditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);
			conditionMask = gVerSetConditionMask(conditionMask, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
			result = gVerifyVersionInfoW(
				&osVerInfo,
				VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR,
				conditionMask) ? true : false;
			return true;
		}
		return false;
	}
}

bool glSystemHelper::getCurrentUserNameW(glStringW & userName) {
	wchar_t userNameTemp[520] = { 0 };
	DWORD userNameTempSize = GL_DIM(userNameTemp);
	if (GetUserNameW(userNameTemp, &userNameTempSize)) {
		userName = userNameTemp;
		return true;
	}
	else {
		throw glWin32APIException(L"GetUserNameW", GetLastError());
	}
	return false;
}

bool glSystemHelper::getSystemDirectoryW(glStringW & systemDir) {
	wchar_t systemDirTemp[520] = { 0 };
	if (GetSystemDirectoryW(systemDirTemp, GL_DIM(systemDirTemp))) {
		systemDir = systemDirTemp;
		return true;
	}
	else {
		throw glWin32APIException(L"GetSystemDirectoryW", GetLastError());
	}
	return false;
}

bool glSystemHelper::getWindowDirectoryW(glStringW & windowDir) {
	wchar_t windowDirTemp[520] = { 0 };
	if (GetWindowsDirectoryW(windowDirTemp, GL_DIM(windowDirTemp))) {
		windowDir = windowDirTemp;
		return true;
	}
	else {
		throw glWin32APIException(L"GetWindowsDirectoryW", GetLastError());
	}
	return false;
}

bool glSystemHelper::getComputerNameW(glStringW & computerName) {
	wchar_t computerNameTemp[520] = { 0 };
	DWORD computerNameTempSize = GL_DIM(computerNameTemp);
	if (GetComputerNameW(computerNameTemp, &computerNameTempSize)) {
		computerName = computerNameTemp;
		return true;
	}
	else {
		throw glWin32APIException(L"GetComputerNameW", GetLastError());
	}
	return false;
}

bool glSystemHelper::getMemoryInfo(glMemoryInfo & memoryInfo) {
	MEMORYSTATUSEX memStatusEx = { 0 };
	memStatusEx.dwLength = sizeof(memStatusEx);
	if (GlobalMemoryStatusEx(&memStatusEx)) {
		memoryInfo.mPhysTotal = memStatusEx.ullTotalPhys;
		memoryInfo.mPhysAvail = memStatusEx.ullAvailPhys;
		memoryInfo.mVirtualTotal = memStatusEx.ullTotalVirtual;
		memoryInfo.mVirtualAvail = memStatusEx.ullAvailVirtual;
		return true;
	}
	else {
		throw glWin32APIException(L"GlobalMemoryStatusEx", GetLastError());
	}
	return false;
}

bool glSystemHelper::getOSVersion(int & osVer) {
	bool ret = false;
	bool result = false;
	OSVERSIONINFOEXW osVerInfo = { 0 };

#define WINVERORGREATER(_Ver1, _ServicePack, _Ver2) \
	if (glIsWinVerOrGreater(HIBYTE(_Ver1), LOBYTE(_Ver1), _ServicePack, result) && result) \
	{ \
	osVer = _Ver2; \
	ret = true; \
	break; \
	}

	do {
		WINVERORGREATER(0x0A00, 0, GL_OSVER_WIN10);
		WINVERORGREATER(_WIN32_WINNT_WINBLUE, 0, GL_OSVER_WIN81);
		WINVERORGREATER(_WIN32_WINNT_WIN8, 0, GL_OSVER_WIN8);
		WINVERORGREATER(_WIN32_WINNT_WIN7, 1, GL_OSVER_WIN7_SP1);
		WINVERORGREATER(_WIN32_WINNT_WIN7, 0, GL_OSVER_WIN7);
		WINVERORGREATER(_WIN32_WINNT_VISTA, 2, GL_OSVER_WINVISTA_SP2);
		WINVERORGREATER(_WIN32_WINNT_VISTA, 1, GL_OSVER_WINVISTA_SP1);
		WINVERORGREATER(_WIN32_WINNT_VISTA, 0, GL_OSVER_WINVISTA);
		WINVERORGREATER(_WIN32_WINNT_WINXP, 2, GL_OSVER_WINXP_SP2);
		WINVERORGREATER(_WIN32_WINNT_WINXP, 1, GL_OSVER_WINXP_SP1);
		WINVERORGREATER(_WIN32_WINNT_WINXP, 0, GL_OSVER_WINXP);
		WINVERORGREATER(_WIN32_WINNT_WIN2K, 0, GL_OSVER_WIN2K);
	} while (0);

	if (!ret) {
		if (!gModule_Kernel32.isAlready()) {
			gModule_Kernel32.createW(L"kernel32.dll");
		}
		if (gModule_Kernel32.isAlready()) {
			if (!gGetVersionExW) {
				gGetVersionExW = (glGetVersionExW)gModule_Kernel32.getProcAddressA("GetVersionExW");
			}
		}
		if (gGetVersionExW) {
			osVerInfo.dwOSVersionInfoSize = sizeof(osVerInfo);
			if (gGetVersionExW((OSVERSIONINFOW *)&osVerInfo)) {
				if (6 == osVerInfo.dwMajorVersion && 1 == osVerInfo.dwMinorVersion) {
					if (1 == osVerInfo.wServicePackMajor) {
						osVer = GL_OSVER_WIN7_SP1;
					}
					else {
						osVer = GL_OSVER_WIN7;
					}
				}
				else if (6 == osVerInfo.dwMajorVersion && 0 == osVerInfo.dwMinorVersion) {
					if (2 == osVerInfo.wServicePackMajor) {
						osVer = GL_OSVER_WINVISTA_SP2;
					}
					else if (1 == osVerInfo.wServicePackMajor) {
						osVer = GL_OSVER_WINVISTA_SP1;
					}
					else {
						osVer = GL_OSVER_WINVISTA;
					}
				}
				else if (5 == osVerInfo.dwMajorVersion && 1 == osVerInfo.dwMinorVersion) {
					if (2 == osVerInfo.wServicePackMajor) {
						osVer = GL_OSVER_WINXP_SP2;
					}
					else if (1 == osVerInfo.wServicePackMajor) {
						osVer = GL_OSVER_WINXP_SP1;
					}
					else {
						osVer = GL_OSVER_WINXP;
					}
				}
				else if (5 == osVerInfo.dwMajorVersion && 0 == osVerInfo.dwMinorVersion) {
					osVer = GL_OSVER_WIN2K;
				}
				ret = true;
			}
		}
	}

#undef WINVERORGREATER

	return ret;
}
