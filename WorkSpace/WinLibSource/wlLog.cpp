
#include "../WinLib.h"
#include "../GameLib.h"
#include "../Include/WinLibPrivate.h"

namespace {
	static wlMutex gMutex;
	static glFile gFile;
}

bool wlLog::openW(const wchar_t * logFileName) {
	wlMutexGuard mutexGuard(&gMutex);
	if (logFileName) {
		if (gFile.openW(logFileName, false, true)) {
			return true;
		}
	}
	return false;
}

void wlLog::close(void) {
	wlMutexGuard mutexGuard(&gMutex);
	gFile.close();
}

bool wlLog::putMessageW(const wchar_t * format, ...) {
	bool ret = false;
	glStringW messageW;
	glStringA messageA;
	wlMutexGuard mutexGuard(&gMutex);
	WL_FORMAT_W(format, messageW, ret);
	if (ret) {
		if (wlStringHelper::w2a(messageW.getString(), messageA)) {
			if (gFile.write(
				messageA.getString(),
				messageA.getLength() * messageA.getCharSize())) {
				return true;
			}
		}
	}
	return false;
}

bool wlLog::putMessageA(const char * format, ...) {
	bool ret = false;
	glStringA messageA;
	wlMutexGuard mutexGuard(&gMutex);
	WL_FORMAT_A(format, messageA, ret);
	if (ret) {
		if (gFile.write(
			messageA.getString(),
			messageA.getLength() * messageA.getCharSize())) {
			return true;
		}
	}
	return false;
}
