
#pragma once

#include "glNonCopyable.h"

//
// @brief �¼���
//
class glEvent : public glNonCopyable {
public:
	glEvent();
	virtual ~glEvent();
public:
	//
	// @brief �����¼�
	//
	bool createW(const wchar_t * eventName, const bool manualReset, const bool initState);
	//
	// @brief ���¼�
	//
	bool openW(const wchar_t * eventName);
	//
	// @brief �����¼�
	//
	void destroy(void);
	//
	// @brief �����¼�
	//
	bool setEvent(void);
	//
	// @brief �������¼�
	//
	bool resetEvent(void);
private:
	void * mEventHandle;
};
