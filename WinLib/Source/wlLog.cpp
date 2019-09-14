
#include "../Include/WinLib.h"

static wlMutex gMutex;

bool wlLog::openW(const wchar_t * logFileName) {
	wlMutexGuard mutexGuard(&gMutex);
	if (logFileName) {
		return true;
	}
	return false;
}

void wlLog::close(void) {
	wlMutexGuard mutexGuard(&gMutex);
}

bool wlLog::putMessageW(const wchar_t * format, ...) {
	wlMutexGuard mutexGuard(&gMutex);
	if (format) {

	}
	return false;
}
