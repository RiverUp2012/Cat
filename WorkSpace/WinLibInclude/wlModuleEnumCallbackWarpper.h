
#pragma once

#include "wlModuleEnumCallback.h"
#include "../GameLibInclude/glNonCopyable.h"
#include "../GameLibInclude/glList.h"
#include "../GameLibInclude/glString.h"

//
// @brief ģ��ö�ٽӿڰ�װ��
//
class wlModuleEnumCallbackWarpper : public wlModuleEnumCallback, public glNonCopyable {
public:
	struct wlModuleInfo {
		void * mModuleHandle;
		glStringW mModuleFileName;
	};
public:
	wlModuleEnumCallbackWarpper();
	virtual ~wlModuleEnumCallbackWarpper();
public:
	void enumModule(const unsigned long processId);
	const glList<wlModuleInfo> & getModuleInfoList(void) const;
private:
	bool onEnumModuleW(
		const wchar_t * moduleFileName,
		void * moduleHandle) override;
private:
	glList<wlModuleInfo> mModuleInfoList;
};
