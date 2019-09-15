
#include "../WinLib.h"
#include "../Include/WinLibPrivate.h"

wlGDIPImage::wlGDIPImage() {
	mImage = 0;
	wlGDIPStartup::startup();
}

wlGDIPImage::~wlGDIPImage() {
	destroy();
}

bool wlGDIPImage::createFromFileW(const wchar_t * fileName) {
	destroy();
	if (fileName) {
		mImage = (void *)Gdiplus::Image::FromFile(fileName);
		if (mImage) {
			return true;
		}
	}
	return false;
}

void wlGDIPImage::destroy(void) {
	Gdiplus::Image * imageTemp = (Gdiplus::Image *)mImage;
	if (imageTemp) {
		delete (Gdiplus::Image *)imageTemp;
		mImage = 0;
	}
}

int wlGDIPImage::getWidth(void) const {
	Gdiplus::Image * imageTemp = (Gdiplus::Image *)mImage;
	if (imageTemp) {
		return imageTemp->GetWidth();
	}
	return 0;
}

int wlGDIPImage::getHeight(void) const {
	Gdiplus::Image * imageTemp = (Gdiplus::Image *)mImage;
	if (imageTemp) {
		return imageTemp->GetHeight();
	}
	return 0;
}

void * wlGDIPImage::getImage(void) const {
	return mImage;
}
