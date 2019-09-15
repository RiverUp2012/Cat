
#include "stdafx.h"
#include "CBio4MemCheatOldAsiaV10.h"

bool CBio4MemCheatOldAsiaV10::setup(void) {
	wlProcessEnumCallbackWarpper pecw;
	shutdown();
	pecw.enumProcess();
	for (auto iter = pecw.getProcessInfoList().begin(); iter.isValid(); iter.moveNext()) {
		const auto & processInfo = iter.getData();
		if (0 == _wcsicmp(L"game.exe", processInfo.mExeFileName.getString())) {
			if (mBio4Process.openByProcessID(
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
	mBio4Process.close();
}

bool CBio4MemCheatOldAsiaV10::queryLeonHP(int & hp) {
	__int16 hpTemp = 0;
	if (mBio4Process.vmRead((const void *)0x033E8E7A, &hpTemp, 2)) {
		hp = hpTemp;
		return true;
	}
	return false;
}

bool CBio4MemCheatOldAsiaV10::setLeonHP(const int hp) {
	const __int16 hpTemp = static_cast<__int16>(hp);
	if (mBio4Process.vmWrite((void *)0x033E8E7A, &hpTemp, 2)) {
		return true;
	}
	return false;
}

bool CBio4MemCheatOldAsiaV10::queryLeonMaxHP(int & maxHP) {
	__int16 maxHPTemp = 0;
	if (mBio4Process.vmRead((const void *)0x033E8E7C, &maxHPTemp, 2)) {
		maxHP = maxHPTemp;
		return true;
	}
	return false;
}

bool CBio4MemCheatOldAsiaV10::setLeonMaxHP(const int maxHP) {
	const __int16 maxHPTemp = static_cast<__int16>(maxHP);
	if (mBio4Process.vmWrite((void *)0x033E8E7C, &maxHPTemp, 2)) {
		return true;
	}
	return false;
}

bool CBio4MemCheatOldAsiaV10::addCurrentItemCount(const int addItemCount) {
	int itemAddr = 0;
	__int16 itemCount = 0;
	if (mBio4Process.vmRead((const void *)0x033E2C4C, &itemAddr, 4)) {
		itemAddr += 2;
		if (mBio4Process.vmRead((const void *)itemAddr, &itemCount, 2)) {
			itemCount += static_cast<__int16>(addItemCount);
			if (mBio4Process.vmWrite((void *)itemAddr, &itemCount, 2)) {
				return true;
			}
		}
	}
	return false;
}

bool CBio4MemCheatOldAsiaV10::addCurrentGunBulletCount(const int addGunBulletCount) {
	int itemAddr = 0;
	__int16 bulletCount = 0;
	if (mBio4Process.vmRead((const void *)0x033E2C4C, &itemAddr, 4)) {
		itemAddr += 8;
		if (mBio4Process.vmRead((const void *)itemAddr, &bulletCount, 2)) {
			bulletCount += static_cast<__int16>(addGunBulletCount * 8);
			if (mBio4Process.vmWrite((void *)itemAddr, &bulletCount, 2)) {
				return true;
			}
		}
	}
	return false;
}

bool CBio4MemCheatOldAsiaV10::queryLeonPTAS(int & ptas) {
	if (mBio4Process.vmRead((const void *)0x033E8E70, &ptas, 4)) {
		return true;
	}
	return false;
}

bool CBio4MemCheatOldAsiaV10::setLeonPTAS(const int ptas) {
	if (mBio4Process.vmWrite((void *)0x033E8E70, &ptas, 4)) {
		return true;
	}
	return false;
}
