
//
// @file GameLibTemplate.h
// @brief Windows 游戏编程模板工具库
// @desc 用于辅助 Windows 操作系统下的游戏编程开发
// @author 李远兵
// @date 2019-09-12
//

#pragma once

#include <assert.h>
#include <malloc.h>
#include <new.h>

class glFile;
class glGameState;

//
// @brief 点模板类
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

//
// @brief 尺寸模板类
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

//
// @brief 矩形模板类
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

//
// @brief 字符串模板类
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
			copy(mString, other.getString(), stringLength);
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
				copy(mString, other.getString(), stringLength);
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
private:
	_U * mString;
	int mCapacity;
};

typedef glString<wchar_t> glStringW;
typedef glString<char> glStringA;

//
// @brief 链表模板类
//
template <typename _U>
class glList {
private:
	class glNode {
	public:
		glNode() {
			mNext = 0;
			mPrev = 0;
		}
		glNode(const _U & data) : mData(data) {
			mNext = 0;
			mPrev = 0;
		}
		virtual ~glNode() {

		}
	public:
		_U mData;
		glNode * mNext;
		glNode * mPrev;
	};
public:
	class glIterator {
		friend class glList;
	public:
		glIterator() {
			mNode = 0;
		}
		virtual ~glIterator() {

		}
	protected:
		glIterator(glNode * node) {
			mNode = node;
		}
	public:
		bool isValid(void) const {
			return mNode ? true : false;
		}
		const _U & getData(void) const {
			return mNode->mData;
		}
		void moveNext(void) {
			if (mNode) {
				mNode = mNode->mNext;
			}
		}
		void movePrev(void) {
			if (mNode) {
				mNode = mNode->mPrev;
			}
		}
	private:
		glNode * mNode;
	};
public:
	glList() {
		mNodeCount = 0;
		mHead = 0;
		mTail = 0;
	}
	glList(const glList & other) {
		mNodeCount = 0;
		mHead = 0;
		mTail = 0;
		glIterator iter = other.begin();
		while (iter.isValid()) {
			pushBack(iter.getData());
			iter.moveNext();
		}
	}
	virtual ~glList() {
		clear();
	}
public:
	void clear(void) {
		glNode * node = mHead;
		while (node) {
			glNode * nextNode = node->mNext;
			delete node;
			node = nextNode;
		}
		mNodeCount = 0;
		mHead = 0;
		mTail = 0;
	}
	bool pushBack(const _U & data) {
		glNode * newNode = new glNode(data);
		if (newNode) {
			if (!mNodeCount) {
				mHead = mTail = newNode;
			}
			else {
				newNode->mPrev = mTail;
				mTail->mNext = newNode;
				mTail = newNode;
			}
			++mNodeCount;
			return true;
		}
		return false;
	}
	bool pushFront(const _U & data) {
		glNode * newNode = new glNode(data);
		if (newNode) {
			if (!mNodeCount) {
				mHead = mTail = newNode;
			}
			else {
				newNode->mNext = mHead;
				mHead->mPrev = newNode;
				mHead = newNode;
			}
			++mNodeCount;
			return true;
		}
		return false;
	}
	bool popBack(void) {
		glNode * delNode = mTail;
		if (delNode) {
			mTail = mTail->mPrev;
			if (mTail) {
				mTail->mNext = 0;
			}
			delete delNode;
			delNode = 0;
			--mNodeCount;
			if (mNodeCount <= 0) {
				mHead = mTail = 0;
			}
			return true;
		}
		return false;
	}
	bool popFront(void) {
		glNode * delNode = mHead;
		if (delNode) {
			mHead = mHead->mNext;
			if (mHead) {
				mHead->mPrev = 0;
			}
			delete delNode;
			delNode = 0;
			--mNodeCount;
			if (mNodeCount <= 0) {
				mHead = mTail = 0;
			}
			return true;
		}
		return false;
	}
	int getNodeCount(void) const {
		return mNodeCount;
	}
	glIterator begin(void) const {
		return glIterator(mHead);
	}
	glIterator end(void) const {
		return glIterator(mTail);
	}
	bool insertBefore(glIterator & pos, const _U & data) {
		assert(contain(data));
		glNode * node = pos.mNode;
		if (node) {
			glNode * newNode = new glNode(data);
			if (newNode) {
				glNode * prevNode = node->mPrev;
				if (prevNode) {
					prevNode->mNext = newNode;
				}
				newNode->mPrev = prevNode;
				newNode->mNext = node;
				node->mPrev = newNode;
				if (mHead == node) {
					mHead = newNode;
				}
				++mNodeCount;
				return true;
			}
		}
		return false;
	}
	bool insertAfter(glIterator & pos, const _U & data)	{
		assert(contain(data));
		glNode * node = pos.mNode;
		if (node) {
			glNode * newNode = new glNode(data);
			if (newNode) {
				glNode * nextNode = node->mNext;
				if (nextNode) {
					nextNode->mPrev = newNode;
				}
				newNode->mNext = nextNode;
				newNode->mPrev = node;
				node->mNext = newNode;
				if (mTail == node) {
					mTail = newNode;
				}
				++mNodeCount;
				return true;
			}
		}
		return false;
	}
	bool remove(glIterator & pos) {
		assert(contain(pos));
		glNode * delNode = pos.mNode;
		if (delNode) {
			glNode * prevNode = delNode->mPrev;
			glNode * nextNode = delNode->mNext;
			if (prevNode) {
				prevNode->mNext = nextNode;
			}
			if (nextNode) {
				nextNode->mPrev = prevNode;
			}
			if (mHead == delNode) {
				mHead = nextNode;
				if (mHead) {
					mHead->mPrev = 0;
				}
			}
			else if (mTail == delNode) {
				mTail = prevNode;
				if (mTail) {
					mTail->mNext = 0;
				}
			}
			pos.mNode = nextNode;
			delete delNode;
			delNode = 0;
			--mNodeCount;
			if (mNodeCount <= 0) {
				mHead = mTail = 0;
			}
			return true;
		}
		return false;
	}
	glIterator find(const _U & data) const {
		glNode * node = mHead;
		while (node) {
			if (data == node->mData) {
				return glIterator(node);
			}
			node = node->mNext;
		}
		return glIterator();
	}
	bool remove(const _U & data) {
		assert(contain(data));
		glIterator iter = find(data);
		if (iter.isValid()) {
			return remove(iter);
		}
		return false;
	}
	bool contain(const _U & data) const {
		return find(data).isValid();
	}
	bool contain(const glIterator & iter) const {
		return iter.isValid() && contain(iter.getData());
	}
public:
	glList & operator = (const glList & other) {
		if (this != &other) {
			clear();
			glIterator iter = other.begin();
			while (iter.isValid()) {
				pushBack(iter.getData());
				iter.moveNext();
			}
		}
		return *this;
	}
private:
	int mNodeCount;
	glNode * mHead;
	glNode * mTail;
};

