
#include "stdafx.h"
#include "CBio4MemCheatHDV16.h"

CBio4MemCheatHDV16::CBio4MemCheatHDV16() {
	mBio4ModuleBaseAddress = 0;
}

bool CBio4MemCheatHDV16::setup(void) {
	wlProcessEnumCallbackWarpper pecw;
	wlModuleEnumCallbackWarpper mecw;
	shutdown();
	//
	// 查找游戏进程
	//
	pecw.enumProcess();
	for (auto iter = pecw.getProcessInfoList().begin(); iter.isValid(); iter.moveNext()) {
		const auto & processInfo = iter.getData();
		if (0 == _wcsicmp(L"bio4.exe", processInfo.mExeFileName)) {
			if (mBio4Process.createByProcessID(
				processInfo.mProcessID,
				WL_PROCESS_FEATURE_VM_OPERATION)) {
				//
				// 查找游戏可执行模块
				//
				mecw.enumModule(mBio4Process.getProcesseID());
				for (auto iter = mecw.getModuleInfoList().begin(); iter.isValid(); iter.moveNext()) {
					const auto & moduleInfo = iter.getData();
					if (glStringHelper::findW(moduleInfo.mModuleFileName, L"bio4.exe") >= 0) {
						//
						// 将游戏可执行模块基地址保存起来
						//
						mBio4ModuleBaseAddress = (int)moduleInfo.mModuleHandle;
						return true;
					}
				}
			}
			break;
		}
	}
	return false;
}

void CBio4MemCheatHDV16::shutdown(void) {
	mBio4Process.destroy();
	mBio4ModuleBaseAddress = 0;
}

bool CBio4MemCheatHDV16::queryLeonHP(int & hp) {
	return false;
}

bool CBio4MemCheatHDV16::setLeonHP(const int hp) {
	return false;
}

bool CBio4MemCheatHDV16::queryLeonMaxHP(int & maxHP) {
	return false;
}

bool CBio4MemCheatHDV16::setLeonMaxHP(const int maxHP) {
	return false;
}

bool CBio4MemCheatHDV16::addCurrentItemCount(const int addItemCount) {
	int address = mBio4ModuleBaseAddress + 0x86D760;
	__int16 itemCount = 0;
	if (mBio4Process.vmRead((const void *)address, &address, 4)) {
		address += 2;
		if (mBio4Process.vmRead((const void *)address, &itemCount, 2)) {
			itemCount += static_cast<__int16>(addItemCount);
			if (mBio4Process.vmWrite((void *)address, &itemCount, 2)) {
				return true;
			}
		}
	}
	return false;
}

bool CBio4MemCheatHDV16::addCurrentGunBulletCount(const int addGunBulletCount) {
	int address = mBio4ModuleBaseAddress + 0x86D760;
	__int16 bulletCount = 0;
	if (mBio4Process.vmRead((const void *)address, &address, 4)) {
		address += 8;
		if (mBio4Process.vmRead((const void *)address, &bulletCount, 2)) {
			bulletCount += static_cast<__int16>(addGunBulletCount * 8);
			if (mBio4Process.vmWrite((void *)address, &bulletCount, 2)) {
				return true;
			}
		}
	}
	return false;
}

bool CBio4MemCheatHDV16::queryLeonPTAS(int & ptas) {
	int address = mBio4ModuleBaseAddress + 0x805F3C;
	if (mBio4Process.vmRead((const void *)address, &address, 4)) {
		address += 0x4FA8;
		if (mBio4Process.vmRead((const void *)address, &ptas, 4)) {
			return true;
		}
	}
	return false;
}

bool CBio4MemCheatHDV16::setLeonPTAS(const int ptas) {
	int address = mBio4ModuleBaseAddress + 0x805F3C;
	if (mBio4Process.vmRead((const void *)address, &address, 4)) {
		address += 0x4FA8;
		if (mBio4Process.vmWrite((void *)address, &ptas, 4)) {
			return true;
		}
	}
	return false;
}
