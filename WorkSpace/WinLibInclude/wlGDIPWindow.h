
#pragma once

#include "../GameLibInclude/glNonCopyable.h"
#include "wlGDIDC.h"
#include "wlGDIBitmap.h"

class wlGDIPImage;

//
// @brief GDI+ ´°¿ÚÀà
//
class wlGDIPWindow : public glNonCopyable {
public:
	wlGDIPWindow();
	virtual ~wlGDIPWindow();
public:
	bool createFromHWND(const void * wndHandle);
	void destroy(void);
	const wlGDIDC & getDC(void) const;
	bool present(void);
	bool drawImage(const wlGDIPImage & image, const int x, const int y, const int width, const int height);
private:
	wlGDIDC mBackBufferDC;
	wlGDIBitmap mBackBufferBitmap;
	void * mGraphics;
	void * mWndHandle;
	wlGDIDC mClientDC;
};
