
#pragma once

struct glTime;

//
// @brief ʱ��������
//
class glTimeHelper {
public:
	static bool getTimeElapseFromSystemStartup(unsigned int & timeElapse);
	static bool getTimeElapseFromSystemStartup64(unsigned long long int & timeElapse);
	static bool getLocalTime(glTime & localTime);
};
