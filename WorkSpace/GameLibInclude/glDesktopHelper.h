
#pragma once

#include "glSize.h"

//
// @brief 桌面助手类
//
class glDesktopHelper {
public:
	//
	// @brief 获取桌面尺寸
	//
	static bool getDesktopSize(glSize<int> & size);
};
