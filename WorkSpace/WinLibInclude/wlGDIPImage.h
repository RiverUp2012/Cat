
#pragma once

#include "../GameLibInclude/glNonCopyable.h"

//
// @brief GDI+ ÕºœÒ¿‡
//
class wlGDIPImage : public glNonCopyable {
public:
	wlGDIPImage();
	virtual ~wlGDIPImage();
public:
	bool createFromFileW(const wchar_t * fileName);
	bool createFromResourceW(const int resourceID, const wchar_t * resourceType);
	bool createFromMemory(const void * buffer, const int bufferSize);
	void destroy(void);
	int getWidth(void) const;
	int getHeight(void) const;
	void * getImage(void) const;
private:
	void * mImage;
	void * mGlobalHandle;
	void * mStream;
};
