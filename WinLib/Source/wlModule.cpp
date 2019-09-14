
#include "../Include/WinLib.h"

wlModule::wlModule() {

}

wlModule::~wlModule() {
	unload();
}

bool wlModule::loadW(const wchar_t * moduleFileName) {
	if (!mModuleHandle && moduleFileName) {
		mModuleHandle = LoadLibraryW(moduleFileName);
		if (mModuleHandle) {
			return true;
		}
	}
	return false;
}

void wlModule::unload(void) {
	if (mModuleHandle) {
		FreeLibrary(mModuleHandle);
		mModuleHandle = 0;
	}
}

bool wlModule::isAlready(void) const {
	return mModuleHandle ? true : false;
}

void * wlModule::getProcAddressA(const char * procName) {
	if (mModuleHandle && procName) {
		return GetProcAddress(mModuleHandle, procName);
	}
	return 0;
}
