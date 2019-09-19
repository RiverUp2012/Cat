
#include "../GameLibInclude/glSprite.h"
#include "../GameLibInclude/glTexture.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glStruct.h"
#include "../GameLibInclude/glGlobalData.h"

glSprite::glSprite() {
	mD3DTex9 = 0;
}

glSprite::glSprite(glTexture * texture) {
	createFromTexture(texture);
}

glSprite::~glSprite() {
	destroy();
}

bool glSprite::createFromTexture(glTexture * texture) {
	IDirect3DTexture9 * d3dTex9 = 0;
	destroy();
	if (texture) {
		d3dTex9 = (IDirect3DTexture9 *)texture->getIDirect3DTexture9();
		if (d3dTex9) {
			d3dTex9->AddRef();
			mImageSize = texture->getImageSize();
			mSurfaceSize = texture->getSurfaceSize();
			mD3DTex9 = (void *)d3dTex9;
			return true;
		}
	}
	return false;
}

void glSprite::destroy(void) {
	IDirect3DTexture9 * d3dTex9 = (IDirect3DTexture9 *)mD3DTex9;
	if (d3dTex9) {
		if (gVideoDevice.isAlready()) {
			d3dTex9->Release();
		}
	}
	mD3DTex9 = 0;
	mImageSize = glSize<float>();
	mSurfaceSize = glSize<float>();
}

bool glSprite::paint(void) {
	glSpriteVertex vertexList[4] = { 0 };
	if (mD3DTex9 && mSurfaceSize.mWidth > 0 && mSurfaceSize.mHeight > 0) {
		for (int i = 0; i < 4; ++i) {
			vertexList[i].rhw = 1.0f;
			vertexList[i].diffuse = 0xffffffff;
		}
		vertexList[0].x = 0;
		vertexList[0].y = 0;
		vertexList[0].u = 0;
		vertexList[0].v = 0;
		vertexList[1].x = mImageSize.mWidth;
		vertexList[1].y = 0;
		vertexList[1].u = (mImageSize.mWidth + 0.5f) / mSurfaceSize.mWidth;
		vertexList[1].v = 0;
		vertexList[2].x = 0;
		vertexList[2].y = mImageSize.mHeight;
		vertexList[2].u = 0;
		vertexList[2].v = (mImageSize.mHeight + 0.5f) / mSurfaceSize.mHeight;
		vertexList[3].x = mImageSize.mWidth;
		vertexList[3].y = mImageSize.mHeight;
		vertexList[3].u = (mImageSize.mWidth + 0.5f) / mSurfaceSize.mWidth;
		vertexList[3].v = (mImageSize.mHeight + 0.5f) / mSurfaceSize.mHeight;
		return gBatchSprite.paintSprite((IDirect3DTexture9 *)mD3DTex9, vertexList);
	}
	return false;
}

bool glSprite::paint(
	const glRect<float> & paintRect,
	const glRect<float> & textureRect,
	const unsigned int diffuse) {
	glSpriteVertex vertexList[4] = { 0 };
	if (mD3DTex9 && mSurfaceSize.mWidth > 0 && mSurfaceSize.mHeight > 0) {
		for (int i = 0; i < 4; ++i) {
			vertexList[i].rhw = 1.0f;
			vertexList[i].diffuse = diffuse;
		}
		vertexList[0].x = paintRect.mX;
		vertexList[0].y = paintRect.mY;
		vertexList[0].u = (textureRect.mX + 0.5f) / mSurfaceSize.mWidth;
		vertexList[0].v = (textureRect.mY + 0.5f) / mSurfaceSize.mHeight;
		vertexList[1].x = paintRect.getRight();
		vertexList[1].y = paintRect.mY;
		vertexList[1].u = (textureRect.getRight() + 0.5f) / mSurfaceSize.mWidth;
		vertexList[1].v = (textureRect.mY + 0.5f) / mSurfaceSize.mHeight;
		vertexList[2].x = paintRect.mX;
		vertexList[2].y = paintRect.getBottom();
		vertexList[2].u = (textureRect.mX + 0.5f) / mSurfaceSize.mWidth;
		vertexList[2].v = (textureRect.getBottom() + 0.5f) / mSurfaceSize.mHeight;
		vertexList[3].x = paintRect.getRight();
		vertexList[3].y = paintRect.getBottom();
		vertexList[3].u = (textureRect.getRight() + 0.5f) / mSurfaceSize.mWidth;
		vertexList[3].v = (textureRect.getBottom() + 0.5f) / mSurfaceSize.mHeight;
		return gBatchSprite.paintSprite((IDirect3DTexture9 *)mD3DTex9, vertexList);
	}
	return false;
}
