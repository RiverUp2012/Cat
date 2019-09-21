
#pragma once

#include "glNonCopyable.h"

//
// @brief Ä£¿éÀà
//
class glModule : public glNonCopyable {
public:
	glModule();
	glModule(const wchar_t * moduleFileName);
	virtual ~glModule();
public:
	bool createW(const wchar_t * moduleFileName);
	void destroy(void);
	bool isAlready(void) const;
	void * getProcAddressW(const wchar_t * procName);
	void * getProcAddressA(const char * procName);
	const void * getModuleHandle(void) const;
private:
	void * mModuleHandle;
};
