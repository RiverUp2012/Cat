
#pragma once

class wlProcessEnumCallback;
class wlModuleEnumCallback;

//
// @brief 进程工具类
//
class wlProcessHelper {
public:
	static void enumProcess(wlProcessEnumCallback * callback);
	static void enumModule(const unsigned long processId, wlModuleEnumCallback * callback);
};
