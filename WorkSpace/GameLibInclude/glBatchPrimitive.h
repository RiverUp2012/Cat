
#pragma once

#include "glNonCopyable.h"
#include "glPoint.h"
#include "glSize.h"
#include "glVertexBuffer.h"
#include "glEnum.h"

struct glPrimitiveVertex;

//
// @brief 批量图元渲染类
//
class glBatchPrimitive : public glNonCopyable {
public:
	glBatchPrimitive();
	virtual ~glBatchPrimitive();
public:
	bool create(void);
	void destroy(void);
	bool flush(void);
	bool paintPoint(
		const glPoint<float> & pos,
		const unsigned int color);
	bool paintLine(
		const glPoint<float> & posStart,
		const glPoint<float> & posEnd,
		const unsigned int color);
	bool paintTriangle(
		const glPoint<float> & pt1,
		const glPoint<float> & pt2,
		const glPoint<float> & pt3,
		const unsigned int color,
		const bool solid);
	bool paintRectangle(
		const glPoint<float> & pos,
		const glSize<float> & size,
		const unsigned int color,
		const bool solid);
private:
	void lockVertexBuffer(void);
	void unlockVertexBuffer(void);
private:
	glVertexBuffer mVertexBuffer;
	glPrimitiveVertex * mVertexList;
	int mPrimitiveCount;
	glPrimitiveType mPrimitiveType;
};
