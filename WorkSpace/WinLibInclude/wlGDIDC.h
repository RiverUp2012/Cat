
#pragma once

#include "../GameLibInclude/glNonCopyable.h"
#include "../GameLibInclude/glRect.h"

class wlGDIBitmap;

//
// @brief GDI DC ¿‡
//
class wlGDIDC : public glNonCopyable {
public:
	wlGDIDC();
	virtual ~wlGDIDC();
public:
	bool createFromHDC(const void * dcHandle);
	bool createFromDC(const wlGDIDC & dc);
	bool createFromHWND(const void * wndHandle);
	void destroy(void);
	void selectBitmap(const wlGDIBitmap & bitmap);
	const void * getHDC(void) const;
	bool drawFromDC(
		const wlGDIDC & dc,
		const glRect<int> & destRect,
		const glPoint<int> & srcPos);
private:
	void * mWndHandle;
	void * mDCHandle;
};
