
#pragma once

#include "glNonCopyable.h"
#include "glRect.h"

class glTexture;

//
// @brief 精灵类
// @desc
//
// glSprite 类在内部已经做过优化操作，用户只需要尽可能将所有的图像都集中在
// 尽可能少的图像文件中，以及尽可能将文本、图形、基础图元进行集中绘制，即可最大限度地优化
// 绘图效率
//
class glSprite : public glNonCopyable {
public:
	glSprite();
	glSprite(glTexture * texture);
	virtual ~glSprite();
public:
	bool createFromTexture(glTexture * texture);
	void destroy(void);
	const glSize<float> & getImageSize(void) const;
	bool paint(void);
	bool paint(
		const glRect<float> & paintRect,
		const glRect<float> & textureRect,
		const unsigned int diffuse = 0xffffffff);
private:
	void * mD3DTex9;
	glSize<float> mImageSize;
	glSize<float> mSurfaceSize;
};
