
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

namespace {
	static glMutex gMutex;
	static glFile gFile;
	static bool gOutputDebugView = false;
}

bool glLog::createW(const wchar_t * logFileName) {
	glMutexGuard mutexGuard(&gMutex);
	if (logFileName) {
		if (gFile.openW(logFileName, false, true)) {
			return true;
		}
	}
	return false;
}

void glLog::destroy(void) {
	glMutexGuard mutexGuard(&gMutex);
	gFile.close();
	gOutputDebugView = false;
}

void glLog::setOutputDebugView(const bool outputDebugView) {
	glMutexGuard mutexGuard(&gMutex);
	gOutputDebugView = outputDebugView;
}

bool glLog::putMessageW(const wchar_t * format, ...) {
	bool ret = false;
	glStringW messageW;
	glStringA messageA;
	glMutexGuard mutexGuard(&gMutex);
	GL_FORMAT_W(format, messageW, ret);
	if (ret) {
		if (glStringHelper::w2a(messageW.getString(), messageA)) {
			if (gOutputDebugView) {
				OutputDebugStringW(messageW.getString());
			}
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
		if (gOutputDebugView) {
			OutputDebugStringA(messageA.getString());
		}
		if (gFile.write(
			messageA.getString(),
			messageA.getLength() * messageA.getCharSize())) {
			return true;
		}
	}
	return false;
}
