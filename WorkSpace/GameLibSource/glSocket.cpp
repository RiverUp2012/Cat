
#include "../GameLibInclude/glSocket.h"
#include "../GameLibInclude/glNetDevice.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glGlobalData.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glStringHelper.h"

typedef int (WSAAPI * glWSAGetLastError)(
	void);
typedef SOCKET (WSAAPI * glsocket)(
	int af,
	int type,
	int protocol);
typedef int (WSAAPI * glbind)(
	SOCKET s,
	const struct sockaddr FAR * name,
	int namelen);
typedef int (WSAAPI * gllisten)(
	SOCKET s,
	int backlog);
typedef int (WSAAPI * glclosesocket)(
	SOCKET s);
typedef int (WSAAPI * glshutdown)(
	SOCKET s,
	int how);
typedef int (WSAAPI * glconnect)(
	SOCKET s,
	const struct sockaddr FAR * name,
	int namelen);
typedef int (WSAAPI * glrecv)(
	SOCKET s,
	char FAR * buf,
	_In_ int len,
	_In_ int flags);
typedef int (WSAAPI * glsend)(
	SOCKET s,
	const char FAR * buf,
	int len,
	int flags);
typedef SOCKET (WSAAPI * glaccept)(
	SOCKET s,
	struct sockaddr FAR * addr,
	int FAR * addrlen);

namespace {
	static glWSAGetLastError gWSAGetLastError = 0;
	static glsocket gsocket = 0;
	static glbind gbind = 0;
	static gllisten glisten = 0;
	static glclosesocket gclosesocket = 0;
	static glshutdown gshutdown = 0;
	static glconnect gconnect = 0;
	static glrecv grecv = 0;
	static glsend gsend = 0;
	static glaccept gaccept = 0;
}

glSocket::glSocket() {
	mSocket = 0;
	mClientSocket = false;
	mServerSocket = false;

	if (!gModule_ws2_32.isAlready()) {
		gModule_ws2_32.createW(L"ws2_32.dll");
	}
	if (gModule_ws2_32.isAlready()) {
		if (!gWSAGetLastError) {
			gWSAGetLastError = (glWSAGetLastError)gModule_ws2_32.getProcAddressA("WSAGetLastError");
		}
		if (!gsocket) {
			gsocket = (glsocket)gModule_ws2_32.getProcAddressA("socket");
		}
		if (!gbind) {
			gbind = (glbind)gModule_ws2_32.getProcAddressA("bind");
		}
		if (!glisten) {
			glisten = (gllisten)gModule_ws2_32.getProcAddressA("listen");
		}
		if (!gclosesocket) {
			gclosesocket = (glclosesocket)gModule_ws2_32.getProcAddressA("closesocket");
		}
		if (!gshutdown) {
			gshutdown = (glshutdown)gModule_ws2_32.getProcAddressA("shutdown");
		}
		if (!gconnect) {
			gconnect = (glconnect)gModule_ws2_32.getProcAddressA("connect");
		}
		if (!grecv) {
			grecv = (glrecv)gModule_ws2_32.getProcAddressA("recv");
		}
		if (!gsend) {
			gsend = (glsend)gModule_ws2_32.getProcAddressA("send");
		}
		if (!gaccept) {
			gaccept = (glaccept)gModule_ws2_32.getProcAddressA("accept");
		}
	}
}

glSocket::~glSocket() {
	destroy();
}

bool glSocket::createForClient(void) {
	glNetDevice::create();
	if (!mSocket && gWSAGetLastError && gsocket) {
		mSocket = (int)gsocket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET != (SOCKET)mSocket) {
			mClientSocket = true;
			return true;
		}
		else {
			throw glWin32APIException(L"socket", gWSAGetLastError());
		}
	}
	return false;
}

bool glSocket::createForServerA(const char * ipV4, const short int port) {
	sockaddr_in sockAddr = { 0 };
	glNetDevice::create();
	if (!mSocket && gWSAGetLastError && gsocket && gbind && glisten && gclosesocket) {
		mSocket = (int)gsocket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET != (SOCKET)mSocket) {
			sockAddr.sin_family = AF_INET;
			sockAddr.sin_port = htons(port);
			sockAddr.sin_addr.S_un.S_addr = ipV4 ? inet_addr(ipV4) : 0;
			if (0 == gbind((SOCKET)mSocket, (const sockaddr *)&sockAddr, sizeof(sockAddr))) {
				if (0 == glisten((SOCKET)mSocket, SOMAXCONN)) {
					mServerSocket = true;
					return true;
				}
				else {
					throw glWin32APIException(L"listen", gWSAGetLastError());
				}
			}
			else {
				throw glWin32APIException(L"bind", gWSAGetLastError());
			}
			if (0 != gclosesocket((SOCKET)mSocket)) {
				throw glWin32APIException(L"closesocket", gWSAGetLastError());
			}
			mSocket = 0;
		}
	}
	return false;
}

