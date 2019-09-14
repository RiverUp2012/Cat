
#include "../WinLib.h"

wlProcessEnumCallbackWarpper::wlProcessEnumCallbackWarpper() {

}

wlProcessEnumCallbackWarpper::~wlProcessEnumCallbackWarpper() {

}

void wlProcessEnumCallbackWarpper::enumProcess(void) {
	mProcessIDList.clear();
	wlProcessHelper::enumProcess(this);
}

const sgeList<unsigned long> & wlProcessEnumCallbackWarpper::getProcessIDList(void) const {
	return mProcessIDList;
}

bool wlProcessEnumCallbackWarpper::onEnumProcess(const unsigned long processID) {
	mProcessIDList.pushBack(processID);
	return true;
}
