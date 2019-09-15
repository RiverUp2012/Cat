
#include "stdafx.h"
#include "CBio4MemCheatOldAsiaV10.h"

bool CBio4MemCheatOldAsiaV10::setup(void) {
	wlProcessEnumCallbackWarpper pecw;
	shutdown();
	pecw.enumProcess();
	for (auto iter = pecw.getProcessInfoList().begin(); iter.isValid(); iter.moveNext()) {
		const auto & processInfo = iter.getData();
		if (0 == _wcsicmp(L"game.exe", processInfo.mExeFileName.getString())) {
			if (mProcess.openByProcessID(
				processInfo.mProcessID,
				WL_PROCESS_FEATURE_VM_OPERATION)) {
				return true;
			}
			break;
		}
	}
	return false;
}

void CBio4MemCheatOldAsiaV10::shutdown(void) {
	mProcess.close();
}

bool CBio4MemCheatOldAsiaV10::queryLeonHP(int & hp) {
	return false;
}

bool CBio4MemCheatOldAsiaV10::setLeonHP(const int hp) {
	return false;
}
