
#pragma once

#include "wlProcessEnumCallback.h"
#include "../GameLibInclude/glNonCopyable.h"
#include "../GameLibInclude/glList.h"
#include "../GameLibInclude/glString.h"

//
// @brief 进程枚举接口包装类
//
class wlProcessEnumCallbackWarpper : public wlProcessEnumCallback, public glNonCopyable {
public:
	struct wlProcessInfo {
		unsigned long mProcessID;
		glStringW mExeFileName;
	};
public:
	wlProcessEnumCallbackWarpper();
	virtual ~wlProcessEnumCallbackWarpper();
public:
	void enumProcess(void);
	const glList<wlProcessInfo> & getProcessInfoList(void) const;
private:
	bool onEnumProcessW(
		const unsigned long processID,
		const wchar_t * exeFileName) override;
private:
	glList<wlProcessInfo> mProcessInfoList;
};
