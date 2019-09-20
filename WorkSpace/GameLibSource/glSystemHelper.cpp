
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
	// @brief �жϵ�ǰ����ϵͳ�����汾�š����汾���Լ� Service Pack ���汾���Ƿ���ڻ����ָ��ֵ
	// @desc
	//
	// ��Ҫע����ǣ��ú������ж��Ƿ���ڻ���ڣ��������ж��Ƿ����
	// ���ڵͰ汾�Ĳ���ϵͳ�����ݸ߰汾�İ汾�Ų������ú���ʱ���ú������Ƿ�����
	// ���ԣ��û��ڵ��øú�����ʱ��Ӧ���ȴ���߰汾�Ĳ���ϵͳ�汾�ſ�ʼ�ж�
	// �ȷ�˵��Windows XP �İ汾���� 5.1��Windows Vista �İ汾���� 6.0���� Windows 7 �İ汾���� 6.1
	// ��ô���� Windows 7 ����ϵͳ�£��������ö��������棺
	//
	// glIsWinVerOrGreater(5, 1, 0) // ��ǰ����ϵͳ�� Win7���汾�Ŵ��ڵ��� 5.1��������
	// glIsWinVerOrGreater(6, 0, 0) // ��ǰ����ϵͳ�� Win7���汾�Ŵ��ڵ��� 6.0��������
	// glIsWinVerOrGreater(6, 1, 0) // ��ǰ����ϵͳ�� Win7���汾�Ŵ��ڵ��� 6.1��������
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