//
// @brief 数组模板类
//
template <typename _U>
class glArray {
public:
	static const int defaultGrowUnits = 16;
public:
	glArray() {
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
	}
	glArray(const int capacity) {
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
		resize(capacity);
	}
	glArray(const int capacity, const _U & data) {
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
		resize(capacity, data);
	}
	glArray(const glArray & other) {
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
		if (resize(other.getCapacity())) {
			for (int i = 0; i < other.getCapacity(); ++i) {
				mArray[i] = other.getAt(i);
			}
		}
	}
	virtual ~glArray() {
		clear();
	}
public:
	void clear(void) {
		if (mArray) {
			for (int i = 0; i < mCapacity; ++i) {
				mArray[i].~_U();
			}
			free(mArray);
		}
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
	}
	bool resize(const int capacity) {
		clear();
		if (capacity > 0) {
			mArray = (_U *)malloc(sizeof(_U)* capacity);
			if (mArray) {
				for (int i = 0; i < capacity; ++i) {
					new (&mArray[i]) _U;
				}
				mCapacity = capacity;
				return true;
			}
		}
		return false;
	}
	bool resize(const int capacity, const _U & data) {
		if (resize(capacity)) {
			for (int i = 0; i < capacity; ++i) {
				mArray[i] = data;
			}
			return true;
		}
		return false;
	}
	bool add(const _U & data) {
		const int newCapacity = mCapacity + defaultGrowUnits;
		_U * newArray = 0;
		if (!mArray || mItems >= mCapacity) {
			newArray = (_U *)realloc(mArray, sizeof(_U) * newCapacity);
			if (newArray) {
				for (int i = mItems; i < newCapacity; ++i) {
					new &(newCapacity[i]) _U;
				}
				mArray = newArray;
				mCapacity = newCapacity;
			}
		}
		if (mArray && mItems < mCapacity) {
			mArray[mItems] = data;
			++mItems;
			return true;
		}
		return false;
	}
	const _U * getArray(void) const {
		return mArray;
	}
	int getCapacity(void) const {
		return mCapacity;
	}
	int getItems(void) const {
		return mItems;
	}
	const _U & getAt(const int index) const {
		assert(mArray && index >= 0 && index < mCapacity);
		return mArray[index];
	}
	_U & getAtRef(const int index) {
		assert(mArray && index >= 0 && index < mCapacity);
		return mArray[index];
	}
	bool setAt(const int index, const _U & data) {
		if (mArray && index >= 0 && index < mCapacity) {
			mArray[index] = data;
			return true;
		}
		return false;
	}
private:
	_U * mArray;
	int mCapacity;
	int mItems;
	int mGrowUnits;
};

