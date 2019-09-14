
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

sgeModule::sgeModule()
{
	mModuleHandle = 0;
}

sgeModule::sgeModule(const wchar_t * moduleFileName)
{
	createW(moduleFileName);
}

sgeModule::~sgeModule()
{
	destroy();
}

bool sgeModule::createW(const wchar_t * moduleFileName)
{
	if (!mModuleHandle && moduleFileName)
	{
		mModuleHandle = (void *)LoadLibraryW(moduleFileName);
		if (mModuleHandle)
		{
			return true;
		}
	}

	return false;
}

void sgeModule::destroy(void)
{
	if (mModuleHandle)
	{
		FreeLibrary((HMODULE)mModuleHandle);
		mModuleHandle = 0;
	}
}

void * sgeModule::getProcAddressW(const wchar_t * procName)
{
	sgeStringA procNameA;

	if (mModuleHandle && procName)
	{
		if (sgeStringTool::w2a(procName, procNameA))
		{
			return getProcAddressA(procNameA.getString());
		}
	}

	return 0;
}

void * sgeModule::getProcAddressA(const char * procName)
{
	if (mModuleHandle && procName)
	{
		return GetProcAddress((HMODULE)mModuleHandle, procName);
	}

	return 0;
}
