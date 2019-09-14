
#include "../Include/WinLib.h"

wlGDIBitmap::wlGDIBitmap() {

}

wlGDIBitmap::~wlGDIBitmap() {
	destroy();
}

bool wlGDIBitmap::createEmpty(const int width, const int height, const int bitCount) {
	BITMAPINFO bmpInfo = { 0 };
	destroy();
	bmpInfo.bmiHeader.biSize = sizeof(bmpInfo.bmiHeader);
	bmpInfo.bmiHeader.biBitCount = bitCount;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	mBitmapHandle = CreateDIBSection(0, &bmpInfo, DIB_RGB_COLORS, 0, 0, 0);
	if (mBitmapHandle) {
		return true;
	}
	return false;
}

void wlGDIBitmap::destroy(void) {
	if (mBitmapHandle) {
		DeleteObject(mBitmapHandle);
		mBitmapHandle = 0;
	}
}

const HBITMAP & wlGDIBitmap::getHBITMAP(void) const {
	return mBitmapHandle;
}
