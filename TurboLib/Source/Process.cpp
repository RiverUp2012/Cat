
#include "../TurboLib.h"
#include "../Include/Private.h"

typedef BOOL (WINAPI * TQueryFullProcessImageNameW)(
	HANDLE hProcess,
	DWORD dwFlags,
	LPWSTR lpExeName,
	PDWORD lpdwSize);
typedef DWORD (WINAPI * TGetModuleFileNameExW)(
	HANDLE hProcess,
	HMODULE hModule,
	LPWSTR lpFilename,
	DWORD nSize);

#define T_MAX_PROCESS (128)
#define T_MAX_PROCESS_IMAGE_NAME_SIZE (520)

typedef struct _T_PROCESS
{
	HANDLE mProcessHandle;
	DWORD mProcessId;
	wchar_t mImageName[T_MAX_PROCESS_IMAGE_NAME_SIZE];
}
T_PROCESS;

static T_PROCESS gProcessArray[T_MAX_PROCESS] = { 0 };
static T_OBJECT gModuleKernel32 = 0;
static T_OBJECT gModulePSAPI = 0;
static TQueryFullProcessImageNameW gQueryFullProcessImageNameW = 0;
static TGetModuleFileNameExW gGetModuleFileNameExW = 0;

static T_PROCESS * TFindUnuseProcess(void)
{
	for (int i = 0; i < T_MAX_PROCESS; ++i)
	{
		if (!gProcessArray[i].mProcessHandle &&
			!gProcessArray[i].mProcessId)
		{
			return &gProcessArray[i];
		}
	}

	return 0;
}

int TProcessIsX64(void)
{
#if defined WIN64 || defined _WIN64
	return T_TRUE;
#endif

	return T_FALSE;
}

int TProcessEnum(
	TProcessCallbackProc enumProc,
	void * userData)
{
	int ret = T_FALSE;
	HANDLE snapshotHandle = 0;
	PROCESSENTRY32W processEntry = { 0 };

	if (enumProc)
	{
		snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE != snapshotHandle)
		{
			processEntry.dwSize = sizeof(processEntry);
			if (Process32FirstW(snapshotHandle, &processEntry))
			{
				do 
				{
					if (!enumProc(processEntry.th32ProcessID, userData))
					{
						break;
					}

				} while (Process32NextW(snapshotHandle, &processEntry));

				ret = T_TRUE;
			}

			CloseHandle(snapshotHandle);
			snapshotHandle = 0;
		}
	}

	return ret;
}

int TProcessQueryImageNameByProcessIdW(
	const unsigned int processId,
	wchar_t * imageName,
	const int imageNameSize)
{
	int ret = T_FALSE;
	HANDLE processHandle = 0;
	DWORD imageNameSizeTemp = imageNameSize;

	if (!gModuleKernel32)
	{
		gModuleKernel32 = TModuleLoadW(L"kernel32.dll");
	}

	if (!gModulePSAPI)
	{
		gModulePSAPI = TModuleLoadW(L"Psapi.dll");
	}

	if (gModuleKernel32)
	{
		// QueryFullProcessImageNameW 从 WinVista 开始支持

		if (!gQueryFullProcessImageNameW)
		{
			gQueryFullProcessImageNameW = (TQueryFullProcessImageNameW)TModuleGetProcAddress(
				gModuleKernel32,
				L"QueryFullProcessImageNameW");
		}
	}

	if (gModulePSAPI)
	{
		// GetModuleFileNameExW 从 Win2K Pro 开始支持

		if (!gGetModuleFileNameExW)
		{
			gGetModuleFileNameExW = (TGetModuleFileNameExW)TModuleGetProcAddress(
				gModulePSAPI,
				L"GetModuleFileNameExW");
		}
	}

	if (imageName && imageNameSize > 0 && (gQueryFullProcessImageNameW || gGetModuleFileNameExW))
	{
		processHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processId);
		if (processHandle)
		{
			if (gQueryFullProcessImageNameW)
			{
				if (gQueryFullProcessImageNameW(
					processHandle,
					//PROCESS_NAME_NATIVE, // 使用原生 Win32 路径格式，不宜于理解
					0,
					imageName,
					&imageNameSizeTemp))
				{
					ret = T_TRUE;
				}
			}
			else if (gGetModuleFileNameExW)
			{
				if (gGetModuleFileNameExW(
					processHandle,
					0,
					imageName,
					imageNameSize))
				{
					ret = T_TRUE;
				}
			}

			CloseHandle(processHandle);
			processHandle = 0;
		}
	}

	return ret;
}
