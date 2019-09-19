
#pragma once

#include "glNonCopyable.h"

//
// @brief ���ܼ�������
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
