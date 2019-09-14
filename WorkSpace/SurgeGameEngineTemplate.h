
#pragma once

#include <assert.h>
#include <malloc.h>
#include <new.h>

class sgeFile;
class sgeGameState;

template <typename _U>
class sgePoint
{
public:

	sgePoint()
	{
		mX = 0;
		mY = 0;
	}

	sgePoint(const _U & x, const _U & y)
	{
		mX = x;
		mY = y;
	}

	template <typename _V>
	sgePoint(const _V & x, const _V & y)
	{
		mX = (_U)x;
		mY = (_U)y;
	}

	sgePoint(const sgePoint & other)
	{
		mX = other.mX;
		mY = other.mY;
	}

	template <typename _V>
	sgePoint(const sgePoint<_V> & other)
	{
		mX = (_U)other.mX;
		mY = (_U)other.mY;
	}

	virtual ~sgePoint()
	{

	}

public:

	sgePoint & operator += (const sgePoint & other)
	{
		mX += other.mX;
		mY += other.mY;

		return *this;
	}

	sgePoint & operator -= (const sgePoint & other)
	{
		mX -= other.mX;
		mY -= other.mY;

		return *this;
	}

	sgePoint operator + (const sgePoint & other) const
	{
		return sgePoint(mX + other.mX, mY + other.mY);
	}

	sgePoint operator - (const sgePoint & other) const
	{
		return sgePoint(mX - other.mX, mY - other.mY);
	}

	bool operator == (const sgePoint<_U> & other) const
	{
		return mX == other.mX && mY == other.mY;
	}

	bool operator != (const sgePoint<_U> & other) const
	{
		return mX != other.mX || mY != other.mY;
	}

public:

	_U mX;
	_U mY;
};

template <typename _U>
class sgeSize
{
public:

	sgeSize()
	{
		mWidth = 0;
		mHeight = 0;
	}

	sgeSize(const _U & width, const _U & height)
	{
		mWidth = width;
		mHeight = height;
	}

	template <typename _V>
	sgeSize(const _V & width, const _V & height)
	{
		mWidth = (_U)width;
		mHeight = (_U)height;
	}

	sgeSize(const sgeSize & other)
	{
		mWidth = other.mWidth;
		mHeight = other.mHeight;
	}

	template <typename _V>
	sgeSize(const sgeSize<_V> & other)
	{
		mWidth = (_U)other.mWidth;
		mHeight = (_U)other.mHeight;
	}

	virtual ~sgeSize()
	{

	}

public:

	_U mWidth;
	_U mHeight;
};

template <typename _U>
class sgeRect : public sgePoint<_U>, public sgeSize<_U>
{
public:

	sgeRect()
	{

	}

	sgeRect(const _U & x, const _U & y, const _U & width, const _U & height) :
		sgePoint(x, y),
		sgeSize(width, height)
	{

	}

	sgeRect(const sgePoint<_U> & pos, const sgeSize<_U> & size) :
		sgePoint(pos),
		sgeSize(size)
	{

	}

	sgeRect(const sgeRect & other) :
		sgePoint(other.mX, other.mY),
		sgeSize(other.mWidth, other.mHeight)
	{

	}

	virtual ~sgeRect()
	{

	}

public:

	_U getRight(void) const
	{
		return mX + mWidth;
	}

	_U getBottom(void) const
	{
		return mY + mHeight;
	}

	bool containPt(const sgePoint<_U> & pt) const
	{
		if (pt.mX < mX) return false;
		if (pt.mY < mY) return false;
		if (pt.mX > getRight()) return false;
		if (pt.mY > getBottom()) return false;

		return true;
	}
};

template <typename _U>
class sgeString
{
public:

	static int getLength(const _U string[])
	{
		int length = 0;

		if (string)
		{
			while (string[length])
			{
				++length;
			}
		}

		return length;
	}

	static void copy(_U * destString, const _U * srcString, const int charsToCopy = 0)
	{
		const int charsToCopyTemp = (charsToCopy <= 0) ? getLength(srcString) : charsToCopy;

		if (destString && srcString)
		{
			for (int i = 0; i < charsToCopyTemp; ++i)
			{
				destString[i] = srcString[i];
			}

			destString[charsToCopyTemp] = getNullChar();
		}
	}

	static unsigned int getCharSize(void)
	{
		return sizeof(_U);
	}

	static _U getNullChar(void)
	{
		return 0;
	}

public:

	sgeString()
	{
		mString = 0;
		mCapacity = 0;
	}

