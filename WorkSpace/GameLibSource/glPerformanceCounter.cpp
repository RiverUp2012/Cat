
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

glPerformanceCounter::glPerformanceCounter()
{
	LARGE_INTEGER frequency = { 0 };
	LARGE_INTEGER timeLastTick = { 0 };

	mFrequency = 0;
	mTimeLastTick = 0;
	mElapse = 0;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&timeLastTick);

	mFrequency = frequency.QuadPart;
	mTimeLastTick = timeLastTick.QuadPart;
}

glPerformanceCounter::~glPerformanceCounter()
{

}

void glPerformanceCounter::tick(void)
{
	LARGE_INTEGER timeLastTick = { 0 };

	QueryPerformanceCounter(&timeLastTick);

	mElapse = timeLastTick.QuadPart - mTimeLastTick;
	mTimeLastTick = timeLastTick.QuadPart;
}

float glPerformanceCounter::getElapseF32(void) const
{
	if (mFrequency > 0)
	{
		return (float)((double)mElapse / (double)mFrequency);
	}

	return 0;
}
