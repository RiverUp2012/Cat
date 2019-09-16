
#include "../GameLib.h"

glSingleAppInstance::glSingleAppInstance() {

}

glSingleAppInstance::~glSingleAppInstance() {
	mEvent.destroy();
}

bool glSingleAppInstance::checkW(const wchar_t * appInstanceName) {
	if (appInstanceName) {
		if (mEvent.openW(appInstanceName)) {
			return true;
		}
		mEvent.createW(appInstanceName, true, false);
	}
	return false;
}
