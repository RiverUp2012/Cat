
#pragma once

#include "glNonCopyable.h"
#include "glRect.h"

class glTexture;

//
// @brief ������
// @desc
//
// glSprite �����ڲ��Ѿ������Ż��������û�ֻ��Ҫ�����ܽ����е�ͼ�񶼼�����
// �������ٵ�ͼ���ļ��У��Լ������ܽ��ı���ͼ�Ρ�����ͼԪ���м��л��ƣ���������޶ȵ��Ż�
// ��ͼЧ��
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
