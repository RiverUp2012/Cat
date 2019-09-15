
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

glModule::glModule()
{
	mModuleHandle = 0;
}

glModule::glModule(const wchar_t * moduleFileName)
{
	createW(moduleFileName);
}

glModule::~glModule()
{
	destroy();
}

bool glModule::createW(const wchar_t * moduleFileName)
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

void glModule::destroy(void)
{
	if (mModuleHandle)
	{
		FreeLibrary((HMODULE)mModuleHandle);
		mModuleHandle = 0;
	}
}

void * glModule::getProcAddressW(const wchar_t * procName)
{
	glStringA procNameA;

	if (mModuleHandle && procName)
	{
		if (glStringTool::w2a(procName, procNameA))
		{
			return getProcAddressA(procNameA.getString());
		}
	}

	return 0;
}

void * glModule::getProcAddressA(const char * procName)
{
	if (mModuleHandle && procName)
	{
		return GetProcAddress((HMODULE)mModuleHandle, procName);
	}

	return 0;
}
