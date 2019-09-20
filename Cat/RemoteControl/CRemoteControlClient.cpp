
#include "stdafx.h"
#include "CRemoteControlClient.h"
#include "RemoteControlCommon.h"

namespace {
	static glSocket gClientSocket;
}

void CRemoteControlClient::startupW(const wchar_t * serverIPv4, const short int serverPort) {

}

void CRemoteControlClient::shutdown(void) {

}

bool CRemoteControlClient::requestUserNameW(glStringW & userName) {
	bool ret = false;
	return ret;
}
