
#include "../GameLibInclude/glNetHelper.h"
#include "../GameLibInclude/glNetDevice.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glDefine.h"
#include "../GameLibInclude/glStringHelper.h"
#include "../GameLibInclude/glGlobalData.h"

typedef int(WSAAPI * glgethostname)(
	char FAR * name,
	int namelen);
typedef struct hostent FAR * (WSAAPI * glgethostbyname)(
	const char FAR * name);
typedef int (WSAAPI * glWSAGetLastError)(
	void);
typedef char FAR *(WSAAPI * glinet_ntoa)(
	struct in_addr in);

namespace {
	static glgethostname ggethostname = 0;
	static glgethostbyname ggethostbyname = 0;
	static glWSAGetLastError gWSAGetLastError = 0;
	static glinet_ntoa ginet_ntoa = 0;
}

bool glNetHelper::getLocalMachineIPv4W(glStringW & ipV4) {
	char hostName[520] = { 0 };
	hostent * hostEnt = 0;
	sockaddr_in sockAddr = { 0 };
	glNetDevice::create();
	if (!gModule_ws2_32.isAlready()) {
		gModule_ws2_32.createW(L"ws2_32.dll");
	}
	if (gModule_ws2_32.isAlready()) {
		if (!ggethostname) {
			ggethostname = (glgethostname)gModule_ws2_32.getProcAddressA("gethostname");
		}
		if (!ggethostbyname) {
			ggethostbyname = (glgethostbyname)gModule_ws2_32.getProcAddressA("gethostbyname");
		}
		if (!gWSAGetLastError) {
			gWSAGetLastError = (glWSAGetLastError)gModule_ws2_32.getProcAddressA("WSAGetLastError");
		}
		if (!ginet_ntoa) {
			ginet_ntoa = (glinet_ntoa)gModule_ws2_32.getProcAddressA("inet_ntoa");
		}
	}
	if (ggethostname && ggethostbyname && gWSAGetLastError && ginet_ntoa) {
		if (0 == ggethostname(hostName, GL_DIM(hostName))) {
			hostEnt = ggethostbyname(hostName);
			if (hostEnt) {
				if (hostEnt->h_addr_list[0]) {
					memcpy(
						&sockAddr.sin_addr.S_un.S_addr,
						hostEnt->h_addr_list[0],
						hostEnt->h_length);
					if (glStringHelper::a2w(ginet_ntoa(sockAddr.sin_addr), ipV4, false)) {
						return true;
					}
				}
			}
			else {
				throw glWin32APIException(L"gethostbyname", gWSAGetLastError());
			}
		}
		else {
			throw glWin32APIException(L"gethostname", gWSAGetLastError());
		}
	}
	return false;
}

bool glNetHelper::getLocalMachineIPv4A(glStringA & ipV4) {
	glStringW ipV4W;
	if (getLocalMachineIPv4W(ipV4W)) {
		if (glStringHelper::w2a(ipV4W, ipV4)) {
			return true;
		}
	}
	return false;
}
