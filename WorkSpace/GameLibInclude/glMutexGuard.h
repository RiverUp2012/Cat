
#pragma once

#include "glNonCopyable.h"

class glMutex;

//
// @brief �����򻥳��ڱ�
// @desc �����������Զ�ͬ���߳���Դ
//
class glMutexGuard : public glNonCopyable {
public:
	glMutexGuard(glMutex * mutex);
	virtual ~glMutexGuard();
private:
	glMutex * mMutex = 0;
};
