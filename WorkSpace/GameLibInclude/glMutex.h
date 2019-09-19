
#pragma once

#include "glNonCopyable.h"

//
// @brief ������
// @desc �����߳���Դͬ��
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
