
#include "../WinLib.h"

wlMutex::wlMutex() {
	mCriticalSection = new CRITICAL_SECTION();
	memset(mCriticalSection, 0, sizeof(CRITICAL_SECTION));
	InitializeCriticalSection((CRITICAL_SECTION *)mCriticalSection);
}

wlMutex::~wlMutex() {
	DeleteCriticalSection((CRITICAL_SECTION *)mCriticalSection);
	delete mCriticalSection;
	mCriticalSection = 0;
}

void wlMutex::lock(void) {
	EnterCriticalSection((CRITICAL_SECTION *)mCriticalSection);
}

void wlMutex::unlock(void) {
	LeaveCriticalSection((CRITICAL_SECTION *)mCriticalSection);
}

wlMutexGuard::wlMutexGuard(wlMutex * mutex) : mMutex(mutex) {
	if (mMutex) mMutex->lock();
}

wlMutexGuard::~wlMutexGuard() {
	if (mMutex) mMutex->unlock();
}
