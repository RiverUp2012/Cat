
#pragma once

#include "glNonCopyable.h"

//
// @brief �ɵȴ���ʱ����
//
class glWaitableTimer : public glNonCopyable {
public:
	glWaitableTimer();
	virtual ~glWaitableTimer();
public:
	bool create(void);
	void destroy(void);
	bool isAlready(void) const;
	bool wait(const int timeOut);
private:
	void * mTimerHandle;
};
