
#include "../WinLib.h"

static DWORD WINAPI globalThreadProc(LPVOID param) {
	wlThread * thread = static_cast<wlThread *>(param);
	if (thread) {
		thread->onThreadRun();
	}
	return 0;
}

wlThread::wlThread() {
	mThreadHandle = 0;
	mThreadID = 0;
}

wlThread::~wlThread() {

}

bool wlThread::create(const bool runNow) {
	bool ret = false;
	if (!mThreadHandle) {
		mThreadHandle = (void *)CreateThread(
			0,
			0,
			globalThreadProc,
			this,
			0,
			&mThreadID);
		if (mThreadHandle) {
			if (runNow) {
				if (ResumeThread((HANDLE)mThreadHandle)) {
					ret = true;
				}
			}
			else {
				ret = true;
			}
		}
	}
	return ret;
}

void wlThread::destroy(const int waitTimeout) {
	if (mThreadHandle) {
		WaitForSingleObject((HANDLE)mThreadHandle, waitTimeout);
		CloseHandle((HANDLE)mThreadHandle);
		mThreadHandle = 0;
	}
}

bool wlThread::isAlready(void) const {
	if (mThreadHandle) {
		if (WAIT_TIMEOUT == WaitForSingleObject((HANDLE)mThreadHandle, 0)) {
			return true;
		}
	}
	return false;
}
