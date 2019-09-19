
#include "../GameLibInclude/glThread.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"

static DWORD WINAPI globalThreadProc(LPVOID param) {
	glThread * thread = static_cast<glThread *>(param);
	if (thread) {
		thread->onThreadRun();
	}
	return 0;
}

void glThread::sleepCurrentThread(const int sleepTimeOut) {
	Sleep(sleepTimeOut);
}

unsigned long glThread::getCurrentThreadID(void) {
	return (unsigned long)GetCurrentThreadId();
}

glThread::glThread() {
	mThreadHandle = 0;
	mThreadID = 0;
}

glThread::~glThread() {

}

bool glThread::create(const bool runNow) {
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
				if (-1 != ResumeThread((HANDLE)mThreadHandle)) {
					ret = true;
				}
				else {
					throw glWin32APIException(L"ResumeThread", GetLastError());
				}
			}
			else {
				ret = true;
			}
		}
		else {
			throw glWin32APIException(L"CreateThread", GetLastError());
		}
	}
	return ret;
}

void glThread::destroy(const int waitTimeout) {
	if (mThreadHandle) {
		WaitForSingleObject((HANDLE)mThreadHandle, waitTimeout);
		CloseHandle((HANDLE)mThreadHandle);
		mThreadHandle = 0;
	}
	mThreadID = 0;
}

bool glThread::wait(const int waitTimeout) {
	DWORD waitRet = 0;
	if (mThreadHandle) {
		waitRet = WaitForSingleObject((HANDLE)mThreadHandle, waitTimeout);
		if (WAIT_OBJECT_0 == waitRet || WAIT_TIMEOUT == waitRet) {
			return true;
		}
		else {
			throw glWin32APIException(L"WaitForSingleObject", GetLastError());
		}
	}
	return false;
}

bool glThread::isAlready(void) const {
	if (mThreadHandle) {
		if (WAIT_TIMEOUT == WaitForSingleObject((HANDLE)mThreadHandle, 0)) {
			return true;
		}
	}
	return false;
}
