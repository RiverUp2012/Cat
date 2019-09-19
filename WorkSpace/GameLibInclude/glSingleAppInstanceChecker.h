
#pragma once

#include "glNonCopyable.h"
#include "glEvent.h"

//
// @brief ���ڱ�֤Ӧ�ó���ֻ��һ��ʵ���������е���
//
class glSingleAppInstanceChecker : public glNonCopyable {
public:
	glSingleAppInstanceChecker();
	virtual ~glSingleAppInstanceChecker();
public:
	bool checkSingleAppInstanceW(const wchar_t * appInstanceName);
private:
	glEvent mEvent;
};
