
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_THREAD (64)
#define T_MAX_THREAD_NAME_SIZE (64)

typedef struct _T_THREAD
{
	HANDLE mThreadHandle;
	DWORD mThreadId;
	TThreadProc mThreadProc;
	void * mUserData;
	wchar_t mThreadName[T_MAX_THREAD_NAME_SIZE];
}
T_THREAD;

static T_THREAD gThreadArray[T_MAX_THREAD] = { 0 };

static T_THREAD * TFindUnuseThread(void)
{
	for (int i = 0; i < T_MAX_THREAD; ++i)
	{
		if (!gThreadArray[i].mThreadHandle)
		{
			return &gThreadArray[i];
		}
	}

	return 0;
}

static DWORD WINAPI TGlobalThreadProc(LPVOID param)
{
	T_THREAD * thread = (T_THREAD *)param;
	if (thread && thread->mThreadProc)
	{
		thread->mThreadProc((T_OBJECT)thread, thread->mUserData);
	}

	return 0;
}

T_OBJECT TThreadCreateW(
	TThreadProc threadProc,
	void * userData,
	const int runNow,
	const wchar_t * threadName)
{
	if (threadProc)
	{
		T_THREAD * threadImpl = (T_THREAD *)TFindUnuseThread();
		if (threadImpl)
		{
			threadImpl->mThreadProc = threadProc;
			threadImpl->mUserData = userData;

			threadImpl->mThreadHandle = CreateThread(
				0,
				0,
				TGlobalThreadProc,
				threadImpl,
				runNow ? 0 : CREATE_SUSPENDED,
				&threadImpl->mThreadId);
			if (threadImpl->mThreadHandle)
			{
				if (threadName)
				{
					TStringCopyW(threadImpl->mThreadName, threadName, 0);
				}

				return (T_OBJECT)threadImpl;
			}

			threadImpl->mThreadProc = 0;
			threadImpl->mUserData = 0;
		}
	}

	return 0;
}

void TThreadDestroy(
	T_OBJECT thread,
	const int waitTimeout)
{
	T_THREAD * threadImpl = (T_THREAD *)thread;
	if (threadImpl)
	{
		if (threadImpl->mThreadHandle)
		{
			WaitForSingleObject(threadImpl->mThreadHandle, waitTimeout);
		}

		CloseHandle(threadImpl->mThreadHandle);

		threadImpl->mThreadHandle = 0;
		threadImpl->mThreadId = 0;
		threadImpl->mThreadProc = 0;
		threadImpl->mUserData = 0;
	}
}

void TThreadKill(
	T_OBJECT thread)
{
	T_THREAD * threadImpl = (T_THREAD *)thread;
	if (threadImpl && threadImpl->mThreadHandle)
	{
		TerminateThread(threadImpl->mThreadHandle, 0);
	}
}

int TThreadSuspend(
	T_OBJECT thread)
{
	T_THREAD * threadImpl = (T_THREAD *)thread;
	if (threadImpl && threadImpl->mThreadHandle)
	{
		if (-1 != SuspendThread(threadImpl->mThreadHandle))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TThreadResume(
	T_OBJECT thread)
{
	T_THREAD * threadImpl = (T_THREAD *)thread;
	if (threadImpl && threadImpl->mThreadHandle)
	{
		if (-1 != ResumeThread(threadImpl->mThreadHandle))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TThreadWait(
	T_OBJECT thread,
	const int waitTimeout)
{
	DWORD waitRet = 0;

	T_THREAD * threadImpl = (T_THREAD *)thread;
	if (threadImpl && threadImpl->mThreadHandle)
	{
		waitRet = WaitForSingleObject(threadImpl->mThreadHandle, waitTimeout);
		if (WAIT_FAILED != waitRet)
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

void * TThreadGetUserData(
	T_OBJECT thread)
{
	T_THREAD * threadImpl = (T_THREAD *)thread;

	return threadImpl ? threadImpl->mUserData : 0;
}

TThreadProc TThreadGetThreadProc(
	T_OBJECT thread)
{
	T_THREAD * threadImpl = (T_THREAD *)thread;

	return threadImpl ? threadImpl->mThreadProc : 0;
}

const wchar_t * TThreadGetNameW(
	T_OBJECT thread)
{
	T_THREAD * threadImpl = (T_THREAD *)thread;

	return threadImpl ? threadImpl->mThreadName : L"";
}

unsigned int TThreadGetId(
	T_OBJECT thread)
{
	T_THREAD * threadImpl = (T_THREAD *)thread;

	return threadImpl ? threadImpl->mThreadId : 0;
}

void TThreadCurrentSleep(
	const int sleepTime)
{
	Sleep(sleepTime);
}

T_OBJECT TThreadGetCurrent(void)
{
	const DWORD threadId = GetCurrentThreadId();

	for (int i = 0; i < T_MAX_THREAD; ++i)
	{
		if (gThreadArray[i].mThreadHandle &&
			threadId == gThreadArray[i].mThreadId)
		{
			return &gThreadArray[i];
		}
	}

	return 0;
}
