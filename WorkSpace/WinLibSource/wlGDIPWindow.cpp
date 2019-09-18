
#include "../WinLib.h"
#include "../Include/WinLibPrivate.h"

wlGDIPWindow::wlGDIPWindow() {
	mGraphics = 0;
	mWndHandle = 0;
	wlGDIPStartup::create();
}

wlGDIPWindow::~wlGDIPWindow() {
	destroy();
}

bool wlGDIPWindow::createFromHWND(const void * wndHandle) {
	bool ret = false;
	RECT clientRect = { 0 };
	destroy();
	if (IsWindow((HWND)wndHandle)) {
		if (GetClientRect((HWND)wndHandle, &clientRect)) {
			if (mBackBufferBitmap.createEmpty(
				clientRect.right - clientRect.left,
				clientRect.bottom - clientRect.top,
				32)) {
				if (mClientDC.createFromHWND(wndHandle)) {
					if (mBackBufferDC.createFromDC(mClientDC)) {
						mBackBufferDC.selectBitmap(mBackBufferBitmap);
						mGraphics = (void *)Gdiplus::Graphics::FromHDC((HDC)mBackBufferDC.getHDC());
						if (mGraphics) {
							mWndHandle = (void *)wndHandle;
							ret = true;
						}
					}
				}
			}
		}
		else {
			throw glWin32APIException(L"GetClientRect", GetLastError());
		}
	}
	return ret;
}

void wlGDIPWindow::destroy(void) {
	Gdiplus::Graphics * graphicsTemp = (Gdiplus::Graphics *)mGraphics;
	if (graphicsTemp) {
		delete graphicsTemp;
	}
	mGraphics = 0;
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
	if (IsWindow((HWND)mWndHandle)) {
		if (GetClientRect((HWND)mWndHandle, &clientRect)) {
			sizeDest.cx = clientRect.right - clientRect.left;
			sizeDest.cy = clientRect.bottom - clientRect.top;
			blendFunc.AlphaFormat = AC_SRC_ALPHA;
			blendFunc.BlendFlags = 0;
			blendFunc.BlendOp = AC_SRC_OVER;
			blendFunc.SourceConstantAlpha = 255;
			if (::UpdateLayeredWindow(
				(HWND)mWndHandle,
				(HDC)mClientDC.getHDC(),
				&ptDest,
				&sizeDest,
				(HDC)mBackBufferDC.getHDC(),
				&ptSrc,
				0,
				&blendFunc,
				ULW_ALPHA)) {
				return true;
			}
			else {
				throw glWin32APIException(L"UpdateLayeredWindow", GetLastError());
			}
		}
		else {
			throw glWin32APIException(L"GetClientRect", GetLastError());
		}
	}
	return false;
}

bool wlGDIPWindow::drawImage(const wlGDIPImage & image, const int x, const int y, const int width, const int height) {
	Gdiplus::Graphics * graphicsTemp = (Gdiplus::Graphics *)mGraphics;
	Gdiplus::Image * imageTemp = (Gdiplus::Image *)image.getImage();
	if (graphicsTemp && imageTemp) {
		if (Gdiplus::Ok == graphicsTemp->DrawImage(imageTemp, x, y, width, height)) {
			return true;
		}
	}
	return false;
}
