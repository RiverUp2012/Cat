
#include "stdafx.h"
#include "CBio4MemCheat.h"
#include "CBio4MemCheatOldAsiaV10.h"

namespace {
	static IBio4MemCheat * gBio4MemCheat = 0;
	static wlProcess mProcessThis;
}

bool CBio4MemCheat::setup(void) {
	shutdown();
	// �򿪵�ǰ����
	if (mProcessThis.openByProcessID(
		GetCurrentProcessId(),
		WL_PROCESS_FEATURE_QUERY_INFO)) {
		// ���� Debug ��Ȩ
		if (mProcessThis.setPrivilegeW(SE_DEBUG_NAME, true)) {
			// ����������
			gBio4MemCheat = new CBio4MemCheatOldAsiaV10();
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
