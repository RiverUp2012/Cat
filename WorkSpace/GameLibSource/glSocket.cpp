
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

glSocket::glSocket() {
	mSocket = 0;
	mClientSocket = false;
	mServerSocket = false;
}

glSocket::glSocket(const int socket) {
	mSocket = socket;
	mClientSocket = true;
	mServerSocket = false;
}

glSocket::~glSocket() {
	destroy();
}

bool glSocket::createForClient(void) {
	glNetDevice::create();
	if (!mSocket) {
		mSocket = (int)socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET != (SOCKET)mSocket) {
			mClientSocket = true;
			return true;
		}
	}
	return false;
}

bool glSocket::createForServerA(const char * ipV4, const short int port) {
	sockaddr_in sockAddr = { 0 };
	glNetDevice::create();
	if (!mSocket) {
		mSocket = (int)socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET != (SOCKET)mSocket) {
			sockAddr.sin_family = AF_INET;
			sockAddr.sin_port = htons(port);
			sockAddr.sin_addr.S_un.S_addr = ipV4 ? inet_addr(ipV4) : 0;
			if (0 == bind((SOCKET)mSocket, (const sockaddr *)&sockAddr, sizeof(sockAddr))) {
				if (0 == listen((SOCKET)mSocket, SOMAXCONN)) {
					mServerSocket = true;
					return true;
				}
			}
			closesocket((SOCKET)mSocket);
			mSocket = 0;
		}
	}
	return false;
}

void glSocket::destroy(void) {
	if (mSocket) {
		shutdown((SOCKET)mSocket, SB_BOTH);
		closesocket((SOCKET)mSocket);
		mSocket = 0;
	}
	mClientSocket = false;
	mServerSocket = false;
}

bool glSocket::connectToServerA(const char * ipV4, const short int port) {
	sockaddr_in sockAddr = { 0 };
	if (mSocket && ipV4 && mClientSocket) {
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(port);
		sockAddr.sin_addr.S_un.S_addr = ipV4 ? inet_addr(ipV4) : 0;
		if (0 == connect((SOCKET)mSocket, (const sockaddr *)&sockAddr, sizeof(sockAddr))) {
			return true;
		}
	}
	return false;
}