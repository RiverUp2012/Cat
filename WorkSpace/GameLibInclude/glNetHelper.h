
#pragma once

#include "glString.h"

//
// @brief ����������
//
class glNetHelper {
public:
	//
	// @brief ��ȡ���ػ����� IPv4 ��ַ
	//
	static bool getLocalMachineIPv4W(glStringW & ipV4);
	static bool getLocalMachineIPv4A(glStringA & ipV4);
};
