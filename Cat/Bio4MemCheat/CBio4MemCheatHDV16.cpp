
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
	// ������Ϸ����
	//
	pecw.enumProcess();
	for (auto iter = pecw.getProcessInfoList().begin(); iter.isValid(); iter.moveNext()) {
		const auto & processInfo = iter.getData();
		if (0 == _wcsicmp(L"bio4.exe", processInfo.mExeFileName.getString())) {
			if (mBio4Process.openByProcessID(
				processInfo.mProcessID,
				WL_PROCESS_FEATURE_VM_OPERATION)) {
				//
				// ������Ϸ��ִ��ģ��
				//
				mecw.enumModule(mBio4Process.getProcesseID());
				for (auto iter = mecw.getModuleInfoList().begin(); iter.isValid(); iter.moveNext()) {
					const auto & moduleInfo = iter.getData();
					if (glStringTool::findW(moduleInfo.mModuleFileName.getString(), L"bio4.exe") >= 0) {
						//
						// ����Ϸ��ִ��ģ�����ַ��������
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
	mBio4Process.close();
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
	return false;
}

bool CBio4MemCheatHDV16::addCurrentGunBulletCount(const int addItemCount) {
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
