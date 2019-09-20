
#include "stdafx.h"
#include "RemoteControlCommon.h"

// ��ǩ��
#define PACK_SIG ("PACK")
// ���汾��
#define PACK_VER_MAJOR (0)
// ���汾��
#define PACK_VER_MINOR (1)

bool isPackValid(const SPackHeader & packHeader) {
	if (0 == memcmp(packHeader.mSig, PACK_SIG, sizeof(packHeader.mSig)) &&
		PACK_VER_MAJOR == packHeader.mVerMajor &&
		PACK_VER_MINOR == packHeader.mVerMinor &&
		packHeader.mProtocol > PROTOCOL_FIRST && packHeader.mProtocol < PROTOCOL_LAST) {
		return true;
	}
	return false;
}

void makePackHeader(SPackHeader & packHeader, const int protocol) {
	if (protocol > PROTOCOL_FIRST && protocol < PROTOCOL_LAST) {
		memcpy(packHeader.mSig, PACK_SIG, sizeof(packHeader.mSig));
		packHeader.mVerMajor = PACK_VER_MAJOR;
		packHeader.mVerMinor = PACK_VER_MINOR;
		packHeader.mProtocol = protocol;
		packHeader.mPackSize = 0;
	}
	else {
		throw glException(L"Invalid Protocol");
	}
}
