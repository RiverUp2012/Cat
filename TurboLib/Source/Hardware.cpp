
#include "../TurboLib.h"
#include "../Include/Private.h"

typedef BOOL (WINAPI * TGlobalMemoryStatusEx)(
	LPMEMORYSTATUSEX lpBuffer);

static T_OBJECT gModuleKernel32 = 0;
static TGlobalMemoryStatusEx gGlobalMemoryStatusEx = 0;

int TMemoryQueryState(
	T_MEMORY_STATE * memoryState)
{
	MEMORYSTATUSEX memoryStatus = { 0 };

	if (!gModuleKernel32)
	{
		gModuleKernel32 = TModuleLoadW(L"kernel32.dll");
	}

	if (gModuleKernel32)
	{
		gGlobalMemoryStatusEx = (TGlobalMemoryStatusEx)TModuleGetProcAddress(
			gModuleKernel32,
			L"GlobalMemoryStatusEx");
	}

	if (memoryState && gGlobalMemoryStatusEx)
	{
		memoryStatus.dwLength = sizeof(memoryStatus);

		if (gGlobalMemoryStatusEx(&memoryStatus))
		{
			memoryState->mTotalPhys = memoryStatus.ullTotalPhys;
			memoryState->mAvailPhys = memoryStatus.ullAvailPhys;
			memoryState->mTotalVirtual = memoryStatus.ullTotalVirtual;
			memoryState->mAvailVirtual = memoryStatus.ullAvailVirtual;

			return T_TRUE;
		}
	}

	return T_FALSE;
}
