
#pragma once

#include "glNonCopyable.h"

//
// @brief 互斥类
// @desc 用于线程资源同步
//
class glMutex : public glNonCopyable {
public:
	glMutex();
	virtual ~glMutex();
public:
	void lock(void);
	void unlock(void);
private:
	void * mCriticalSection;
};
