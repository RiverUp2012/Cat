
#pragma once

//
// @brief ģ��ö�ٻص��ӿ���
//
class wlModuleEnumCallback {
public:
	virtual bool onEnumModuleW(
		const wchar_t * moduleFileName,
		void * moduleHandle) = 0;
};
