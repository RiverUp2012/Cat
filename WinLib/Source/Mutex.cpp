
#include "../Include/WinLib.h"

namespace wl {

	Mutex::Mutex() {
		memset(&mCriticalSection, 0, sizeof(mCriticalSection));
		InitializeCriticalSection(&mCriticalSection);
	}

	Mutex::~Mutex() {
		DeleteCriticalSection(&mCriticalSection);
	}

	void Mutex::lock(void) {
		EnterCriticalSection(&mCriticalSection);
	}

	void Mutex::unlock(void) {
		LeaveCriticalSection(&mCriticalSection);
	}

	MutexGuard::MutexGuard(Mutex * mutex) : mMutex(mutex) {
		if (mMutex) mMutex->lock();
	}

	MutexGuard::~MutexGuard() {
		if (mMutex) mMutex->unlock();
	}

} // namespace wl
