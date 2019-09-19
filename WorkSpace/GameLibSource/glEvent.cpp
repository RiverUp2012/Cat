
#include "../GameLibInclude/glEvent.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glPrivate.h"

glEvent::glEvent() {
	mEventHandle = 0;
}

glEvent::~glEvent() {
	destroy();
}

bool glEvent::createW(const wchar_t * eventName, const bool manualReset, const bool initState) {
	if (!mEventHandle) {
		mEventHandle = (void *)CreateEventW(
			0,
			manualReset ? TRUE : FALSE,
			initState ? TRUE : FALSE,
			eventName);
		if (mEventHandle) {
			return true;
		}
		else {
			throw glWin32APIException(L"CreateEventW", GetLastError());
		}
	}
	return false;
}

bool glEvent::openW(const wchar_t * eventName) {
	if (!mEventHandle && eventName) {
		mEventHandle = (void *)OpenEventW(
			EVENT_ALL_ACCESS,
			FALSE,
			eventName);
		if (mEventHandle) {
			return true;
		}
	}
	return false;
}

void glEvent::destroy(void) {
	if (mEventHandle) {
		CloseHandle((HANDLE)mEventHandle);
		mEventHandle = 0;
	}
}

bool glEvent::setEvent(void) {
	if (mEventHandle) {
		if (SetEvent((HANDLE)mEventHandle)) {
			return true;
		}
		else {
			throw glWin32APIException(L"SetEvent", GetLastError());
		}
	}
	return false;
}

bool glEvent::resetEvent(void) {
	if (mEventHandle) {
		if (ResetEvent((HANDLE)mEventHandle)) {
			return true;
		}
		else {
			throw glWin32APIException(L"ResetEvent", GetLastError());
		}
	}
	return false;
}
