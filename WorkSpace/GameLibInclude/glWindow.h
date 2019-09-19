
#pragma once

#include "glNonCopyable.h"

//
// @brief ´°¿ÚÀà
//
class glWindow : public glNonCopyable {
public:
	glWindow();
	virtual ~glWindow();
public:
	bool createW(
		const wchar_t * windowTitle,
		const int screenWidth,
		const int screenHeight);
	void destroy(void);
	bool isAlready(void) const;
	void * getHandle(void) const;
private:
	void * mWindowHandle;
};
