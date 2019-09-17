
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

namespace {
	static bool gCreateFlag = false;
}

bool glNetDevice::create(void) {
	WSADATA wsaData = { 0 };
	int ret = 0;
	if (!gCreateFlag) {
		ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (0 == ret) {
			gCreateFlag = true;
			return true;
		}
		else if (WSAVERNOTSUPPORTED == ret) {
			ret = WSAStartup(wsaData.wHighVersion, &wsaData);
			if (0 == ret) {
				gCreateFlag = true;
				return true;
			}
		}
	}
	return false;
}

void glNetDevice::destroy(void) {
	if (gCreateFlag) {
		WSACleanup();
		gCreateFlag = false;
	}
}
