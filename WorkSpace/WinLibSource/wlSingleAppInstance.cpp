
#include "../WinLib.h"

wlSingleAppInstance::wlSingleAppInstance() {

}

wlSingleAppInstance::~wlSingleAppInstance() {
	mEvent.destroy();
}

bool wlSingleAppInstance::checkW(const wchar_t * appInstanceName) {
	if (appInstanceName) {
		if (mEvent.openW(appInstanceName)) {
			return true;
		}
		mEvent.createW(appInstanceName, true, false);
	}
	return false;
}
