
#pragma once

#include "glException.h"

//
// @brief ¡¥±Ìƒ£∞Â¿‡
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
			if (!mNode) {
				throw glException(L"bad iterator");
			}
			return mNode->mData;
		}
		_U & getDataRef(void) {
			if (!mNode) {
				throw glException(L"bad iterator");
			}
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
	void pushBack(const _U & data) {
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
		}
		else {
			throw glException(L"bad new");
		}
	}
	void pushFront(const _U & data) {
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
		}
		else {
			throw glException(L"bad new");
		}
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
#if defined DEBUG || defined _DEBUG
		if (!contain(data)) {
			throw glException(L"bad iterator");
		}
#endif
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
			else {
				throw glException(L"bad new");
			}
		}
		return false;
	}
	bool insertAfter(glIterator & pos, const _U & data)	{
#if defined DEBUG || defined _DEBUG
		if (!contain(data)) {
			throw glException(L"bad iterator");
		}
#endif
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
			else {
				throw glException(L"bad new");
			}
		}
		return false;
	}
	bool remove(glIterator & pos) {
#if defined DEBUG || defined _DEBUG
		if (!contain(pos)) {
			throw glException(L"bad iterator");
		}
#endif
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
#if defined DEBUG || defined _DEBUG
		if (!contain(data)) {
			throw glException(L"bad iterator");
		}
#endif
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
