
#pragma once

#include "../GameLibInclude/glNonCopyable.h"

//
// @brief GDI ŒªÕº¿‡
//
class wlGDIBitmap : public glNonCopyable {
public:
	wlGDIBitmap();
	virtual ~wlGDIBitmap();
public:
	bool createEmpty(const int width, const int height, const short int bitCount);
	bool createFromFileW(const wchar_t * fileName);
	void destroy(void);
	const void * getHBITMAP(void) const;
private:
	void * mBitmapHandle;
};
