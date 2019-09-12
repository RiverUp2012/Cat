
#include "../Include/WinLib.h"

namespace wl {

	Module::Module() {

	}

	Module::~Module() {
		unload();
	}

	bool Module::loadW(const wchar_t * moduleFileName) {
		if (!mModuleHandle && moduleFileName) {
			mModuleHandle = LoadLibraryW(moduleFileName);
			if (mModuleHandle) {
				return true;
			}
		}
		return false;
	}

	void Module::unload(void) {
		if (mModuleHandle) {
			FreeLibrary(mModuleHandle);
			mModuleHandle = 0;
		}
	}

	bool Module::isAlready(void) const {
		return mModuleHandle ? true : false;
	}

	void * Module::getProcAddressA(const char * procName) {
		if (mModuleHandle && procName) {
			return GetProcAddress(mModuleHandle, procName);
		}
		return 0;
	}

} // namespace wl
