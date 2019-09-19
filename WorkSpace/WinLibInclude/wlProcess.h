
#pragma once

#include "../GameLibInclude/glNonCopyable.h"
#include "../GameLibInclude/glString.h"

//
// @brief ½ø³ÌÀà
//
class wlProcess : public glNonCopyable {
public:
	wlProcess();
	virtual ~wlProcess();
public:
	bool createByProcessID(const unsigned long processID, const int features = 0);
	void destroy(void);
	bool terminate(void);
	bool getImageFileNameW(glStringW & imageFileName);
	bool vmRead(const void * vmAddress, void * buffer, const int bytesToRead);
	bool vmWrite(void * vmAddress, const void * buffer, const int bytesToWrite);
	bool setPrivilegeW(const wchar_t * privilegeName, const bool enableOrDisable);
	void * getProcessHandle(void) const;
	unsigned long getProcesseID(void) const;
private:
	void * mProcessHandle;
	unsigned long mProcessID;
};
