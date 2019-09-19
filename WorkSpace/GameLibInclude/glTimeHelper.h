
#pragma once

struct glTime;

//
// @brief 时间助手类
//
class glTimeHelper {
public:
	static bool getTimeElapseFromSystemStartup(unsigned int & timeElapse);
	static bool getTimeElapseFromSystemStartup64(unsigned long long int & timeElapse);
	static bool getLocalTime(glTime & localTime);
};
