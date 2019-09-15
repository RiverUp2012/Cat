
#include "stdafx.h"
#include "CBio4MemCheat.h"
#include "CBio4MemCheatOldAsiaV10.h"

namespace {
	static IBio4MemCheat * gBio4MemCheat = 0;
	static wlProcess mProcessThis;
}

bool CBio4MemCheat::setup(const Bio4Ver & ver) {
	shutdown();
	// 打开当前进程
	if (mProcessThis.openByProcessID(
		GetCurrentProcessId(),
		WL_PROCESS_FEATURE_QUERY_INFO)) {
		// 启用 Debug 特权
		if (mProcessThis.setPrivilegeW(SE_DEBUG_NAME, true)) {
			// 启动作弊器
			if (Bio4VerOldAsiaV10 == ver) {
				gBio4MemCheat = new CBio4MemCheatOldAsiaV10();
			}
			else if (Bio4VerOldAsiaV11 == ver) {

			}
			else if (Bio4VerOldEuropeV10 == ver) {

			}
			else if (Bio4VerOldEuropeV11 == ver) {

			}
			if (gBio4MemCheat) {
				if (gBio4MemCheat->setup()) {
					return true;
				}
			}
		}
	}
	return false;
}

void CBio4MemCheat::shutdown(void) {
	if (gBio4MemCheat) {
		gBio4MemCheat->shutdown();
		delete gBio4MemCheat;
		gBio4MemCheat = 0;
	}
	mProcessThis.close();
}

bool CBio4MemCheat::queryLeonHP(int & hp) {
	if (gBio4MemCheat) {
		return gBio4MemCheat->queryLeonHP(hp);
	}
	return false;
}

bool CBio4MemCheat::setLeonHP(const int hp) {
	if (gBio4MemCheat) {
		return gBio4MemCheat->setLeonHP(hp);
	}
	return false;
}

bool CBio4MemCheat::queryLeonMaxHP(int & maxHP) {
	if (gBio4MemCheat) {
		return gBio4MemCheat->queryLeonMaxHP(maxHP);
	}
	return false;
}

bool CBio4MemCheat::setLeonMaxHP(const int maxHP) {
	if (gBio4MemCheat) {
		return gBio4MemCheat->setLeonMaxHP(maxHP);
	}
	return false;
}

bool CBio4MemCheat::addCurrentItemCount(const int addItemCount) {
	return false;
}

bool CBio4MemCheat::addCurrentGunBulletCount(const int addGunBulletCount) {
	if (gBio4MemCheat) {
		return gBio4MemCheat->addCurrentGunBulletCount(addGunBulletCount);
	}
	return false;
}
