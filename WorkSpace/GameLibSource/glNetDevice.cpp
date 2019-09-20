
#include "../GameLibInclude/glNetDevice.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glGlobalData.h"

typedef int (WSAAPI * glWSAStartup)(
	WORD wVersionRequested,
	LPWSADATA lpWSAData);
typedef int (WSAAPI * glWSACleanup)(
	void);
typedef int (WSAAPI * glWSAGetLastError)(
	void);

namespace {
	static bool gCreateFlag = false;
	static glWSAStartup gWSAStartup = 0;
	static glWSACleanup gWSACleanup = 0;
	static glWSAGetLastError gWSAGetLastError = 0;
}

bool glNetDevice::create(void) {
	WSADATA wsaData = { 0 };
	int ret = 0;
	if (!gModule_ws2_32.isAlready()) {
		gModule_ws2_32.createW(L"ws2_32.dll");
	}
	if (gModule_ws2_32.isAlready()) {
		if (!gWSAStartup) {
			gWSAStartup = (glWSAStartup)gModule_ws2_32.getProcAddressA("WSAStartup");
		}
		if (!gWSACleanup) {
			gWSACleanup = (glWSACleanup)gModule_ws2_32.getProcAddressA("WSACleanup");
		}
		if (!gWSAGetLastError) {
			gWSAGetLastError = (glWSAGetLastError)gModule_ws2_32.getProcAddressA("WSAGetLastError");
		}
	}
	if (!gCreateFlag && gWSAStartup && gWSAGetLastError) {
		ret = gWSAStartup(MAKEWORD(2, 2), &wsaData);
		if (0 == ret) {
			gCreateFlag = true;
			return true;
		}
		else if (WSAVERNOTSUPPORTED == ret) {
			ret = gWSAStartup(wsaData.wHighVersion, &wsaData);
			if (0 == ret) {
				gCreateFlag = true;
				return true;
			}
			else {
				throw glWin32APIException(L"WSAStartup", gWSAGetLastError());
			}
		}
		else {
			throw glWin32APIException(L"WSAStartup", gWSAGetLastError());
		}
	}
	return false;
}

void glNetDevice::destroy(void) {
	if (gCreateFlag && gWSACleanup) {
		gWSACleanup();
		gCreateFlag = false;
	}
}
