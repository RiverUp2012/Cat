
#include "../Include/WinLib.h"

namespace wl {

	GDIPImage::GDIPImage() {

	}

	GDIPImage::~GDIPImage() {
		destroy();
	}

	bool GDIPImage::createFromFileW(const wchar_t * fileName) {
		destroy();
		if (fileName) {
			mImage = Gdiplus::Image::FromFile(fileName);
			if (mImage) {
				return true;
			}
		}
		return false;
	}

	void GDIPImage::destroy(void) {
		if (mImage) {
			delete mImage;
			mImage = 0;
		}
	}

	int GDIPImage::getWidth(void) const {
		if (mImage) {
			return mImage->GetWidth();
		}
		return 0;
	}

	int GDIPImage::getHeight(void) const {
		if (mImage) {
			return mImage->GetHeight();
		}
		return 0;
	}

	Gdiplus::Image * GDIPImage::getImage(void) const {
		return mImage;
	}

} // namespace wl
