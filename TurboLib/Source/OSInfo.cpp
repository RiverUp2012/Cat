
#include "../TurboLib.h"
#include "../Include/Private.h"

typedef BOOL (WINAPI * TVerifyVersionInfoW)(
	LPOSVERSIONINFOEXW lpVersionInformation,
	DWORD dwTypeMask,
	DWORDLONG dwlConditionMask);
typedef ULONGLONG (NTAPI * TVerSetConditionMask)(
	ULONGLONG ConditionMask,
	ULONG TypeMask,
	UCHAR Condition);
typedef BOOL (WINAPI * TGetVersionExW)(
	LPOSVERSIONINFOW lpVersionInformation);
typedef BOOL(WINAPI * TIsWow64Process)(
	HANDLE hProcess,
	PBOOL Wow64Process);

static T_OBJECT gModuleKernel32 = 0;
static TVerifyVersionInfoW gVerifyVersionInfoW = 0;
static TVerSetConditionMask gVerSetConditionMask = 0;
static TGetVersionExW gGetVersionExW = 0;
static TIsWow64Process gIsWow64Process = 0;

//
// 判断当前操作系统的主版本号、副版本号以及 Service Pack 主版本号是否大于或等于指定值
//
// 需要注意的是，该函数是判断是否大于或等于，而不是判断是否等于
// 对于低版本的操作系统，传递高版本的版本号参数给该函数时，该函数总是返回真
// 所以，用户在调用该函数的时候，应该先从最高版本的操作系统版本号开始判断
// 比方说，Windows XP 的版本号是 5.1，Windows Vista 的版本号是 6.0，而 Windows 7 的版本号是 6.1
// 那么，在 Windows 7 操作系统下，下述调用都将返回真：
//
// TIsWinVerOrGreater(5, 1, 0) // 当前操作系统是 Win7，版本号大于等于 5.1，返回真
// TIsWinVerOrGreater(6, 0, 0) // 当前操作系统是 Win7，版本号大于等于 6.0，返回真
// TIsWinVerOrGreater(6, 1, 0) // 当前操作系统是 Win7，版本号大于等于 6.1，返回真
//
static int TIsWinVerOrGreater(
	const short int verMajor,
	const short int verMinor,
	const short int servicePackMajor,
	int * result)
{
	OSVERSIONINFOEXW osVerInfo = { 0 };
	DWORDLONG conditionMask = 0;

	if (!gModuleKernel32)
	{
		gModuleKernel32 = TModuleLoadW(L"kernel32.dll");
	}

	if (gModuleKernel32)
	{
		if (!gVerifyVersionInfoW)
		{
			gVerifyVersionInfoW = (TVerifyVersionInfoW)TModuleGetProcAddress(
				gModuleKernel32,
				L"VerifyVersionInfoW");
		}

		if (!gVerSetConditionMask)
		{
			gVerSetConditionMask = (TVerSetConditionMask)TModuleGetProcAddress(
				gModuleKernel32,
				L"VerSetConditionMask");
		}
	}

	if (gVerifyVersionInfoW && gVerSetConditionMask && result)
	{
		osVerInfo.dwOSVersionInfoSize = sizeof(osVerInfo);
		osVerInfo.dwMajorVersion = verMajor;
		osVerInfo.dwMinorVersion = verMinor;
		osVerInfo.wServicePackMajor = servicePackMajor;

		conditionMask = gVerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL);
		conditionMask = gVerSetConditionMask(conditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);
		conditionMask = gVerSetConditionMask(conditionMask, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

		*result = gVerifyVersionInfoW(
			&osVerInfo,
			VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR,
			conditionMask) ? T_TRUE : T_FALSE;

		return T_TRUE;
	}

	return T_FALSE;
}

