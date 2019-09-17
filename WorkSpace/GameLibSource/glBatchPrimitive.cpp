
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

#define GL_PRIMITIVE_VERTEX_SIZE (sizeof(glPrimitiveVertex))
#define GL_PRIMITIVE_VERTEX_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define GL_MAX_PRIMITIVE_VERTEX (1024 * 8)

glBatchPrimitive::glBatchPrimitive() {
	mVertexList = 0;
	mPrimitiveCount = 0;
	mPrimitiveType = glPrimitiveTypeUnknown;
}

glBatchPrimitive::~glBatchPrimitive() {
	destroy();
}

bool glBatchPrimitive::create(void) {
	destroy();
	if (mVertexBuffer.create(
		GL_PRIMITIVE_VERTEX_SIZE * GL_MAX_PRIMITIVE_VERTEX,
		GL_PRIMITIVE_VERTEX_FVF)) 	{
		lockVertexBuffer();
		return true;
	}
	return false;
}

void glBatchPrimitive::destroy(void) {
	unlockVertexBuffer();
	mVertexBuffer.destroy();
	mVertexList = 0;
	mPrimitiveCount = 0;
	mPrimitiveType = glPrimitiveTypeUnknown;
}

bool glBatchPrimitive::flush(void) {
	bool ret = false;
	D3DPRIMITIVETYPE d3dPrimType = D3DPT_POINTLIST;
	IDirect3DDevice9 * d3dDev9 = gVideoDevice.getIDirect3DDevice9();
	if (mVertexBuffer.isAlready() && d3dDev9) {
		if (glPrimitiveTypeUnknown != mPrimitiveType && mPrimitiveCount > 0) {
			unlockVertexBuffer();
			if (glPrimitiveTypePoint == mPrimitiveType) {
				d3dPrimType = D3DPT_POINTLIST;
			}
			else if (glPrimitiveTypeLine == mPrimitiveType) {
				d3dPrimType = D3DPT_LINELIST;
			}
			else if (glPrimitiveTypeTriangle == mPrimitiveType) {
				d3dPrimType = D3DPT_TRIANGLELIST;
			}
			if (SUCCEEDED(d3dDev9->SetTexture(0, 0))) {
				if (SUCCEEDED(d3dDev9->SetStreamSource(
					0,
					mVertexBuffer.getIDirect3DVertexBuffer9(),
					0,
					GL_PRIMITIVE_VERTEX_SIZE))) {
					if (SUCCEEDED(d3dDev9->SetFVF(GL_PRIMITIVE_VERTEX_FVF))) {
						if (SUCCEEDED(d3dDev9->DrawPrimitive(
							d3dPrimType,
							0,
							mPrimitiveCount))) {
							mPrimitiveCount = 0;
							ret = true;
						}
					}
				}
			}
		}
		else {
			ret = true;
		}
	}
	return ret;
}

bool glBatchPrimitive::paintPoint(
	const glPoint<float> & pos,
	const unsigned int color) {
	if (mVertexBuffer.isAlready()) {
		if (glPrimitiveTypePoint != mPrimitiveType ||
			mPrimitiveCount >= GL_MAX_PRIMITIVE_VERTEX) {
			flush();
			mPrimitiveType = glPrimitiveTypePoint;
			mPrimitiveCount = 0;
		}
		lockVertexBuffer();
		if (mVertexList) {
			glPrimitiveVertex * vertexList = &mVertexList[mPrimitiveCount];
			++mPrimitiveCount;
			vertexList[0].x = pos.mX;
			vertexList[0].y = pos.mY;
			vertexList[0].diffuse = color;
			return true;
		}
	}
	return false;
}

