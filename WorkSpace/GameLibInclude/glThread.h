
#pragma once

#include "glNonCopyable.h"

//
// @brief œﬂ≥Ã¿‡
//
class glThread : public glNonCopyable {
public:
	static void sleepCurrentThread(const int sleepTimeOut);
	static unsigned long getCurrentThreadID(void);
public:
	glThread();
	virtual ~glThread();
public:
	bool create(const bool runNow = true);
	void destroy(const int waitTimeout = 0);
	bool wait(const int waitTimeout);
	bool isAlready(void) const;
public:
	virtual void onThreadRun(void) = 0;
private:
	void * mThreadHandle;
	unsigned long mThreadID = 0;
};
