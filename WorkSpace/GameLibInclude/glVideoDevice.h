
#pragma once

#include "glNonCopyable.h"

class glWindow;
struct IDirect3DDevice9;

//
// @brief 视频设备类
//
class glVideoDevice : public glNonCopyable {
public:
	glVideoDevice();
	virtual ~glVideoDevice();
public:
	bool create(
		glWindow & window,
		const int screenWidth,
		const int screenHeight);
	void destroy(void);
	bool isAlready(void) const;
	IDirect3DDevice9 * getIDirect3DDevice9(void) const;
	bool clear(const unsigned int clearColor);
	bool present(void);
private:
	void setupDefaultRenderStatus(void);
private:
	IDirect3DDevice9 * mD3DDev9;
};
