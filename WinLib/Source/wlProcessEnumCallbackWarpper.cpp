
#include "../Include/WinLib.h"

wlProcessEnumCallbackWarpper::wlProcessEnumCallbackWarpper() {

}

wlProcessEnumCallbackWarpper::~wlProcessEnumCallbackWarpper() {

}

void wlProcessEnumCallbackWarpper::enumProcess(void) {
	mProcessIDList.clear();
	wlProcessHelper::enumProcess(this);
}

const std::list<DWORD> & wlProcessEnumCallbackWarpper::getProcessIDList(void) const {
	return mProcessIDList;
}

bool wlProcessEnumCallbackWarpper::onEnumProcess(const DWORD processID) {
	mProcessIDList.push_back(processID);
	return true;
}
