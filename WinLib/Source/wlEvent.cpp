
#include "../Include/WinLib.h"

wlEvent::wlEvent() {

}

wlEvent::~wlEvent() {
	destroy();
}

bool wlEvent::createW(const wchar_t * eventName, const bool manualReset, const bool initState) {
	if (!mEventHandle) {
		mEventHandle = CreateEventW(0, manualReset ? TRUE : FALSE, initState ? TRUE : FALSE, eventName);
		if (mEventHandle) {
			return true;
		}
	}
	return false;
}

bool wlEvent::openW(const wchar_t * eventName) {
	if (!mEventHandle && eventName) {
		mEventHandle = OpenEventW(EVENT_ALL_ACCESS, FALSE, eventName);
		if (mEventHandle) {
			return true;
		}
	}
	return false;
}

void wlEvent::destroy(void) {
	if (mEventHandle) {
		CloseHandle(mEventHandle);
		mEventHandle = 0;
	}
}
