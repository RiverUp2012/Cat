
#include "../GameLibInclude/glLog.h"
#include "../GameLibInclude/glMutex.h"
#include "../GameLibInclude/glMutexGuard.h"
#include "../GameLibInclude/glFile.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glStringHelper.h"
#include "../GameLibInclude/glDefine.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glThread.h"
#include "../GameLibInclude/glTimeHelper.h"

namespace {
	static glMutex gMutex;
	static glFile gFile;
	static bool gOutputDebugView = false;
	static bool gAutoAppendNewLine = false;
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
	gAutoAppendNewLine = false;
}

void glLog::setOutputDebugView(const bool outputDebugView) {
	gOutputDebugView = outputDebugView;
}

bool glLog::getOutputDebugView(void) {
	return gOutputDebugView;
}

void glLog::setAutoAppendNewLine(const bool autoAppendNewLine) {
	gAutoAppendNewLine = autoAppendNewLine;
}

bool glLog::getAutoAppendNewLine(void) {
	return gAutoAppendNewLine;
}

bool glLog::putMessageW(const wchar_t * format, ...) {
	bool ret = false;
	glStringW messageW;
	glStringA messageA;
	bool endWithNewLine = false;
	glMutexGuard mutexGuard(&gMutex);
	if (format) {
		GL_FORMAT_W(format, messageW, ret);
		if (ret) {
			if (glStringHelper::w2a(messageW, messageA)) {
				endWithNewLine = glStringHelper::endWithNewLineA(messageA);
				if (gOutputDebugView) {
					OutputDebugStringW(messageW);
					if (gAutoAppendNewLine && !endWithNewLine) {
						OutputDebugStringW(L"\r\n");
					}
				}
				if (gFile.write(
					messageA,
					messageA.getLength() * messageA.getCharSize())) {
					if (gAutoAppendNewLine && !endWithNewLine) {
						if (!gFile.write("\r\n", 2)) {
							return false;
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}

bool glLog::putMessageA(const char * format, ...) {
	bool ret = false;
	glStringA messageA;
	bool endWithNewLine = false;
	glMutexGuard mutexGuard(&gMutex);
	if (format) {
		GL_FORMAT_A(format, messageA, ret);
		if (ret) {
			endWithNewLine = glStringHelper::endWithNewLineA(messageA);
			if (gOutputDebugView) {
				OutputDebugStringA(messageA);
				if (gAutoAppendNewLine && !endWithNewLine) {
					OutputDebugStringW(L"\r\n");
				}
			}
			if (gFile.write(
				messageA,
				messageA.getLength() * messageA.getCharSize())) {
				if (gAutoAppendNewLine && !endWithNewLine) {
					if (!gFile.write("\r\n", 2)) {
						return false;
					}
				}
				return true;
			}
		}
	}
	return false;
}

glLogFunc::glLogFunc(const char * funcName, const int lineNo) {
	mFuncName = funcName;
	mLineNo = lineNo;
	mTimeBegin = 0;
	glTimeHelper::getTimeElapseFromSystemStartup(mTimeBegin);
	glLog::putMessageA(
		"------ %s() [line : %d thread : %d] Begin ------ \r\n",
		mFuncName,
		mLineNo,
		glThread::getCurrentThreadID());
}

glLogFunc::~glLogFunc() {
	unsigned int timeNow = 0;
	glTimeHelper::getTimeElapseFromSystemStartup(timeNow);
	glLog::putMessageA(
		"------ %s() [line : %d thread : %d elapse : %d] End ------ \r\n",
		mFuncName,
		mLineNo,
		glThread::getCurrentThreadID(),
		timeNow - mTimeBegin);
}
