
#include "../WinLib.h"
#include "../Include/WinLibPrivate.h"

wlGDIPImage::wlGDIPImage() {
	mImage = 0;
	mGlobalHandle = 0;
	mStream = 0;
	wlGDIPStartup::create();
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

bool wlGDIPImage::createFromResourceW(const int resourceID, const wchar_t * resourceType) {
	glModuleResourceHelper::glResourceInfo resInfo = { 0 };
	destroy();
	if (resourceType) {
		if (glModuleResourceHelper::getResourceW(resourceID, resourceType, resInfo)) {
			if (createFromMemory(resInfo.mData, resInfo.mSize)) {
				return true;
			}
		}
	}
	return false;
}

bool wlGDIPImage::createFromMemory(const void * buffer, const int bufferSize) {
	HGLOBAL globalHandle = 0;
	IStream * stream = 0;
	HRESULT comRet = S_OK;
	destroy();
	if (buffer && bufferSize > 0) {
		globalHandle = GlobalAlloc(GMEM_FIXED, bufferSize);
		if (globalHandle) {
			mGlobalHandle = (void *)globalHandle;
			memcpy((void *)globalHandle, buffer, bufferSize);
			comRet = CreateStreamOnHGlobal(globalHandle, FALSE, &stream);
			if (SUCCEEDED(comRet)) {
				mStream = (void *)stream;
				mImage = (void *)Gdiplus::Image::FromStream(stream);
				if (mImage) {
					return true;
				}
			}
			else {
				throw glCOMAPIException(L"CreateStreamOnHGlobal", comRet);
			}
		}
		else {
			throw glWin32APIException(L"GlobalAlloc", GetLastError());
		}
	}
	return false;
}

void wlGDIPImage::destroy(void) {
	Gdiplus::Image * image = (Gdiplus::Image *)mImage;
	HGLOBAL globalHandle = (HGLOBAL)mGlobalHandle;
	IStream * stream = (IStream *)mStream;
	if (image) {
		delete (Gdiplus::Image *)image;
		image = 0;
	}
	if (stream) {
		stream->Release();
		stream = 0;
	}
	if (globalHandle) {
		GlobalFree(globalHandle);
		globalHandle = 0;
	}
	mImage = 0;
	mGlobalHandle = 0;
	mStream = 0;
}

int wlGDIPImage::getWidth(void) const {
	Gdiplus::Image * image = (Gdiplus::Image *)mImage;
	if (image) {
		return image->GetWidth();
	}
	return 0;
}

int wlGDIPImage::getHeight(void) const {
	Gdiplus::Image * image = (Gdiplus::Image *)mImage;
	if (image) {
		return image->GetHeight();
	}
	return 0;
}

void * wlGDIPImage::getImage(void) const {
	return mImage;
}
