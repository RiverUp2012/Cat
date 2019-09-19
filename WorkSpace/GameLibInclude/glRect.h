
#pragma once

#include "glPoint.h"
#include "glSize.h"

//
// @brief ¾ØÐÎÄ£°åÀà
//
template <typename _U>
class glRect : public glPoint<_U>, public glSize<_U> {
public:
	glRect() {

	}
	glRect(const _U & x, const _U & y, const _U & width, const _U & height) :
		glPoint(x, y),
		glSize(width, height) {

	}
	glRect(const glPoint<_U> & pos, const glSize<_U> & size) :
		glPoint(pos),
		glSize(size) {

	}
	glRect(const glRect & other) :
		glPoint(other.mX, other.mY),
		glSize(other.mWidth, other.mHeight) {

	}
	virtual ~glRect() {

	}
public:
	_U getRight(void) const {
		return mX + mWidth;
	}
	_U getBottom(void) const {
		return mY + mHeight;
	}
	bool containPt(const glPoint<_U> & pt) const {
		if (pt.mX < mX) return false;
		if (pt.mY < mY) return false;
		if (pt.mX > getRight()) return false;
		if (pt.mY > getBottom()) return false;

		return true;
	}
};
