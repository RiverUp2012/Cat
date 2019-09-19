
#include "../GameLibInclude/glPerformanceCounter.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glPrivate.h"

glPerformanceCounter::glPerformanceCounter() {
	LARGE_INTEGER frequency = { 0 };
	LARGE_INTEGER timeLastTick = { 0 };
	mFrequency = 0;
	mTimeLastTick = 0;
	mElapse = 0;
	if (!QueryPerformanceFrequency(&frequency)) {
		throw glWin32APIException(L"QueryPerformanceFrequency", GetLastError());
	}
	if (!QueryPerformanceCounter(&timeLastTick)) {
		throw glWin32APIException(L"QueryPerformanceCounter", GetLastError());
	}
	mFrequency = frequency.QuadPart;
	mTimeLastTick = timeLastTick.QuadPart;
}

glPerformanceCounter::~glPerformanceCounter() {

}

void glPerformanceCounter::tick(void) {
	LARGE_INTEGER timeLastTick = { 0 };
	if (!QueryPerformanceCounter(&timeLastTick)) {
		throw glWin32APIException(L"QueryPerformanceCounter", GetLastError());
	}
	mElapse = timeLastTick.QuadPart - mTimeLastTick;
	mTimeLastTick = timeLastTick.QuadPart;
}

float glPerformanceCounter::getElapseF32(void) const {
	if (mFrequency > 0) {
		return (float)((double)mElapse / (double)mFrequency);
	}
	return 0;
}
