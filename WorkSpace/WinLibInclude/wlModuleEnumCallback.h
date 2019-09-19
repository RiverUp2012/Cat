
#pragma once

//
// @brief 模块枚举回调接口类
//
class wlModuleEnumCallback {
public:
	virtual bool onEnumModuleW(
		const wchar_t * moduleFileName,
		void * moduleHandle) = 0;
};
