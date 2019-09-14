
#include "../Include/WinLib.h"

wlMutex::wlMutex() {
	memset(&mCriticalSection, 0, sizeof(mCriticalSection));
	InitializeCriticalSection(&mCriticalSection);
}

wlMutex::~wlMutex() {
	DeleteCriticalSection(&mCriticalSection);
}

void wlMutex::lock(void) {
	EnterCriticalSection(&mCriticalSection);
}

void wlMutex::unlock(void) {
	LeaveCriticalSection(&mCriticalSection);
}

wlMutexGuard::wlMutexGuard(wlMutex * mutex) : mMutex(mutex) {
	if (mMutex) mMutex->lock();
}

wlMutexGuard::~wlMutexGuard() {
	if (mMutex) mMutex->unlock();
}
