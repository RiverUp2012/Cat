
#include "../GameLibInclude/glLog.h"
#include "../GameLibInclude/glMutex.h"
#include "../GameLibInclude/glMutexGuard.h"
#include "../GameLibInclude/glFile.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glStringHelper.h"
#include "../GameLibInclude/glDefine.h"
#include "../GameLibInclude/glPrivate.h"

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
		if (glStringHelper::w2a(messageW, messageA)) {
			if (gOutputDebugView) {
				OutputDebugStringW(messageW);
			}
			if (gFile.write(
				messageA,
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
			OutputDebugStringA(messageA);
		}
		if (gFile.write(
			messageA,
			messageA.getLength() * messageA.getCharSize())) {
			return true;
		}
	}
	return false;
}