//
// @brief 资源池模板类
//
template <typename _U>
class glResourcePool {
private:
	struct glItem {
		_U mResource;
		int mID;
		bool mInUse;
	};
public:
	glResourcePool(const int capacity = 64) {
		if (capacity > 0) {
			if (mItemArray.resize(capacity)) {
				for (int i = 0; i < mItemArray.getCapacity(); ++i) {
					glItem & item = mItemArray.getAtRef(i);
					item.mID = 0;
					item.mInUse = false;
				}
			}
		}
		mNextItemID = 1;
	}
	virtual ~glResourcePool() {
		mItemArray.clear();
	}
public:
	bool insertResource(const _U & resource, int & id) {
		if (mNextItemID < 0xFFFFFFFF) {
			for (int i = 0; i < mItemArray.getCapacity(); ++i) {
				glItem & item = mItemArray.getAtRef(i);
				if (!item.mInUse) {
					item.mResource = resource;
					item.mID = mNextItemID;
					item.mInUse = true;
					++mNextItemID;
					id = item.mID;
					return true;
				}
			}
		}
		return false;
	}
	bool getResource(const int id, _U & resource, const bool markResourceUnuse = true) const {
		for (int i = 0; i < mItemArray.getCapacity(); ++i) {
			const glItem & item = mItemArray.getAt(i);
			if (item.mInUse && id == item.mID) {
				resource = item.mResource;
				if (markResourceUnuse) {
					item.mInUse = false;
					item.mID = 0;
				}
				return true;
			}
		}
		return false;
	}
private:
	glArray<glItem> mItemArray;
	int mNextItemID;
};

//
// @brief 从文件中读取数据
//
template <typename _U>
bool glReadFile(glFile & file, _U & value) {
	return file.read(&value, sizeof(_U));
}

//
// @brief 将数据写入文件
//
template <typename _U>
bool glWriteFile(glFile & file, const _U & value) {
	return file.write(&value, sizeof(_U));
}

//
// @brief 压入新的游戏状态
//
template <typename _U>
void glPushNewGameState(void) {
	glEngine * engine = glEngine::get();
	if (engine) {
		glGameState * gameState = new _U();
		if (gameState) {
			engine->pushGameState(gameState);
			gameState->release();
			gameState = 0;
		}
	}
}
