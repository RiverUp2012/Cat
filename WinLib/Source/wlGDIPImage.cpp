
#include "../Include/WinLib.h"

wlGDIPImage::wlGDIPImage() {

}

wlGDIPImage::~wlGDIPImage() {
	destroy();
}

bool wlGDIPImage::createFromFileW(const wchar_t * fileName) {
	destroy();
	if (fileName) {
		mImage = Gdiplus::Image::FromFile(fileName);
		if (mImage) {
			return true;
		}
	}
	return false;
}

void wlGDIPImage::destroy(void) {
	if (mImage) {
		delete mImage;
		mImage = 0;
	}
}

int wlGDIPImage::getWidth(void) const {
	if (mImage) {
		return mImage->GetWidth();
	}
	return 0;
}

int wlGDIPImage::getHeight(void) const {
	if (mImage) {
		return mImage->GetHeight();
	}
	return 0;
}

Gdiplus::Image * wlGDIPImage::getImage(void) const {
	return mImage;
}
