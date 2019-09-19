
#include "../GameLibInclude/glMutexGuard.h"
#include "../GameLibInclude/glMutex.h"

glMutexGuard::glMutexGuard(glMutex * mutex) : mMutex(mutex) {
	if (mMutex) mMutex->lock();
}

glMutexGuard::~glMutexGuard() {
	if (mMutex) mMutex->unlock();
}
