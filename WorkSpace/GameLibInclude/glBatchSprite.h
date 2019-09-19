
#pragma once

#include "glNonCopyable.h"
#include "glVertexBuffer.h"

struct glSpriteVertex;
struct IDirect3DTexture9;

//
// @brief 批量精灵渲染类
//
class glBatchSprite : public glNonCopyable {
public:
	glBatchSprite();
	virtual ~glBatchSprite();
public:
	bool create(void);
	void destroy(void);
	bool flush(void);
	bool paintSprite(IDirect3DTexture9 * d3dTex9, glSpriteVertex * vertexList);
private:
	void lockVertexBuffer(void);
	void unlockVertexBuffer(void);
private:
	glVertexBuffer mVertexBuffer;
	glSpriteVertex * mVertexList;
	IDirect3DTexture9 * mD3DTex9;
	int mSpriteCount;
};