	sgeString(const _U string[])
	{
		mString = 0;
		mCapacity = 0;

		const int stringLength = getLength(string);
		if (stringLength > 0 && resize(stringLength + 1))
		{
			copy(mString, string, stringLength);
		}
	}

	sgeString(const sgeString & other)
	{
		mString = 0;
		mCapacity = 0;

		const int stringLength = other.getLength();
		if (stringLength > 0 && resize(stringLength + 1))
		{
			copy(mString, other.getString(), stringLength);
		}
	}

	virtual ~sgeString()
	{
		clear();
	}

public:

	void clear(void)
	{
		if (mString)
		{
			free(mString);
			mString = 0;
		}

		mCapacity = 0;
	}

	bool resize(const int capacity)
	{
		clear();

		if (capacity > 0)
		{
			mString = (_U *)malloc(getCharSize() * capacity);
			if (mString)
			{
				mString[0] = getNullChar();
				mCapacity = capacity;

				return true;
			}
		}

		return false;
	}

	_U * getBuffer(void) const
	{
		return mString;
	}

	const _U * getString(void) const
	{
		return mString;
	}

	int getLength(void) const
	{
		return getLength(mString);
	}

	int getCapacity(void) const
	{
		return mCapacity;
	}

	bool setAt(const int index, const _U charToSet)
	{
		if (mString && index >= 0 && index < mCapacity)
		{
			mString[index] = charToSet;

			return true;
		}

		return false;
	}

	const _U & getAt(const int index) const
	{
		assert(mString && index >= 0 && index < mCapacity);

		return mString[index];
	}

public:

	sgeString & operator = (const _U string[])
	{
		if (mString != string)
		{
			const int stringLength = getLength(string);
			if (stringLength > 0 && resize(stringLength + 1))
			{
				copy(mString, string, stringLength);
			}
		}

		return *this;
	}

	sgeString & operator = (const sgeString & other)
	{
		if (this != &other)
		{
			const int stringLength = other.getLength();
			if (stringLength > 0 && resize(stringLength + 1))
			{
				copy(mString, other.getString(), stringLength);
			}
		}

		return *this;
	}

	sgeString operator + (const _U string[]) const
	{
		sgeString ret;
		int stringLength = string ? getLength(string) : 0;
		int thisStringLength = getLength();

		if (ret.resize(thisStringLength + stringLength + 1))
		{
			if (getString())
			{
				copy(ret.getBuffer(), getString(), thisStringLength);
				ret.setAt(thisStringLength, 0);
			}

			if (string)
			{
				copy(&(ret.getBuffer()[thisStringLength]), string, stringLength);
				ret.setAt(thisStringLength + stringLength, 0);
			}
		}

		return ret;
	}

	sgeString operator + (const sgeString & other) const
	{
		sgeString ret;
		int stringLength = other.getLength();
		int thisStringLength = getLength();

		if (ret.resize(thisStringLength + stringLength + 1))
		{
			if (getString())
			{
				copy(ret.getBuffer(), getString(), thisStringLength);
				ret.setAt(thisStringLength, 0);
			}

			if (other.getString())
			{
				copy(&(ret.getBuffer()[thisStringLength]), other.getString(), stringLength);
				ret.setAt(thisStringLength + stringLength, 0);
			}
		}

		return ret;
	}

private:

	_U * mString;
	int mCapacity;
};

typedef sgeString<wchar_t> sgeStringW;
typedef sgeString<char> sgeStringA;

template <typename _U>
class sgeList
{
private:

	class sgeNode
	{
	public:

		sgeNode()
		{
			mNext = 0;
			mPrev = 0;
		}

		sgeNode(const _U & data) : mData(data)
		{
			mNext = 0;
			mPrev = 0;
		}

		virtual ~sgeNode()
		{

		}

	public:

		_U mData;
		sgeNode * mNext;
		sgeNode * mPrev;
	};

public:

	class sgeIterator
	{
		friend class sgeList;

	public:

		sgeIterator()
		{
			mNode = 0;
		}

		virtual ~sgeIterator()
		{

		}

	protected:

		sgeIterator(sgeNode * node)
		{
			mNode = node;
		}

	public:

		bool isValid(void) const
		{
			return mNode ? true : false;
		}

		const _U & getData(void) const
		{
			return mNode->mData;
		}

		void moveNext(void)
		{
			if (mNode)
			{
				mNode = mNode->mNext;
			}
		}

		void movePrev(void)
		{
			if (mNode)
			{
				mNode = mNode->mPrev;
			}
		}

