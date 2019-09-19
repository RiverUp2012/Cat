
#include "../GameLibInclude/glMutex.h"
#include "../GameLibInclude/glPrivate.h"

glMutex::glMutex() {
	mCriticalSection = new CRITICAL_SECTION();
	memset(mCriticalSection, 0, sizeof(CRITICAL_SECTION));
	InitializeCriticalSection((CRITICAL_SECTION *)mCriticalSection);
}

glMutex::~glMutex() {
	DeleteCriticalSection((CRITICAL_SECTION *)mCriticalSection);
	delete mCriticalSection;
	mCriticalSection = 0;
}

void glMutex::lock(void) {
	EnterCriticalSection((CRITICAL_SECTION *)mCriticalSection);
}

void glMutex::unlock(void) {
	LeaveCriticalSection((CRITICAL_SECTION *)mCriticalSection);
}
