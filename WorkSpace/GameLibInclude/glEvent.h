
#pragma once

#include "glNonCopyable.h"

//
// @brief 事件类
//
class glEvent : public glNonCopyable {
public:
	glEvent();
	virtual ~glEvent();
public:
	//
	// @brief 创建事件
	//
	bool createW(const wchar_t * eventName, const bool manualReset, const bool initState);
	//
	// @brief 打开事件
	//
	bool openW(const wchar_t * eventName);
	//
	// @brief 销毁事件
	//
	void destroy(void);
	//
	// @brief 激活事件
	//
	bool setEvent(void);
	//
	// @brief 反激活事件
	//
	bool resetEvent(void);
private:
	void * mEventHandle;
};
