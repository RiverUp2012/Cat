
#include "../GameLibInclude/glMutex.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"

glMutex::glMutex() {
	mCriticalSection = new CRITICAL_SECTION();
	if (mCriticalSection) {
		memset(mCriticalSection, 0, sizeof(CRITICAL_SECTION));
		InitializeCriticalSection((CRITICAL_SECTION *)mCriticalSection);
	}
	else {
		throw glException(L"bad new");
	}
}

glMutex::~glMutex() {
	if (mCriticalSection) {
		DeleteCriticalSection((CRITICAL_SECTION *)mCriticalSection);
		delete mCriticalSection;
		mCriticalSection = 0;
	}
	else {
		throw glException(L"YOU !! RPWT ??");
	}
}

void glMutex::lock(void) {
	if (mCriticalSection) {
		EnterCriticalSection((CRITICAL_SECTION *)mCriticalSection);
	}
}

void glMutex::unlock(void) {
	if (mCriticalSection) {
		LeaveCriticalSection((CRITICAL_SECTION *)mCriticalSection);
	}
}
