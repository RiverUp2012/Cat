
#pragma once

//
// @brief ����ö�ٻص��ӿ���
//
class wlProcessEnumCallback {
public:
	virtual bool onEnumProcessW(
		const unsigned long processID,
		const wchar_t * exeFileName) = 0;
};
