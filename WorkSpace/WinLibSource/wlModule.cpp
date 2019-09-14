
#include "../WinLib.h"

wlModule::wlModule() {
	mModuleHandle = 0;
}

wlModule::~wlModule() {
	unload();
}

bool wlModule::loadW(const wchar_t * moduleFileName) {
	if (!mModuleHandle && moduleFileName) {
		mModuleHandle = (void *)LoadLibraryW(moduleFileName);
		if (mModuleHandle) {
			return true;
		}
	}
	return false;
}

void wlModule::unload(void) {
	if (mModuleHandle) {
		FreeLibrary((HMODULE)mModuleHandle);
		mModuleHandle = 0;
	}
}

bool wlModule::isAlready(void) const {
	return mModuleHandle ? true : false;
}

void * wlModule::getProcAddressA(const char * procName) {
	if (mModuleHandle && procName) {
		return GetProcAddress((HMODULE)mModuleHandle, procName);
	}
	return 0;
}
