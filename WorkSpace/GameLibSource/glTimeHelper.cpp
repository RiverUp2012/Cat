
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

bool glTimeHelper::getTimeElapseFromSystemStartup(unsigned int & timeElapse) {
	timeElapse = GetTickCount();
	return true;
}

bool glTimeHelper::getTimeElapseFromSystemStartup64(unsigned long long int & timeElapse) {
	timeElapse = GetTickCount64();
	return true;
}

bool glTimeHelper::getLocalTime(glTime & localTime) {
	SYSTEMTIME sysTime = { 0 };
	GetLocalTime(&sysTime);
	localTime.mYear = sysTime.wYear;
	localTime.mMonth = sysTime.wMonth;
	localTime.mDay = sysTime.wDay;
	localTime.mHour = sysTime.wHour;
	localTime.mMinute = sysTime.wMinute;
	localTime.mMilliseconds = sysTime.wMilliseconds;
	return true;
}
