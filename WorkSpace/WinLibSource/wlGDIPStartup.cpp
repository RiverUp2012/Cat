
#include "../Include/WinLibPrivate.h"

namespace {
	ULONG_PTR gToken = 0;
}

void wlGDIPStartup::create(void) {
	Gdiplus::GdiplusStartupInput startupInput = { 0 };
	if (!gToken) {
		Gdiplus::GdiplusStartup(&gToken, &startupInput, 0);
	}
}

void wlGDIPStartup::destroy(void) {
	if (gToken) {
		Gdiplus::GdiplusShutdown(gToken);
		gToken = 0;
	}
}
