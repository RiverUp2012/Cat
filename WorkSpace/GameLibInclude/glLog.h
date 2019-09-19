
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