bool glBatchPrimitive::paintLine(
	const glPoint<float> & posStart,
	const glPoint<float> & posEnd,
	const unsigned int color) {
	if (mVertexBuffer.isAlready()) {
		if (glPrimitiveTypeLine != mPrimitiveType ||
			mPrimitiveCount * 2 >= GL_MAX_PRIMITIVE_VERTEX) {
			flush();
			mPrimitiveType = glPrimitiveTypeLine;
			mPrimitiveCount = 0;
		}
		lockVertexBuffer();
		if (mVertexList) {
			glPrimitiveVertex * vertexList = &mVertexList[mPrimitiveCount * 2];
			++mPrimitiveCount;
			vertexList[0].x = posStart.mX;
			vertexList[0].y = posStart.mY;
			vertexList[0].diffuse = color;
			vertexList[1].x = posEnd.mX;
			vertexList[1].y = posEnd.mY;
			vertexList[1].diffuse = color;
			return true;
		}
	}
	return false;
}

bool glBatchPrimitive::paintTriangle(
	const glPoint<float> & pt1,
	const glPoint<float> & pt2,
	const glPoint<float> & pt3,
	const unsigned int color,
	const bool solid)
{
	if (solid)
	{
		if (mVertexBuffer.isAlready())
		{
			if (glPrimitiveTypeTriangle != mPrimitiveType ||
				mPrimitiveCount * 3 >= GL_MAX_PRIMITIVE_VERTEX)
			{
				flush();

				mPrimitiveType = glPrimitiveTypeTriangle;
				mPrimitiveCount = 0;
			}

			lockVertexBuffer();
			if (mVertexList)
			{
				glPrimitiveVertex * vertexList = &mVertexList[mPrimitiveCount * 3];
				++mPrimitiveCount;

				vertexList[0].x = pt1.mX;
				vertexList[0].y = pt1.mY;
				vertexList[0].diffuse = color;

				vertexList[1].x = pt2.mX;
				vertexList[1].y = pt2.mY;
				vertexList[1].diffuse = color;

				vertexList[2].x = pt3.mX;
				vertexList[2].y = pt3.mY;
				vertexList[2].diffuse = color;

				return true;
			}
		}
	}
	else
	{
		if (paintLine(pt1, pt2, color) &&
			paintLine(pt2, pt3, color) &&
			paintLine(pt3, pt1, color))
		{
			return true;
		}
	}

	return false;
}

bool glBatchPrimitive::paintRectangle(
	const glPoint<float> & pos,
	const glSize<float> & size,
	const unsigned int color,
	const bool solid) {
	const glPoint<float> & pt1 = pos;
	const glPoint<float> & pt2 = glPoint<float>(pos.mX + size.mWidth, pos.mY);
	const glPoint<float> & pt3 = glPoint<float>(pos.mX, pos.mY + size.mHeight);
	const glPoint<float> & pt4 = glPoint<float>(pos.mX + size.mWidth, pos.mY + size.mHeight);
	if (solid) {
		if (paintTriangle(pt1, pt2, pt3, color, solid) &&
			paintTriangle(pt2, pt4, pt3, color, solid)) {
			return true;
		}
	}
	else {
		if (paintLine(pt1, pt2, color) &&
			paintLine(pt2, pt4, color) &&
			paintLine(pt4, pt3, color) &&
			paintLine(pt3, pt1, color)) {
			return true;
		}
	}
	return false;
}

void glBatchPrimitive::lockVertexBuffer(void) {
	if (mVertexBuffer.isAlready() && !mVertexList) {
		mVertexList = (glPrimitiveVertex *)mVertexBuffer.lock();
		if (mVertexList) {
			if (1.0f != mVertexList[0].rhw) {
				for (int i = 0; i < GL_MAX_PRIMITIVE_VERTEX; ++i) {
					mVertexList[i].rhw = 1.0f;
					mVertexList[i].z = 0.0f;
				}
			}
		}
	}
}

void glBatchPrimitive::unlockVertexBuffer(void) {
	if (mVertexBuffer.isAlready() && mVertexList) {
		if (mVertexBuffer.unlock()) {
			mVertexList = 0;
		}
	}
}
