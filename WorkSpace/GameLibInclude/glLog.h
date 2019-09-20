
#pragma once

//
// @brief »’÷æ¿‡
//
class glLog {
public:
	static bool createW(const wchar_t * logFileName);
	static void destroy(void);
	static void setOutputDebugView(const bool outputDebugView);
	static bool getOutputDebugView(void);
	static void setAutoAppendNewLine(const bool autoAppendNewLine);
	static bool getAutoAppendNewLine(void);
	static bool putMessageW(const wchar_t * format, ...);
	static bool putMessageA(const char * format, ...);
};

class glLogFunc {
public:
	glLogFunc(const char * funcName, const int lineNo);
	~glLogFunc();
private:
	const char * mFuncName;
	int mLineNo;
	unsigned int mTimeBegin;
};

#define GL_LOG_FUNC \
	glLogFunc logFunc(__FUNCTION__, __LINE__);
