
#include "../WinLib.h"
#include "../Include/WinLibPrivate.h"

wlGDIDC::wlGDIDC() {
	mWndHandle = 0;
	mDCHandle = 0;
}

wlGDIDC::~wlGDIDC() {
	destroy();
}

bool wlGDIDC::createFromHDC(const void * dcHandle) {
	destroy();
	mDCHandle = (void *)CreateCompatibleDC((HDC)dcHandle);
	if (mDCHandle) {
		return true;
	}
	return false;
}

bool wlGDIDC::createFromDC(const wlGDIDC & dc) {
	destroy();
	mDCHandle = (void *)CreateCompatibleDC((HDC)dc.getHDC());
	if (mDCHandle) {
		return true;
	}
	return false;
}

bool wlGDIDC::createFromHWND(const void * wndHandle) {
	destroy();
	if (IsWindow((HWND)wndHandle)) {
		mDCHandle = (void *)GetDC((HWND)wndHandle);
		if (mDCHandle) {
			mWndHandle = (void *)wndHandle;
			return true;
		}
	}
	return false;
}

void wlGDIDC::destroy(void) {
	if (mDCHandle) {
		if (mWndHandle) {
			ReleaseDC((HWND)mWndHandle, (HDC)mDCHandle);
			mWndHandle = 0;
		}
		else {
			DeleteDC((HDC)mDCHandle);
		}
		mDCHandle = 0;
	}
}

void wlGDIDC::selectBitmap(wlGDIBitmap & bitmap) {
	if (mDCHandle && bitmap.getHBITMAP()) {
		SelectObject((HDC)mDCHandle, (HBITMAP)bitmap.getHBITMAP());
	}
}

const void * wlGDIDC::getHDC(void) const {
	return mDCHandle;
}
