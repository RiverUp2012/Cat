
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_EVENT (64)

typedef struct _T_EVENT
{
	HANDLE mEventHandle;
}
T_EVENT;

static T_EVENT gEventArray[T_MAX_EVENT] = { 0 };

static T_EVENT * TFindUnuseEvent(void)
{
	for (int i = 0; i < T_MAX_EVENT; ++i)
	{
		if (!gEventArray[i].mEventHandle)
		{
			return &gEventArray[i];
		}
	}

	return 0;
}

T_OBJECT TEventCreateW(
	const int manualReset,
	const int initialState,
	const wchar_t * eventName)
{
	T_EVENT * eventImpl = (T_EVENT *)TFindUnuseEvent();
	if (eventImpl)
	{
		eventImpl->mEventHandle = CreateEventW(
			0,
			manualReset ? TRUE : FALSE,
			initialState ? TRUE : FALSE,
			eventName);
		if (eventImpl->mEventHandle)
		{
			return (T_OBJECT)eventImpl;
		}
	}

	return 0;
}

T_OBJECT TEventCreateA(
	const int manualReset,
	const int initialState,
	const char * eventName)
{
	T_EVENT * eventImpl = (T_EVENT *)TFindUnuseEvent();
	if (eventImpl)
	{
		eventImpl->mEventHandle = CreateEventA(
			0,
			manualReset ? TRUE : FALSE,
			initialState ? TRUE : FALSE,
			eventName);
		if (eventImpl->mEventHandle)
		{
			return (T_OBJECT)eventImpl;
		}
	}

	return 0;
}

T_OBJECT TEventOpenW(
	const wchar_t * eventName)
{
	HANDLE eventHandle = 0;

	if (eventName)
	{
		eventHandle = OpenEventW(EVENT_ALL_ACCESS, FALSE, eventName);
		if (eventHandle)
		{
			T_EVENT * eventImpl = (T_EVENT *)TFindUnuseEvent();
			if (eventImpl)
			{
				eventImpl->mEventHandle = eventHandle;

				return (T_OBJECT)eventImpl;
			}

			CloseHandle(eventHandle);
			eventHandle = 0;
		}
	}

	return 0;
}

T_OBJECT TEventOpenA(
	const char * eventName)
{
	HANDLE eventHandle = 0;

	if (eventName)
	{
		eventHandle = OpenEventA(EVENT_ALL_ACCESS, FALSE, eventName);
		if (eventHandle)
		{
			T_EVENT * eventImpl = (T_EVENT *)TFindUnuseEvent();
			if (eventImpl)
			{
				eventImpl->mEventHandle = eventHandle;

				return (T_OBJECT)eventImpl;
			}

			CloseHandle(eventHandle);
			eventHandle = 0;
		}
	}

	return 0;
}

void TEventDestroy(
	T_OBJECT event)
{
	T_EVENT * eventImpl = (T_EVENT *)event;
	if (eventImpl)
	{
		if (eventImpl->mEventHandle)
		{
			CloseHandle(eventImpl->mEventHandle);
			eventImpl->mEventHandle = 0;
		}
	}
}

int TEventWait(
	T_OBJECT event,
	const int waitTimeout)
{
	DWORD waitRet = 0;

	T_EVENT * eventImpl = (T_EVENT *)event;
	if (eventImpl && eventImpl->mEventHandle)
	{
		waitRet = WaitForSingleObject(eventImpl->mEventHandle, waitTimeout);
		if (WAIT_FAILED != waitRet)
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TEventSet(
	T_OBJECT event)
{
	T_EVENT * eventImpl = (T_EVENT *)event;
	if (eventImpl && eventImpl->mEventHandle)
	{
		if (SetEvent(eventImpl->mEventHandle))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TEventReset(
	T_OBJECT event)
{
	T_EVENT * eventImpl = (T_EVENT *)event;
	if (eventImpl && eventImpl->mEventHandle)
	{
		if (ResetEvent(eventImpl->mEventHandle))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}