int TOSInfoQueryVersion(
	int * osVer)
{
	int ret = T_FALSE;
	int result = T_FALSE;
	OSVERSIONINFOEXW osVerInfo = { 0 };

#define WINVERORGREATER(_Ver1, _ServicePack, _Ver2) \
	if (TIsWinVerOrGreater(HIBYTE(_Ver1), LOBYTE(_Ver1), _ServicePack, &result) && result) \
	{ \
	*osVer = _Ver2; \
	ret = T_TRUE; \
	break; \
	}

	if (osVer)
	{
		do
		{
			WINVERORGREATER(0x0A00, 0, T_OSVER_WIN10);
			WINVERORGREATER(_WIN32_WINNT_WINBLUE, 0, T_OSVER_WIN81);
			WINVERORGREATER(_WIN32_WINNT_WIN8, 0, T_OSVER_WIN8);
			WINVERORGREATER(_WIN32_WINNT_WIN7, 1, T_OSVER_WIN7SP1);
			WINVERORGREATER(_WIN32_WINNT_WIN7, 0, T_OSVER_WIN7);
			WINVERORGREATER(_WIN32_WINNT_VISTA, 2, T_OSVER_WINVISTASP2);
			WINVERORGREATER(_WIN32_WINNT_VISTA, 1, T_OSVER_WINVISTASP1);
			WINVERORGREATER(_WIN32_WINNT_VISTA, 0, T_OSVER_WINVISTA);
			WINVERORGREATER(_WIN32_WINNT_WINXP, 0, T_OSVER_WINXP);
			WINVERORGREATER(_WIN32_WINNT_WIN2K, 0, T_OSVER_WIN2K);
		} while (0);

		if (!ret)
		{
			if (!gModuleKernel32)
			{
				gModuleKernel32 = TModuleLoadW(L"kernel32.dll");
			}

			if (gModuleKernel32)
			{
				gGetVersionExW = (TGetVersionExW)TModuleGetProcAddress(
					gModuleKernel32,
					L"GetVersionExW");
			}

			if (gGetVersionExW)
			{
				osVerInfo.dwOSVersionInfoSize = sizeof(osVerInfo);

				if (gGetVersionExW((OSVERSIONINFOW *)&osVerInfo))
				{
					if (6 == osVerInfo.dwMajorVersion && 1 == osVerInfo.dwMinorVersion)
					{
						if (1 == osVerInfo.wServicePackMajor)
						{
							*osVer = T_OSVER_WIN7SP1;
						}
						else
						{
							*osVer = T_OSVER_WIN7;
						}
					}
					else if (6 == osVerInfo.dwMajorVersion && 0 == osVerInfo.dwMinorVersion)
					{
						if (2 == osVerInfo.wServicePackMajor)
						{
							*osVer = T_OSVER_WINVISTASP2;
						}
						else if (1 == osVerInfo.wServicePackMajor)
						{
							*osVer = T_OSVER_WINVISTASP1;
						}
						else
						{
							*osVer = T_OSVER_WINVISTA;
						}
					}
					else if (5 == osVerInfo.dwMajorVersion && 1 == osVerInfo.dwMinorVersion)
					{
						if (2 == osVerInfo.wServicePackMajor)
						{
							*osVer = T_OSVER_WINXPSP2;
						}
						else if (1 == osVerInfo.wServicePackMajor)
						{
							*osVer = T_OSVER_WINXPSP1;
						}
						else
						{
							*osVer = T_OSVER_WINXP;
						}
					}
					else if (5 == osVerInfo.dwMajorVersion && 0 == osVerInfo.dwMinorVersion)
					{
						*osVer = T_OSVER_WIN2K;
					}

					ret = T_TRUE;
				}
			}
		}
	}

#undef WINVERORGREATER

	return ret;
}

