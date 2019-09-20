
#include "../GameLibInclude/glSocket.h"
#include "../GameLibInclude/glNetDevice.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"

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

bool glSocket::sendData(const void * buffer, const int bytesToSend, int * bytesSended) {
	int ret = 0;
	if (mSocket && buffer && bytesToSend > 0) {
		ret = send((SOCKET)mSocket, (const char *)buffer, bytesToSend, 0);
		if (SOCKET_ERROR != ret) {
			if (bytesSended) {
				*bytesSended = ret;
			}
			else {
				throw glWin32APIException(L"send", WSAGetLastError());
			}
			return true;
		}
	}
	return false;
}

bool glSocket::recvData(void * buffer, const int bytesToRecv, int * bytesRecved) {
	int ret = 0;
	if (mSocket && buffer && bytesToRecv > 0) {
		ret = recv((SOCKET)mSocket, (char *)buffer, bytesToRecv, 0);
		if (SOCKET_ERROR != ret) {
			if (bytesRecved) {
				*bytesRecved = ret;
			}
			return true;
		}
		else {
			throw glWin32APIException(L"send", WSAGetLastError());
		}
	}
	return false;
}

bool glSocket::sendAllData(const void * buffer, const int bytesToSend) {
	char * bufferTemp = (char *)buffer;
	int bytesSended = 0;
	if (mSocket && bufferTemp && bytesToSend > 0) {
		while (true) {
			int ret = send((SOCKET)mSocket, &(bufferTemp[bytesSended]), bytesToSend - bytesSended, 0);
			if (SOCKET_ERROR != ret) {
				bytesSended += ret;
				if (bytesSended >= bytesToSend) {
					return true;
				}
			}
			else {
				throw glWin32APIException(L"send", WSAGetLastError());
			}
		}
	}
	return false;
}

bool glSocket::recvAllData(void * buffer, const int bytesToRecv) {
	char * bufferTemp = (char *)buffer;
	int bytesRecved = 0;
	if (mSocket && bufferTemp && bytesToRecv > 0) {
		while (true) {
			int ret = recv((SOCKET)mSocket, &(bufferTemp[bytesRecved]), bytesToRecv - bytesRecved, 0);
			if (SOCKET_ERROR != ret) {
				bytesRecved += ret;
				if (bytesRecved >= bytesToRecv) {
					return true;
				}
			}
			else {
				throw glWin32APIException(L"send", WSAGetLastError());
			}
		}
	}
	return false;
}
