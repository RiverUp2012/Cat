
#include "../Include/WinLib.h"

wlGDIDC::wlGDIDC() {

}

wlGDIDC::~wlGDIDC() {
	destroy();
}

bool wlGDIDC::createFromHDC(const HDC & dcHandle) {
	destroy();
	mDCHandle = CreateCompatibleDC(dcHandle);
	if (mDCHandle) {
		return true;
	}
	return false;
}

bool wlGDIDC::createFromDC(const wlGDIDC & dc) {
	destroy();
	mDCHandle = CreateCompatibleDC(dc.getHDC());
	if (mDCHandle) {
		return true;
	}
	return false;
}

bool wlGDIDC::createFromHWND(const HWND & wndHandle) {
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

void wlGDIDC::destroy(void) {
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

void wlGDIDC::selectBitmap(wlGDIBitmap & bitmap) {
	if (mDCHandle && bitmap.getHBITMAP()) {
		SelectObject(mDCHandle, bitmap.getHBITMAP());
	}
}

const HDC & wlGDIDC::getHDC(void) const {
	return mDCHandle;
}
