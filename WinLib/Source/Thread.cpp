
#include "../Include/WinLib.h"

namespace wl {

	static DWORD WINAPI globalThreadProc(LPVOID param) {
		Thread * thread = static_cast<Thread *>(param);
		if (thread) {
			thread->onThreadRun();
		}
		return 0;
	}

	Thread::Thread() {
	}

	Thread::~Thread() {
	}

	bool Thread::create(const bool runNow) {
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

	void Thread::destroy(const int waitTimeout) {
		if (mThreadHandle) {
			WaitForSingleObject(mThreadHandle, waitTimeout);
			CloseHandle(mThreadHandle);
			mThreadHandle = 0;
		}
	}

	bool Thread::isAlready(void) const {
		if (mThreadHandle) {
			if (WAIT_TIMEOUT == WaitForSingleObject(mThreadHandle, 0)) {
				return true;
			}
		}
		return false;
	}

} // namespace wl
