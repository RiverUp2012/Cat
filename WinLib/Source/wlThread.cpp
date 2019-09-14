
#include "../Include/WinLib.h"

static DWORD WINAPI globalThreadProc(LPVOID param) {
	wlThread * thread = static_cast<wlThread *>(param);
	if (thread) {
		thread->onThreadRun();
	}
	return 0;
}

wlThread::wlThread() {
}

wlThread::~wlThread() {
}

bool wlThread::create(const bool runNow) {
	bool ret = false;
	if (!mThreadHandle) {
		mThreadHandle = CreateThread(0, 0, globalThreadProc, this, 0, &mThreadID);
		if (mThreadHandle) {
			if (runNow) {
				if (ResumeThread(mThreadHandle)) {
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
		WaitForSingleObject(mThreadHandle, waitTimeout);
		CloseHandle(mThreadHandle);
		mThreadHandle = 0;
	}
}

bool wlThread::isAlready(void) const {
	if (mThreadHandle) {
		if (WAIT_TIMEOUT == WaitForSingleObject(mThreadHandle, 0)) {
			return true;
		}
	}
	return false;
}
