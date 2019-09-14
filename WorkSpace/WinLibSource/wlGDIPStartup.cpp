
#include "../WinLib.h"

wlGDIPStartup::wlGDIPStartup() {
	Gdiplus::GdiplusStartupInput startupInput = { 0 };
	if (!mToken) {
		Gdiplus::GdiplusStartup(&mToken, &startupInput, 0);
	}
}

wlGDIPStartup::~wlGDIPStartup() {
	if (mToken) {
		Gdiplus::GdiplusShutdown(mToken);
		mToken = 0;
	}
}
