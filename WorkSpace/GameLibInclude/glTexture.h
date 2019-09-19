
#pragma once

#include "glNonCopyable.h"
#include "glSize.h"
#include "glString.h"

//
// @brief Œ∆¿Ì¿‡
//
class glTexture : public glNonCopyable {
public:
	glTexture();
	virtual ~glTexture();
public:
	bool createFromFileW(
		const wchar_t * fileName,
		const unsigned int colorKey = 0);
	bool createFromResourceW(
		const int resourceID,
		const wchar_t * resourceType,
		const unsigned int colorKey = 0);
	bool createFromMemory(
		const void * buffer,
		const unsigned int bufferSize,
		const unsigned int colorKey = 0);
	void destroy(void);
	bool isAlready(void) const;
	const glSize<float> & getImageSize(void) const;
	const glSize<float> & getSurfaceSize(void) const;
	void * getIDirect3DTexture9(void) const;
	const wchar_t * getImageFileNameW(void) const;
private:
	void * mD3DTex9;
	glSize<float> mImageSize;
	glSize<float> mSurfaceSize;
	glStringW mImageFileName;
};
