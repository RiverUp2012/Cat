
#include "../TurboLib.h"
#include "../Include/Private.h"

typedef struct _T_MUTEX
{
	CRITICAL_SECTION mCriticalSection;
}
T_MUTEX;

T_OBJECT TMutexCreate(void)
{
	T_MUTEX * mutexImpl = (T_MUTEX *)TMalloc0(sizeof(T_MUTEX));
	if (mutexImpl)
	{
		InitializeCriticalSection(&mutexImpl->mCriticalSection);
	}

	return (T_OBJECT)mutexImpl;
}

void TMutexDestroy(
	T_OBJECT mutex)
{
	T_MUTEX * mutexImpl = (T_MUTEX *)mutex;
	if (mutexImpl)
	{
		DeleteCriticalSection(&mutexImpl->mCriticalSection);

		TFree(mutexImpl);
		mutexImpl = 0;
	}
}

void TMutexLock(
	T_OBJECT mutex)
{
	T_MUTEX * mutexImpl = (T_MUTEX *)mutex;
	if (mutexImpl)
	{
		EnterCriticalSection(&mutexImpl->mCriticalSection);
	}
}

void TMutexUnlock(
	T_OBJECT mutex)
{
	T_MUTEX * mutexImpl = (T_MUTEX *)mutex;
	if (mutexImpl)
	{
		LeaveCriticalSection(&mutexImpl->mCriticalSection);
	}
}
