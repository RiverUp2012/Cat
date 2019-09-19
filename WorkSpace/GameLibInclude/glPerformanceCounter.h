
#pragma once

#include "glNonCopyable.h"

//
// @brief 性能计数器类
//
class glPerformanceCounter : public glNonCopyable {
public:
	glPerformanceCounter();
	virtual ~glPerformanceCounter();
public:
	void tick(void);
	float getElapseF32(void) const;
private:
	long long int mFrequency;
	long long int mTimeLastTick;
	long long int mElapse;
};
