
#pragma once

class wlProcessEnumCallback;
class wlModuleEnumCallback;

//
// @brief ���̹�����
//
class wlProcessHelper {
public:
	static void enumProcess(wlProcessEnumCallback * callback);
	static void enumModule(const unsigned long processId, wlModuleEnumCallback * callback);
};