int TOSInfoOSVersionToStringW(
	const int osVer,
	wchar_t * string,
	const int stringSize)
{
#define VER2STR(_Ver, _String) \
	if (_Ver == osVer && _String) \
	{ \
	TStringCopyW(string, _String, 0); \
	return T_TRUE; \
	}

	if (string && stringSize > 0)
	{
		VER2STR(T_OSVER_WIN2K, L"Windows 2000");
		VER2STR(T_OSVER_WINXP, L"Windows XP");
		VER2STR(T_OSVER_WINXPSP1, L"Windows XP SP1");
		VER2STR(T_OSVER_WINXPSP2, L"Windows XP SP2");
		VER2STR(T_OSVER_WINVISTA, L"Windows Vista");
		VER2STR(T_OSVER_WINVISTASP1, L"Windows Vista SP1");
		VER2STR(T_OSVER_WINVISTASP2, L"Windows Vista SP2");
		VER2STR(T_OSVER_WIN7, L"Windows 7");
		VER2STR(T_OSVER_WIN7SP1, L"Windows 7 SP1");
		VER2STR(T_OSVER_WIN8, L"Windows 8");
		VER2STR(T_OSVER_WIN81, L"Windows 8.1");
		VER2STR(T_OSVER_WIN10, L"Windows 10");
	}

#undef VER2STR

	return T_FALSE;
}

int TOSInfoOSVersionToStringA(
	const int osVer,
	char * string,
	const int stringSize)
{
#define VER2STR(_Ver, _String) \
	if (_Ver == osVer && _String) \
	{ \
	TStringCopyA(string, _String, 0); \
	return T_TRUE; \
}

	if (string && stringSize > 0)
	{
		VER2STR(T_OSVER_WIN2K, "Windows 2000");
		VER2STR(T_OSVER_WINXP, "Windows XP");
		VER2STR(T_OSVER_WINXPSP1, "Windows XP SP1");
		VER2STR(T_OSVER_WINXPSP2, "Windows XP SP2");
		VER2STR(T_OSVER_WINVISTA, "Windows Vista");
		VER2STR(T_OSVER_WINVISTASP1, "Windows Vista SP1");
		VER2STR(T_OSVER_WINVISTASP2, "Windows Vista SP2");
		VER2STR(T_OSVER_WIN7, "Windows 7");
		VER2STR(T_OSVER_WIN7SP1, "Windows 7 SP1");
		VER2STR(T_OSVER_WIN8, "Windows 8");
		VER2STR(T_OSVER_WIN81, "Windows 8.1");
		VER2STR(T_OSVER_WIN10, "Windows 10");
	}

#undef VER2STR

	return T_FALSE;
}

int TOSInfoIsOSx64(
	int * isX64)
{
#if defined WIN64 || defined _WIN64
	if (isX64)
	{
		*isX64 = T_TRUE;
		return T_TRUE;
	}
#else
	BOOL isWOW64 = FALSE;

	if (!gModuleKernel32)
	{
		gModuleKernel32 = TModuleLoadW(L"kernel32.dll");
	}

	if (gModuleKernel32)
	{
		gIsWow64Process = (TIsWow64Process)TModuleGetProcAddress(
			gModuleKernel32,
			L"IsWow64Process");
	}

	if (isX64 && gIsWow64Process)
	{
		if (gIsWow64Process(GetCurrentProcess(), &isWOW64))
		{
			*isX64 = isWOW64;
			return T_TRUE;
		}
	}
#endif

	return T_FALSE;
}

int TOSSettingTurn(
	const int settingType,
	const int onOrOff)
{
	int ret = T_FALSE;
	BOOL bValue = (1 == onOrOff ? TRUE : FALSE);

	if (T_OSSETTING_CLIENT_AREA_ANIMATION == settingType)
	{
		if (SystemParametersInfoW(SPI_SETCLIENTAREAANIMATION, 0, &bValue, SPIF_SENDCHANGE))
		{
			ret = T_TRUE;
		}
	}
	else if (T_OSSETTING_DROP_SHADOW == settingType)
	{
		if (SystemParametersInfoW(SPI_SETDROPSHADOW, 0, &bValue, SPIF_SENDCHANGE))
		{
			ret = T_TRUE;
		}
	}
	
	return ret;
}

int TOSGetUserNameW(
	wchar_t * userName,
	const int userNameSize)
{
	DWORD bufferSize = userNameSize;

	if (userName && userNameSize > 0)
	{
		if (GetUserNameW(userName, &bufferSize))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TOSGetUserNameA(
	char * userName,
	const int userNameSize)
{
	DWORD bufferSize = userNameSize;

	if (userName && userNameSize > 0)
	{
		if (GetUserNameA(userName, &bufferSize))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}
