
#include "../Include/WinLib.h"

wlGDIPWindow::wlGDIPWindow() {

}

wlGDIPWindow::~wlGDIPWindow() {
	destroy();
}

bool wlGDIPWindow::createFromHWND(const HWND & wndHandle) {
	bool ret = false;
	RECT clientRect = { 0 };
	destroy();
	if (IsWindow(wndHandle)) {
		if (GetClientRect(wndHandle, &clientRect)) {
			if (mBackBufferBitmap.createEmpty(
				clientRect.right - clientRect.left,
				clientRect.bottom - clientRect.top,
				32)) {
				if (mClientDC.createFromHWND(wndHandle)) {
					if (mBackBufferDC.createFromDC(mClientDC)) {
						mBackBufferDC.selectBitmap(mBackBufferBitmap);
						mGraphics = Gdiplus::Graphics::FromHDC(mBackBufferDC.getHDC());
						if (mGraphics) {
							mWndHandle = wndHandle;
							ret = true;
						}
					}
				}
			}
		}
	}
	return ret;
}

void wlGDIPWindow::destroy(void) {
	if (mGraphics) {
		delete mGraphics;
		mGraphics = 0;
	}
	mBackBufferBitmap.destroy();
	mBackBufferDC.destroy();
	mWndHandle = 0;
	mClientDC.destroy();
}

const wlGDIDC & wlGDIPWindow::getDC(void) const {
	return mBackBufferDC;
}

bool wlGDIPWindow::present(void) {
	RECT clientRect = { 0 };
	POINT ptDest = { 0 };
	POINT ptSrc = { 0 };
	SIZE sizeDest = { 0 };
	BLENDFUNCTION blendFunc = { 0 };
	if (IsWindow(mWndHandle)) {
		if (GetClientRect(mWndHandle, &clientRect)) {
			sizeDest.cx = clientRect.right - clientRect.left;
			sizeDest.cy = clientRect.bottom - clientRect.top;
			blendFunc.AlphaFormat = AC_SRC_ALPHA;
			blendFunc.BlendFlags = 0;
			blendFunc.BlendOp = AC_SRC_OVER;
			blendFunc.SourceConstantAlpha = 255;
			if (::UpdateLayeredWindow(
				mWndHandle,
				mClientDC.getHDC(),
				&ptDest,
				&sizeDest,
				mBackBufferDC.getHDC(),
				&ptSrc,
				0,
				&blendFunc,
				ULW_ALPHA)) {
				return true;
			}
		}
	}
	return false;
}

bool wlGDIPWindow::drawImage(wlGDIPImage & image, const int x, const int y, const int width, const int height) {
	Gdiplus::Image * imageTemp = image.getImage();
	if (mGraphics && imageTemp) {
		if (Gdiplus::Ok == mGraphics->DrawImage(imageTemp, x, y, width, height)) {
			return true;
		}
	}
	return false;
}
