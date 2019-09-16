
#include "../GameLib.h"

namespace {
	static glMutex gMutex;
	static glFile gFile;
}

bool glLog::openW(const wchar_t * logFileName) {
	glMutexGuard mutexGuard(&gMutex);
	if (logFileName) {
		if (gFile.openW(logFileName, false, true)) {
			return true;
		}
	}
	return false;
}

void glLog::close(void) {
	glMutexGuard mutexGuard(&gMutex);
	gFile.close();
}

bool glLog::putMessageW(const wchar_t * format, ...) {
	bool ret = false;
	glStringW messageW;
	glStringA messageA;
	glMutexGuard mutexGuard(&gMutex);
	GL_FORMAT_W(format, messageW, ret);
	if (ret) {
		if (glStringHelper::w2a(messageW.getString(), messageA)) {
			if (gFile.write(
				messageA.getString(),
				messageA.getLength() * messageA.getCharSize())) {
				return true;
			}
		}
	}
	return false;
}

bool glLog::putMessageA(const char * format, ...) {
	bool ret = false;
	glStringA messageA;
	glMutexGuard mutexGuard(&gMutex);
	GL_FORMAT_A(format, messageA, ret);
	if (ret) {
		if (gFile.write(
			messageA.getString(),
			messageA.getLength() * messageA.getCharSize())) {
			return true;
		}
	}
	return false;
}
