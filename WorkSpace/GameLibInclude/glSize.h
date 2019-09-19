
#pragma once

//
// @brief ≥ﬂ¥Áƒ£∞Â¿‡
//
template <typename _U>
class glSize {
public:
	glSize() {
		mWidth = 0;
		mHeight = 0;
	}
	glSize(const _U & width, const _U & height) {
		mWidth = width;
		mHeight = height;
	}
	template <typename _V>
	glSize(const _V & width, const _V & height) {
		mWidth = (_U)width;
		mHeight = (_U)height;
	}
	glSize(const glSize & other) {
		mWidth = other.mWidth;
		mHeight = other.mHeight;
	}
	template <typename _V>
	glSize(const glSize<_V> & other) {
		mWidth = (_U)other.mWidth;
		mHeight = (_U)other.mHeight;
	}
	virtual ~glSize() {

	}
public:
	_U mWidth;
	_U mHeight;
};
