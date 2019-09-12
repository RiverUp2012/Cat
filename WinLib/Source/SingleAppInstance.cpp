
#include "../Include/WinLib.h"

namespace wl {

	SingleAppInstance::SingleAppInstance() {

	}

	SingleAppInstance::~SingleAppInstance() {
		mEvent.destroy();
	}

	bool SingleAppInstance::checkW(const wchar_t * appInstanceName) {
		if (appInstanceName) {
			if (mEvent.openW(appInstanceName)) {
				return true;
			}
			mEvent.createW(appInstanceName, true, false);
		}
		return false;
	}

} // namespace wl
