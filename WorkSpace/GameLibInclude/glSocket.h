
#pragma once

#include "glNonCopyable.h"

//
// @brief ÍøÂç Socket Àà
//
class glSocket : public glNonCopyable {
public:
	glSocket();
public:
	virtual ~glSocket();
public:
	bool createForClient(void);
	bool createForServerA(const char * ipV4, const short int port);
	void destroy(void);
	bool isAlready(void) const;
	bool connectToServerA(const char * ipV4, const short int port);
	bool connectToServerW(const wchar_t * ipV4, const short int port);
	bool sendData(const void * buffer, const int bytesToSend, int * bytesSended);
	bool recvData(void * buffer, const int bytesToRecv, int * bytesRecved);
	bool sendAllData(const void * buffer, const int bytesToSend);
	bool recvAllData(void * buffer, const int bytesToRecv);
	bool acceptClientConnect(glSocket & clientSock);
private:
#if defined WIN64 || defined _WIN64
	void bindClientSocket(const __int64 socket);
#else
	void bindClientSocket(const int socket);
#endif
private:
#if defined WIN64 || defined _WIN64
	__int64 mSocket;
#else
	int mSocket;
#endif
	bool mClientSocket;
	bool mServerSocket;
};
