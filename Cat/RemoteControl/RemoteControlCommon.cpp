
#include "stdafx.h"
#include "RemoteControlCommon.h"

// 包签名
#define PACK_SIG ("PACK")
// 包版本号
#define PACK_VER_MAJOR (0)
// 包版本号
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

bool writeMemFileStringW(glMemFile & memFile, const glStringW & string) {
	const int stringLength = string.getLength();
	if (glWriteMemFile(memFile, stringLength)) {
		if (stringLength > 0) {
			if (memFile.write(string.getString(), string.getCharSize() * stringLength)) {
				return true;
			}
		}
		else {
			return true;
		}
	}
	return false;
}

bool readMemFileStringW(glMemFile & memFile, glStringW & string) {
	int stringLength = 0;
	if (glReadMemFile(memFile, stringLength)) {
		string.clear();
		if (stringLength > 0) {
			if (string.resize(stringLength + 1)) {
				if (memFile.read(string.getBuffer(), string.getCharSize() * stringLength)) {
					string.setAt(stringLength, L'\0');
					return true;
				}
			}
		}
		else {
			return true;
		}
	}
	return false;
}

int calcMemStringSizeW(const glStringW & string) {
	const int stringLength = string.getLength();
	return sizeof(stringLength) + (string.getCharSize() * stringLength);
}