	private:

		sgeNode * mNode;
	};

public:

	sgeList()
	{
		mNodeCount = 0;
		mHead = 0;
		mTail = 0;
	}

	sgeList(const sgeList & other)
	{
		mNodeCount = 0;
		mHead = 0;
		mTail = 0;

		sgeIterator iter = other.begin();
		while (iter.isValid())
		{
			pushBack(iter.getData());
			iter.moveNext();
		}
	}

	virtual ~sgeList()
	{
		clear();
	}

public:

	void clear(void)
	{
		sgeNode * node = mHead;
		while (node)
		{
			sgeNode * nextNode = node->mNext;
			delete node;
			node = nextNode;
		}

		mNodeCount = 0;
		mHead = 0;
		mTail = 0;
	}

	bool pushBack(const _U & data)
	{
		sgeNode * newNode = new sgeNode(data);
		if (newNode)
		{
			if (!mNodeCount)
			{
				mHead = mTail = newNode;
			}
			else
			{
				newNode->mPrev = mTail;
				mTail->mNext = newNode;
				mTail = newNode;
			}

			++mNodeCount;

			return true;
		}

		return false;
	}

	bool pushFront(const _U & data)
	{
		sgeNode * newNode = new sgeNode(data);
		if (newNode)
		{
			if (!mNodeCount)
			{
				mHead = mTail = newNode;
			}
			else
			{
				newNode->mNext = mHead;
				mHead->mPrev = newNode;
				mHead = newNode;
			}

			++mNodeCount;

			return true;
		}

		return false;
	}

	bool popBack(void)
	{
		sgeNode * delNode = mTail;
		if (delNode)
		{
			mTail = mTail->mPrev;
			if (mTail)
			{
				mTail->mNext = 0;
			}

			delete delNode;
			delNode = 0;

			--mNodeCount;
			if (mNodeCount <= 0)
			{
				mHead = mTail = 0;
			}

			return true;
		}

		return false;
	}

	bool popFront(void)
	{
		sgeNode * delNode = mHead;
		if (delNode)
		{
			mHead = mHead->mNext;
			if (mHead)
			{
				mHead->mPrev = 0;
			}

			delete delNode;
			delNode = 0;

			--mNodeCount;
			if (mNodeCount <= 0)
			{
				mHead = mTail = 0;
			}

			return true;
		}

		return false;
	}

	int getNodeCount(void) const
	{
		return mNodeCount;
	}

	sgeIterator begin(void) const
	{
		return sgeIterator(mHead);
	}

	sgeIterator end(void) const
	{
		return sgeIterator(mTail);
	}

	bool insertBefore(sgeIterator & pos, const _U & data)
	{
		assert(contain(data));

		sgeNode * node = pos.mNode;
		if (node)
		{
			sgeNode * newNode = new sgeNode(data);
			if (newNode)
			{
				sgeNode * prevNode = node->mPrev;
				if (prevNode)
				{
					prevNode->mNext = newNode;
				}

				newNode->mPrev = prevNode;
				newNode->mNext = node;
				node->mPrev = newNode;

				if (mHead == node)
				{
					mHead = newNode;
				}

				++mNodeCount;

				return true;
			}
		}

		return false;
	}

	bool insertAfter(sgeIterator & pos, const _U & data)
	{
		assert(contain(data));

		sgeNode * node = pos.mNode;
		if (node)
		{
			sgeNode * newNode = new sgeNode(data);
			if (newNode)
			{
				sgeNode * nextNode = node->mNext;
				if (nextNode)
				{
					nextNode->mPrev = newNode;
				}

				newNode->mNext = nextNode;
				newNode->mPrev = node;
				node->mNext = newNode;

				if (mTail == node)
				{
					mTail = newNode;
				}

				++mNodeCount;

				return true;
			}
		}

		return false;
	}

	bool remove(sgeIterator & pos)
	{
		assert(contain(pos));

		sgeNode * delNode = pos.mNode;
		if (delNode)
		{
			sgeNode * prevNode = delNode->mPrev;
			sgeNode * nextNode = delNode->mNext;

			if (prevNode)
			{
				prevNode->mNext = nextNode;
			}

			if (nextNode)
			{
				nextNode->mPrev = prevNode;
			}

			if (mHead == delNode)
			{
				mHead = nextNode;
				if (mHead)
				{
					mHead->mPrev = 0;
				}
			}
			else if (mTail == delNode)
			{
				mTail = prevNode;
				if (mTail)
				{
					mTail->mNext = 0;
				}
			}

			pos.mNode = nextNode;

			delete delNode;
			delNode = 0;

			--mNodeCount;
			if (mNodeCount <= 0)
			{
				mHead = mTail = 0;
			}

			return true;
		}

		return false;
	}

