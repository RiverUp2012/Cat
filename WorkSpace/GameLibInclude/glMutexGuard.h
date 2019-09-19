
#pragma once

#include "glNonCopyable.h"

class glMutex;

//
// @brief 代码域互斥哨兵
// @desc 在生命期内自动同步线程资源
//
class glMutexGuard : public glNonCopyable {
public:
	glMutexGuard(glMutex * mutex);
	virtual ~glMutexGuard();
private:
	glMutex * mMutex = 0;
};
