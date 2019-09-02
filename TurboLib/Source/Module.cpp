
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_MODULE_FILE_NAME_SIZE (520)
#define T_MAX_MODULE (64)

typedef struct _T_MODULE
{
	wchar_t mModuleFileName[T_MAX_MODULE_FILE_NAME_SIZE];
	HMODULE mModuleHandle;
	int mRefCount;
}
T_MODULE;

static T_MODULE gModuleArray[T_MAX_MODULE] = { 0 };

static T_MODULE * TFindUnuseModule(void)
{
	for (int i = 0; i < T_MAX_MODULE; ++i)
	{
		if (!gModuleArray[i].mModuleHandle)
		{
			return &gModuleArray[i];
		}
	}

	return 0;
}

static T_MODULE * TFindModuleByModuleFileName(
	const wchar_t * moduleFileName)
{
	if (moduleFileName)
	{
		for (int i = 0; i < T_MAX_MODULE; ++i)
		{
			if (gModuleArray[i].mModuleHandle &&
				0 == _wcsicmp(moduleFileName, gModuleArray[i].mModuleFileName))
			{
				return &gModuleArray[i];
			}
		}
	}

	return 0;
}

T_OBJECT TModuleLoadW(
	const wchar_t * moduleFileName)
{
	T_MODULE * moduleImpl = TFindModuleByModuleFileName(moduleFileName);
	if (moduleImpl)
	{
		++moduleImpl->mRefCount;

		return (T_OBJECT)moduleImpl;
	}
	else
	{
		moduleImpl = TFindUnuseModule();
		if (moduleImpl)
		{
			moduleImpl->mModuleHandle = LoadLibraryW(moduleFileName);
			if (moduleImpl->mModuleHandle)
			{
				TStringCopyW(moduleImpl->mModuleFileName, moduleFileName, 0);
				moduleImpl->mRefCount = 1;

				return (T_OBJECT)moduleImpl;
			}
		}
	}

	return 0;
}

T_OBJECT TModuleLoadA(
	const char * moduleFileName)
{
	T_OBJECT module = 0;
	wchar_t * moduleFileNameW = 0;

	if (moduleFileName)
	{
		moduleFileNameW = TStringA2W(moduleFileName);
		if (moduleFileNameW)
		{
			module = TModuleLoadW(moduleFileNameW);

			TFree(moduleFileNameW);
			moduleFileNameW = 0;
		}
	}

	return module;
}

void TModuleUnload(
	T_OBJECT module)
{
	T_MODULE * moduleImpl = (T_MODULE *)module;
	if (moduleImpl)
	{
		--moduleImpl->mRefCount;
		if (moduleImpl->mRefCount <= 0)
		{
			if (moduleImpl->mModuleHandle)
			{
				FreeLibrary(moduleImpl->mModuleHandle);
				moduleImpl->mModuleHandle = 0;
			}

			moduleImpl->mRefCount = 0;
			TMemset(moduleImpl->mModuleFileName, sizeof(moduleImpl->mModuleFileName), 0);
		}
	}
}

void * TModuleGetProcAddress(
	T_OBJECT module,
	const wchar_t * procName)
{
	char * procNameA = 0;
	void * procAddress = 0;

	T_MODULE * moduleImpl = (T_MODULE *)module;
	if (moduleImpl && moduleImpl->mModuleHandle && procName)
	{
		procNameA = TStringW2A(procName);
		if (procNameA)
		{
			procAddress = GetProcAddress(moduleImpl->mModuleHandle, procNameA);

			TFree(procNameA);
			procNameA = 0;
		}
	}

	return procAddress;
}

int TModuleIsLoadedW(
	const wchar_t * moduleFileName)
{
	return 0 != TFindModuleByModuleFileName(moduleFileName) ? T_TRUE : T_FALSE;
}

int TModuleIsLoadedA(
	const char * moduleFileName)
{
	int ret = T_FALSE;
	wchar_t * moduleFileNameW = 0;

	if (moduleFileName)
	{
		moduleFileNameW = TStringA2W(moduleFileName);
		if (moduleFileNameW)
		{
			ret = TModuleIsLoadedW(moduleFileNameW);

			TFree(moduleFileNameW);
			moduleFileNameW = 0;
		}
	}

	return ret;
}

HMODULE TModuleGetHandle(
	T_OBJECT module)
{
	T_MODULE * moduleImpl = (T_MODULE *)module;

	return moduleImpl ? moduleImpl->mModuleHandle : 0;
}
