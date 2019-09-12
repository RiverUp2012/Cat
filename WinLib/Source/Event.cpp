
#include "../Include/WinLib.h"

namespace wl {

	Event::Event() {

	}

	Event::~Event() {
		destroy();
	}

	bool Event::createW(const wchar_t * eventName, const bool manualReset, const bool initState) {
		if (!mEventHandle) {
			mEventHandle = CreateEventW(0, manualReset ? TRUE : FALSE, initState ? TRUE : FALSE, eventName);
			if (mEventHandle) {
				return true;
			}
		}
		return false;
	}

	bool Event::openW(const wchar_t * eventName) {
		if (!mEventHandle && eventName) {
			mEventHandle = OpenEventW(EVENT_ALL_ACCESS, FALSE, eventName);
			if (mEventHandle) {
				return true;
			}
		}
		return false;
	}

	void Event::destroy(void) {
		if (mEventHandle) {
			CloseHandle(mEventHandle);
			mEventHandle = 0;
		}
	}

} // namespace wl
