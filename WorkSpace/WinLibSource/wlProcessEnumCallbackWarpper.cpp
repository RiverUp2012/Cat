
#include "../WinLibInclude/wlProcessEnumCallbackWarpper.h"
#include "../WinLibInclude/wlProcessHelper.h"

wlProcessEnumCallbackWarpper::wlProcessEnumCallbackWarpper() {

}

wlProcessEnumCallbackWarpper::~wlProcessEnumCallbackWarpper() {

}

void wlProcessEnumCallbackWarpper::enumProcess(void) {
	mProcessInfoList.clear();
	wlProcessHelper::enumProcess(this);
}

const glList<wlProcessEnumCallbackWarpper::wlProcessInfo> & wlProcessEnumCallbackWarpper::getProcessInfoList(void) const {
	return mProcessInfoList;
}

bool wlProcessEnumCallbackWarpper::onEnumProcessW(
	const unsigned long processID,
	const wchar_t * exeFileName) {
	wlProcessInfo processInfo;
	processInfo.mProcessID = processID;
	processInfo.mExeFileName = exeFileName;
	mProcessInfoList.pushBack(processInfo);
	return true;
}
