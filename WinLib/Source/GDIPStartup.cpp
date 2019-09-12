
#include "../Include/WinLib.h"

namespace wl {

	GDIPStartup::GDIPStartup() {
		Gdiplus::GdiplusStartupInput startupInput = { 0 };
		if (!mToken) {
			Gdiplus::GdiplusStartup(&mToken, &startupInput, 0);
		}
	}

	GDIPStartup::~GDIPStartup() {
		if (mToken) {
			Gdiplus::GdiplusShutdown(mToken);
			mToken = 0;
		}
	}

} // namespace wl