	sgeIterator find(const _U & data) const
	{
		sgeNode * node = mHead;
		while (node)
		{
			if (data == node->mData)
			{
				return sgeIterator(node);
			}

			node = node->mNext;
		}

		return sgeIterator();
	}

	bool remove(const _U & data)
	{
		assert(contain(data));

		sgeIterator iter = find(data);
		if (iter.isValid())
		{
			return remove(iter);
		}

		return false;
	}

	bool contain(const _U & data) const
	{
		return find(data).isValid();
	}

	bool contain(const sgeIterator & iter) const
	{
		return iter.isValid() && contain(iter.getData());
	}

public:

	sgeList & operator = (const sgeList & other)
	{
		if (this != &other)
		{
			clear();

			sgeIterator iter = other.begin();
			while (iter.isValid())
			{
				pushBack(iter.getData());
				iter.moveNext();
			}
		}

		return *this;
	}

private:

	int mNodeCount;
	sgeNode * mHead;
	sgeNode * mTail;
};

template <typename _U>
class sgeArray
{
public:

	static const int defaultGrowUnits = 16;

public:

	sgeArray()
	{
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
	}

	sgeArray(const int capacity)
	{
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;

		resize(capacity);
	}

	sgeArray(const int capacity, const _U & data)
	{
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;

		resize(capacity, data);
	}

	sgeArray(const sgeArray & other)
	{
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;

		if (resize(other.getCapacity()))
		{
			for (int i = 0; i < other.getCapacity(); ++i)
			{
				mArray[i] = other.getAt(i);
			}
		}
	}

	virtual ~sgeArray()
	{
		clear();
	}

public:

	void clear(void)
	{
		if (mArray)
		{
			for (int i = 0; i < mCapacity; ++i)
			{
				mArray[i].~_U();
			}

			free(mArray);
		}

		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
	}

	bool resize(const int capacity)
	{
		clear();

		if (capacity > 0)
		{
			mArray = (_U *)malloc(sizeof(_U)* capacity);
			if (mArray)
			{
				for (int i = 0; i < capacity; ++i)
				{
					new (&mArray[i]) _U;
				}

				mCapacity = capacity;

				return true;
			}
		}

		return false;
	}

	bool resize(const int capacity, const _U & data)
	{
		if (resize(capacity))
		{
			for (int i = 0; i < capacity; ++i)
			{
				mArray[i] = data;
			}

			return true;
		}

		return false;
	}

	bool add(const _U & data)
	{
		const int newCapacity = mCapacity + defaultGrowUnits;
		_U * newArray = 0;

		if (!mArray || mItems >= mCapacity)
		{
			newArray = (_U *)realloc(mArray, sizeof(_U) * newCapacity);
			if (newArray)
			{
				for (int i = mItems; i < newCapacity; ++i)
				{
					new &(newCapacity[i]) _U;
				}

				mArray = newArray;
				mCapacity = newCapacity;
			}
		}

		if (mArray && mItems < mCapacity)
		{
			mArray[mItems] = data;
			++mItems;

			return true;
		}

		return false;
	}

	const _U * getArray(void) const
	{
		return mArray;
	}

	int getCapacity(void) const
	{
		return mCapacity;
	}

	int getItems(void) const
	{
		return mItems;
	}

	const _U & getAt(const int index) const
	{
		assert(mArray && index >= 0 && index < mCapacity);

		return mArray[index];
	}

	_U & getAtRef(const int index)
	{
		assert(mArray && index >= 0 && index < mCapacity);

		return mArray[index];
	}

	bool setAt(const int index, const _U & data)
	{
		if (mArray && index >= 0 && index < mCapacity)
		{
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

template <typename _U>
bool sgeReadFile(sgeFile & file, _U & value)
{
	return file.read(&value, sizeof(_U));
}

template <typename _U>
bool sgeWriteFile(sgeFile & file, const _U & value)
{
	return file.write(&value, sizeof(_U));
}

template <typename _U>
void sgePushNewGameState(void)
{
	sgeEngine * engine = sgeEngine::get();
	if (engine)
	{
		sgeGameState * gameState = new _U();
		if (gameState)
		{
			engine->pushGameState(gameState);

			gameState->release();
			gameState = 0;
		}
	}
}
