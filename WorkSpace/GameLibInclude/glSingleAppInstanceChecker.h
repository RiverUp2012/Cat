
#pragma once

#include "glNonCopyable.h"
#include "glEvent.h"

//
// @brief 用于保证应用程序只有一个实例正在运行的类
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
