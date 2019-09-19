
#pragma once

//
// @brief µ„ƒ£∞Â¿‡
//
template <typename _U>
class glPoint {
public:
	glPoint() {
		mX = 0;
		mY = 0;
	}
	glPoint(const _U & x, const _U & y) {
		mX = x;
		mY = y;
	}
	template <typename _V>
	glPoint(const _V & x, const _V & y) {
		mX = (_U)x;
		mY = (_U)y;
	}
	glPoint(const glPoint & other) {
		mX = other.mX;
		mY = other.mY;
	}
	template <typename _V>
	glPoint(const glPoint<_V> & other) {
		mX = (_U)other.mX;
		mY = (_U)other.mY;
	}
	virtual ~glPoint() {

	}
public:
	glPoint & operator += (const glPoint & other) {
		mX += other.mX;
		mY += other.mY;
		return *this;
	}
	glPoint & operator -= (const glPoint & other) {
		mX -= other.mX;
		mY -= other.mY;
		return *this;
	}
	glPoint operator + (const glPoint & other) const {
		return glPoint(mX + other.mX, mY + other.mY);
	}
	glPoint operator - (const glPoint & other) const {
		return glPoint(mX - other.mX, mY - other.mY);
	}
	bool operator == (const glPoint<_U> & other) const {
		return mX == other.mX && mY == other.mY;
	}
	bool operator != (const glPoint<_U> & other) const {
		return mX != other.mX || mY != other.mY;
	}
public:
	_U mX;
	_U mY;
};
