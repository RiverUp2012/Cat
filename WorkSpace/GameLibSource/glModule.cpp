
#include "../GameLibInclude/glModule.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glStringHelper.h"

glModule::glModule() {
	mModuleHandle = 0;
}

glModule::glModule(const wchar_t * moduleFileName) {
	createW(moduleFileName);
}

glModule::~glModule() {
	destroy();
}

bool glModule::createW(const wchar_t * moduleFileName) {
	if (!mModuleHandle && moduleFileName) {
		mModuleHandle = (void *)LoadLibraryW(moduleFileName);
		if (mModuleHandle) {
			return true;
		}
		else {
			throw glWin32APIException(L"LoadLibraryW", GetLastError());
		}
	}
	return false;
}

void glModule::destroy(void) {
	if (mModuleHandle) {
		FreeLibrary((HMODULE)mModuleHandle);
		mModuleHandle = 0;
	}
}

bool glModule::isAlready(void) const {
	return mModuleHandle ? true : false;
}

void * glModule::getProcAddressW(const wchar_t * procName) {
	glStringA procNameA;
	if (mModuleHandle && procName) {
		if (glStringHelper::w2a(procName, procNameA)) {
			return getProcAddressA(procNameA);
		}
	}
	return 0;
}

void * glModule::getProcAddressA(const char * procName) {
	void * procAddress = 0;
	if (mModuleHandle && procName) {
		procAddress = GetProcAddress((HMODULE)mModuleHandle, procName);
		if (!procAddress) {
			throw glWin32APIException(L"GetProcAddress", GetLastError());
		}
	}
	return procAddress;
}
