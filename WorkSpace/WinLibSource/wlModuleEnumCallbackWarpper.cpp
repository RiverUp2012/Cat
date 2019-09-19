
#include "../WinLibInclude/wlModuleEnumCallbackWarpper.h"
#include "../WinLibInclude/wlProcessHelper.h"

wlModuleEnumCallbackWarpper::wlModuleEnumCallbackWarpper() {

}

wlModuleEnumCallbackWarpper::~wlModuleEnumCallbackWarpper() {

}

void wlModuleEnumCallbackWarpper::enumModule(const unsigned long processId) {
	mModuleInfoList.clear();
	wlProcessHelper::enumModule(processId, this);
}

const glList<wlModuleEnumCallbackWarpper::wlModuleInfo> & wlModuleEnumCallbackWarpper::getModuleInfoList(void) const {
	return mModuleInfoList;
}

bool wlModuleEnumCallbackWarpper::onEnumModuleW(const wchar_t * moduleFileName, void * moduleHandle) {
	wlModuleInfo moduleInfo;
	moduleInfo.mModuleHandle = moduleHandle;
	moduleInfo.mModuleFileName = moduleFileName;
	mModuleInfoList.pushBack(moduleInfo);
	return true;
}
