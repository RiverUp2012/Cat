
#pragma once

#include <malloc.h>
#include <assert.h>

//
// @brief ×Ö·û´®Ä£°åÀà
//
template <typename _U>
class glString {
public:
	static int getLength(const _U string[]) {
		int length = 0;
		if (string) {
			while (string[length]) {
				++length;
			}
		}
		return length;
	}
	static void copy(_U * destString, const _U * srcString, const int charsToCopy = 0) {
		const int charsToCopyTemp = (charsToCopy <= 0) ? getLength(srcString) : charsToCopy;
		if (destString && srcString) {
			for (int i = 0; i < charsToCopyTemp; ++i) {
				destString[i] = srcString[i];
			}
			destString[charsToCopyTemp] = getNullChar();
		}
	}
	static unsigned int getCharSize(void) {
		return sizeof(_U);
	}
	static _U getNullChar(void) {
		return 0;
	}
public:
	glString() {
		mString = 0;
		mCapacity = 0;
	}
	glString(const _U string[]) {
		mString = 0;
		mCapacity = 0;
		const int stringLength = getLength(string);
		if (stringLength > 0 && resize(stringLength + 1)) {
			copy(mString, string, stringLength);
		}
	}
	glString(const glString & other) {
		mString = 0;
		mCapacity = 0;
		const int stringLength = other.getLength();
		if (stringLength > 0 && resize(stringLength + 1)) {
			copy(mString, other, stringLength);
		}
	}
	virtual ~glString() {
		clear();
	}
public:
	void clear(void) {
		if (mString) {
			free(mString);
			mString = 0;
		}
		mCapacity = 0;
	}
	bool resize(const int capacity) {
		clear();
		if (capacity > 0) {
			mString = (_U *)malloc(getCharSize() * capacity);
			if (mString) {
				mString[0] = getNullChar();
				mCapacity = capacity;
				return true;
			}
		}
		return false;
	}
	_U * getBuffer(void) const {
		return mString;
	}
	const _U * getString(void) const {
		static const _U nullString[1] = { getNullChar() };
		return mString ? mString : nullString;
	}
	int getLength(void) const {
		return getLength(mString);
	}
	int getCapacity(void) const {
		return mCapacity;
	}
	bool setAt(const int index, const _U charToSet) {
		if (mString && index >= 0 && index < mCapacity) {
			mString[index] = charToSet;
			return true;
		}
		return false;
	}
	const _U & getAt(const int index) const {
		assert(mString && index >= 0 && index < mCapacity);
		return mString[index];
	}
	_U & getAtRef(const int index) {
		assert(mString && index >= 0 && index < mCapacity);
		return mString[index];
	}
	bool sub(const int offset, const int length, glString & subString) const {
		const int stringLength = getLength();
		if (offset + length <= stringLength && subString.resize(length + 1)) {
			copy(subString.getBuffer(), &(mString[offset]), length);
			subString.setAt(length, 0);
			return true;
		}
		return false;
	}
	bool left(const int length, glString & subString) const {
		return sub(0, length, subString);
	}
	bool right(const int length, glString & subString) const {
		return sub(getLength() - length, length, subString);
	}
	void replaceChar(const _U & srcChar, const _U & destChar) {
		if (mString) {
			for (int i = 0; i < getLength(); ++i) {
				if (srcChar == mString[i]) {
					mString[i] = destChar;
				}
			}
		}
	}
public:
	glString & operator = (const _U string[]) {
		if (mString != string) {
			const int stringLength = getLength(string);
			if (stringLength > 0 && resize(stringLength + 1)) {
				copy(mString, string, stringLength);
			}
		}
		return *this;
	}
	glString & operator = (const glString & other) {
		if (this != &other) {
			const int stringLength = other.getLength();
			if (stringLength > 0 && resize(stringLength + 1)) {
				copy(mString, other, stringLength);
			}
		}
		return *this;
	}
	glString operator + (const _U string[]) const {
		glString ret;
		int stringLength = string ? getLength(string) : 0;
		int thisStringLength = getLength();
		if (ret.resize(thisStringLength + stringLength + 1)) {
			if (getString()) {
				copy(ret.getBuffer(), getString(), thisStringLength);
				ret.setAt(thisStringLength, 0);
			}
			if (string) {
				copy(&(ret.getBuffer()[thisStringLength]), string, stringLength);
				ret.setAt(thisStringLength + stringLength, 0);
			}
		}
		return ret;
	}
	glString operator + (const glString & other) const {
		glString ret;
		int stringLength = other.getLength();
		int thisStringLength = getLength();
		if (ret.resize(thisStringLength + stringLength + 1)) {
			if (getString()) {
				copy(ret.getBuffer(), getString(), thisStringLength);
				ret.setAt(thisStringLength, 0);
			}
			if (other.getString()) {
				copy(&(ret.getBuffer()[thisStringLength]), other.getString(), stringLength);
				ret.setAt(thisStringLength + stringLength, 0);
			}
		}
		return ret;
	}
	glString & operator += (const _U string[]) {
		int stringLength = string ? getLength(string) : 0;
		int thisStringLength = getLength();
		_U * newString = 0;
		if (thisStringLength + stringLength > 0) {
			newString = new _U[thisStringLength + stringLength + 1];
			if (newString) {
				if (getString()) {
					copy(newString, getString(), thisStringLength);
					newString[thisStringLength] = 0;
				}
				if (string) {
					copy(&(newString[thisStringLength]), string, stringLength);
					newString[thisStringLength + stringLength] = 0;
				}
				clear();
				mString = newString;
				mCapacity = thisStringLength + stringLength + 1;
			}
		}
		return *this;
	}
	glString & operator += (const glString & other) {
		int stringLength = other.getLength();
		int thisStringLength = getLength();
		_U * newString = 0;
		if (thisStringLength + stringLength > 0) {
			newString = new _U[thisStringLength + stringLength + 1];
			if (newString) {
				if (getString()) {
					copy(newString, getString(), thisStringLength);
					newString[thisStringLength] = 0;
				}
				if (other.getString()) {
					copy(&(newString[thisStringLength]), other.getString(), stringLength);
					newString[thisStringLength + stringLength] = 0;
				}
				clear();
				mString = newString;
				mCapacity = thisStringLength + stringLength + 1;
			}
		}
		return *this;
	}
	operator const _U * (void) const {
		return getString();
	}
private:
	_U * mString;
	int mCapacity;
};

typedef glString<wchar_t> glStringW;
typedef glString<char> glStringA;
