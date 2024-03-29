
#include "../WinLibInclude/wlGDIBitmap.h"
#include "../WinLibInclude/wlPrivate.h"
#include "../GameLibInclude/glException.h"

wlGDIBitmap::wlGDIBitmap() {
	mBitmapHandle = 0;
}

wlGDIBitmap::~wlGDIBitmap() {
	destroy();
}

bool wlGDIBitmap::createEmpty(const int width, const int height, const short int bitCount) {
	BITMAPINFO bmpInfo = { 0 };
	destroy();
	bmpInfo.bmiHeader.biSize = sizeof(bmpInfo.bmiHeader);
	bmpInfo.bmiHeader.biBitCount = bitCount;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	mBitmapHandle = (void *)CreateDIBSection(0, &bmpInfo, DIB_RGB_COLORS, 0, 0, 0);
	if (!mBitmapHandle) {
		throw glWin32APIException(L"CreateDIBSection", GetLastError());
	}
	return true;
}

bool wlGDIBitmap::createFromFileW(const wchar_t * fileName) {
	destroy();
	if (fileName) {
		mBitmapHandle = (void *)LoadImageW(
			0,
			fileName,
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (!mBitmapHandle) {
			throw glWin32APIException(L"LoadImageW", GetLastError());
		}
		return true;
	}
	return false;
}

void wlGDIBitmap::destroy(void) {
	if (mBitmapHandle) {
		DeleteObject((HBITMAP)mBitmapHandle);
		mBitmapHandle = 0;
	}
}

const void * wlGDIBitmap::getHBITMAP(void) const {
	return mBitmapHandle;
}
