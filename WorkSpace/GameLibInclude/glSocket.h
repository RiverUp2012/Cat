
#pragma once

#include "glNonCopyable.h"

//
// @brief ÍøÂç Socket Àà
//
class glSocket : public glNonCopyable {
public:
	glSocket();
private:
	glSocket(const int socket);
public:
	virtual ~glSocket();
public:
	bool createForClient(void);
	bool createForServerA(const char * ipV4, const short int port);
	void destroy(void);
	bool connectToServerA(const char * ipV4, const short int port);
	bool sendData(const void * buffer, const int bytesToSend, int * bytesSended);
	bool recvData(void * buffer, const int bytesToRecv, int * bytesRecved);
	bool sendAllData(const void * buffer, const int bytesToSend);
	bool recvAllData(void * buffer, const int bytesToRecv);
private:
	int mSocket;
	bool mClientSocket;
	bool mServerSocket;
};
