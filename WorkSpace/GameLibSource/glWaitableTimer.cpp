
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

glWaitableTimer::glWaitableTimer() {
	mTimerHandle = 0;
}

glWaitableTimer::~glWaitableTimer() {
	destroy();
}

bool glWaitableTimer::create(void) {
	if (!mTimerHandle) {
		mTimerHandle = (HANDLE)CreateWaitableTimerW(0, FALSE, 0);
		if (mTimerHandle) {
			return true;
		}
		else {
			throw glWin32APIException(L"CreateWaitableTimerW", GetLastError());
		}
	}
	return false;
}

void glWaitableTimer::destroy(void) {
	if (mTimerHandle) {
		CloseHandle((HANDLE)mTimerHandle);
		mTimerHandle = 0;
	}
}

bool glWaitableTimer::isAlready(void) const {
	return mTimerHandle ? true : false;
}

bool glWaitableTimer::wait(const int timeOut) {
	LARGE_INTEGER duration = { 0 };
	if (mTimerHandle) {
		duration.QuadPart = -10 * 1000 * timeOut;
		if (SetWaitableTimer((HANDLE)mTimerHandle, &duration, 0, 0, 0, FALSE)) {
			if (WAIT_OBJECT_0 == WaitForSingleObject((HANDLE)mTimerHandle, INFINITE)) {
				return true;
			}
			else {
				throw glWin32APIException(L"WaitForSingleObject", GetLastError());
			}
		}
		else {
			throw glWin32APIException(L"SetWaitableTimer", GetLastError());
		}
	}
	return false;
}