void glSocket::destroy(void) {
	if (mSocket && gWSAGetLastError && gshutdown && gclosesocket) {
		if (0 != gshutdown((SOCKET)mSocket, SB_BOTH)) {
			throw glWin32APIException(L"shutdown", gWSAGetLastError());
		}
		if (0 != gclosesocket((SOCKET)mSocket)) {
			throw glWin32APIException(L"closesocket", gWSAGetLastError());
		}
		mSocket = 0;
	}
	mClientSocket = false;
	mServerSocket = false;
}

bool glSocket::isAlready(void) const {
	return mSocket ? true : false;
}

bool glSocket::connectToServerA(const char * ipV4, const short int port) {
	sockaddr_in sockAddr = { 0 };
	if (mSocket && ipV4 && mClientSocket && gWSAGetLastError && gconnect) {
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(port);
		sockAddr.sin_addr.S_un.S_addr = ipV4 ? inet_addr(ipV4) : 0;
		if (0 == gconnect((SOCKET)mSocket, (const sockaddr *)&sockAddr, sizeof(sockAddr))) {
			return true;
		}
		else {
			throw glWin32APIException(L"connect", gWSAGetLastError());
		}
	}
	return false;
}

bool glSocket::connectToServerW(const wchar_t * ipV4, const short int port) {
	glStringA ipV4A;
	if (ipV4) {
		if (glStringHelper::w2a(ipV4, ipV4A, false)) {
			if (connectToServerA(ipV4A, port)) {
				return true;
			}
		}
	}
	return false;
}

bool glSocket::sendData(const void * buffer, const int bytesToSend, int * bytesSended) {
	int ret = 0;
	if (mSocket && buffer && bytesToSend > 0 && gWSAGetLastError && gsend) {
		ret = gsend((SOCKET)mSocket, (const char *)buffer, bytesToSend, 0);
		if (SOCKET_ERROR != ret) {
			if (bytesSended) {
				*bytesSended = ret;
			}
			else {
				throw glWin32APIException(L"send", gWSAGetLastError());
			}
			return true;
		}
	}
	return false;
}

bool glSocket::recvData(void * buffer, const int bytesToRecv, int * bytesRecved) {
	int ret = 0;
	if (mSocket && buffer && bytesToRecv > 0 && gWSAGetLastError && grecv) {
		ret = grecv((SOCKET)mSocket, (char *)buffer, bytesToRecv, 0);
		if (SOCKET_ERROR != ret) {
			if (bytesRecved) {
				*bytesRecved = ret;
			}
			return true;
		}
		else {
			throw glWin32APIException(L"recv", gWSAGetLastError());
		}
	}
	return false;
}

bool glSocket::sendAllData(const void * buffer, const int bytesToSend) {
	char * bufferTemp = (char *)buffer;
	int bytesSended = 0;
	if (mSocket && bufferTemp && bytesToSend > 0 && gWSAGetLastError && gsend) {
		while (true) {
			int ret = gsend((SOCKET)mSocket, &(bufferTemp[bytesSended]), bytesToSend - bytesSended, 0);
			if (SOCKET_ERROR != ret) {
				bytesSended += ret;
				if (bytesSended >= bytesToSend) {
					return true;
				}
			}
			else {
				throw glWin32APIException(L"send", gWSAGetLastError());
			}
		}
	}
	return false;
}

bool glSocket::recvAllData(void * buffer, const int bytesToRecv) {
	char * bufferTemp = (char *)buffer;
	int bytesRecved = 0;
	if (mSocket && bufferTemp && bytesToRecv > 0 && gWSAGetLastError && grecv) {
		while (true) {
			int ret = grecv((SOCKET)mSocket, &(bufferTemp[bytesRecved]), bytesToRecv - bytesRecved, 0);
			if (SOCKET_ERROR != ret) {
				bytesRecved += ret;
				if (bytesRecved >= bytesToRecv) {
					return true;
				}
			}
			else {
				throw glWin32APIException(L"send", gWSAGetLastError());
			}
		}
	}
	return false;
}

bool glSocket::acceptClientConnect(glSocket & clientSock) {
	sockaddr_in sockAddr = { 0 };
	int sockAddrSize = sizeof(sockAddr);
	SOCKET clientWinSock = 0;
	if (mSocket && gaccept) {
		clientWinSock = gaccept((SOCKET)mSocket, (sockaddr *)&sockAddr, &sockAddrSize);
		if (INVALID_SOCKET != clientWinSock) {
			clientSock.bindClientSocket(clientWinSock);
			return true;
		}
	}
	return false;
}

void glSocket::bindClientSocket(const int socket) {
	destroy();
	if (socket) {
		mSocket = socket;
		mClientSocket = true;
		mServerSocket = false;
	}
}
