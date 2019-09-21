
#include "../WinLibInclude/wlGDIDC.h"
#include "../WinLibInclude/wlGDIBitmap.h"
#include "../WinLibInclude/wlPrivate.h"
#include "../GameLibInclude/glException.h"

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
	if (!mDCHandle) {
		throw glWin32APIException(L"CreateCompatibleDC", GetLastError());
	}
	return true;
}

bool wlGDIDC::createFromDC(const wlGDIDC & dc) {
	destroy();
	mDCHandle = (void *)CreateCompatibleDC((HDC)dc.getHDC());
	if (!mDCHandle) {
		throw glWin32APIException(L"CreateCompatibleDC", GetLastError());
	}
	return true;
}

bool wlGDIDC::createFromHWND(const void * wndHandle) {
	destroy();
	if (IsWindow((HWND)wndHandle)) {
		mDCHandle = (void *)GetDC((HWND)wndHandle);
		if (mDCHandle) {
			mWndHandle = (void *)wndHandle;
			return true;
		}
		else {
			throw glWin32APIException(L"GetDC", GetLastError());
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

void wlGDIDC::selectBitmap(const wlGDIBitmap & bitmap) {
	if (mDCHandle && bitmap.getHBITMAP()) {
		SelectObject((HDC)mDCHandle, (HBITMAP)bitmap.getHBITMAP());
	}
}

const void * wlGDIDC::getHDC(void) const {
	return mDCHandle;
}

bool wlGDIDC::drawFromDC(
	const wlGDIDC & dc,
	const glRect<int> & destRect,
	const glPoint<int> & srcPos) {
	if (mDCHandle) {
		if (BitBlt(
			(HDC)mDCHandle,
			destRect.mX,
			destRect.mY,
			destRect.mWidth,
			destRect.mHeight,
			(HDC)dc.getHDC(),
			srcPos.mX,
			srcPos.mY,
			SRCCOPY)) {
			return true;
		}
		else {
			throw glWin32APIException(L"BitBlt", GetLastError());
		}
	}
	return false;
}
