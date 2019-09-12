
#include "../Include/WinLib.h"

namespace wl {

	GDIDC::GDIDC() {

	}

	GDIDC::~GDIDC() {
		destroy();
	}

	bool GDIDC::createFromHDC(const HDC & dcHandle) {
		destroy();
		mDCHandle = CreateCompatibleDC(dcHandle);
		if (mDCHandle) {
			return true;
		}
		return false;
	}

	bool GDIDC::createFromDC(const GDIDC & dc) {
		destroy();
		mDCHandle = CreateCompatibleDC(dc.getHDC());
		if (mDCHandle) {
			return true;
		}
		return false;
	}

	bool GDIDC::createFromHWND(const HWND & wndHandle) {
		destroy();
		if (IsWindow(wndHandle)) {
			mDCHandle = GetDC(wndHandle);
			if (mDCHandle) {
				mWndHandle = wndHandle;
				return true;
			}
		}
		return false;
	}

	void GDIDC::destroy(void) {
		if (mDCHandle) {
			if (mWndHandle) {
				ReleaseDC(mWndHandle, mDCHandle);
				mWndHandle = 0;
			}
			else {
				DeleteDC(mDCHandle);
			}
			mDCHandle = 0;
		}
	}

	void GDIDC::selectBitmap(GDIBitmap & bitmap) {
		if (mDCHandle && bitmap.getHBITMAP()) {
			SelectObject(mDCHandle, bitmap.getHBITMAP());
		}
	}

	const HDC & GDIDC::getHDC(void) const {
		return mDCHandle;
	}

} // namespace wl
