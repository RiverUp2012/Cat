
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

sgePerformanceCounter::sgePerformanceCounter()
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

sgePerformanceCounter::~sgePerformanceCounter()
{

}

void sgePerformanceCounter::tick(void)
{
	LARGE_INTEGER timeLastTick = { 0 };

	QueryPerformanceCounter(&timeLastTick);

	mElapse = timeLastTick.QuadPart - mTimeLastTick;
	mTimeLastTick = timeLastTick.QuadPart;
}

float sgePerformanceCounter::getElapseF32(void) const
{
	if (mFrequency > 0)
	{
		return (float)((double)mElapse / (double)mFrequency);
	}

	return 0;
}
