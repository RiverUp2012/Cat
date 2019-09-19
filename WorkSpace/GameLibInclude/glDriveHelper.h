
#pragma once

#include "glArray.h"
#include "glString.h"

//
// @brief 驱动器助手类
//
class glDriveHelper {
public:
	//
	// @brief 获取可用驱动器列表
	//
	static void getDriveNameListW(glArray<glStringW> & driveNameArray);
};
