
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_NET (32)

typedef struct _T_NET
{
	SOCKET mWinSocket;
	// �Ƿ��Ѿ��ɹ�ִ���� bind ������ֻ�з���� sock ��Ҫִ�� bind ����
	int mBindFlag;
	// �Ƿ��Ѿ��ɹ�ִ���� listen ������ֻ�з���� sock ��Ҫִ�� listen ����
	int mListenFlag;
	// �Ƿ��Ѿ��ɹ�ִ���� connect ������ֻ�пͻ��� sock ��Ҫִ�� connect ����
	int mConnectFlag;
}
T_NET;

static T_NET gNetArray[T_MAX_NET] = { 0 };

static T_NET * TFindUnuseNet(void)
{
	for (int i = 0; i < T_MAX_NET; ++i)
	{
		if (!gNetArray[i].mWinSocket)
		{
			return &gNetArray[i];
		}
	}

	return 0;
}

int TNetDeviceStartup(void)
{
	WSADATA wsaData = { 0 };
	int ret = 0;

	ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (0 == ret)
	{
		return T_TRUE;
	}
	else if (WSAVERNOTSUPPORTED == ret)
	{
		ret = WSAStartup(wsaData.wHighVersion, &wsaData);
		if (0 == ret)
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

void TNetDeviceShutdown(void)
{
	WSACleanup();
}

T_OBJECT TNetSockCreateClient(void)
{
	T_NET * netImpl = TFindUnuseNet();
	if (netImpl)
	{
		netImpl->mWinSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET != netImpl->mWinSocket)
		{
			return (T_OBJECT)netImpl;
		}
	}

	return 0;
}

T_OBJECT TNetSockCreateServer(
	const char * ipV4,
	const short int port)
{
	struct sockaddr_in sockAddr = { 0 };

	T_NET * netImpl = TFindUnuseNet();
	if (netImpl && ipV4)
	{
		netImpl->mWinSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET != netImpl->mWinSocket)
		{
			sockAddr.sin_family = AF_INET;
			sockAddr.sin_addr.S_un.S_addr = inet_addr(ipV4);
			sockAddr.sin_port = htons(port);

			if (0 == bind(
				netImpl->mWinSocket,
				(const struct sockaddr *)&sockAddr,
				sizeof(sockAddr)))
			{
				netImpl->mBindFlag = T_TRUE;

				if (0 == listen(netImpl->mWinSocket, SOMAXCONN))
				{
					netImpl->mListenFlag = T_TRUE;

					return (T_OBJECT)netImpl;
				}
			}

			shutdown(netImpl->mWinSocket, SB_BOTH);
			closesocket(netImpl->mWinSocket);
			netImpl->mWinSocket = 0;
			netImpl->mBindFlag = T_FALSE;
			netImpl->mListenFlag = T_FALSE;
		}
	}

	return 0;
}

void TNetSockDestroy(
	T_OBJECT sock)
{
	T_NET * netImpl = (T_NET *)sock;
	if (netImpl)
	{
		if (netImpl->mWinSocket)
		{
			shutdown(netImpl->mWinSocket, SB_BOTH);
			closesocket(netImpl->mWinSocket);
			netImpl->mWinSocket = 0;
		}

		TMemset(netImpl, sizeof(T_NET), 0);
	}
}

int TNetSockConnect(
	T_OBJECT sock,
	const char * ipV4,
	const short int port)
{
	struct sockaddr_in sockAddr = { 0 };

	T_NET * netImpl = (T_NET *)sock;
	if (netImpl &&
		INVALID_SOCKET != netImpl->mWinSocket && // sock ������Ч
		!netImpl->mBindFlag && // �����ǿͻ��� sock �������ӵ������ sock
		!netImpl->mListenFlag &&
		!netImpl->mConnectFlag && // ֮ǰû�� connect ��
		ipV4)
	{
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_addr.S_un.S_addr = inet_addr(ipV4);
		sockAddr.sin_port = htons(port);

		if (0 == connect(
			netImpl->mWinSocket,
			(const struct sockaddr *)&sockAddr,
			sizeof(sockAddr)))
		{
			netImpl->mConnectFlag = T_TRUE;

			return T_TRUE;
		}
	}

	return T_FALSE;
}

T_OBJECT TNetSockAcceptConnect(
	T_OBJECT sock)
{
	struct sockaddr_in sockAddr = { 0 };
	int sockAddrSize = sizeof(sockAddr);
	T_NET * serverNetImpl = (T_NET *)sock;
	T_NET * clientNetImpl = TFindUnuseNet();

	if (serverNetImpl &&
		INVALID_SOCKET != serverNetImpl->mWinSocket &&
		serverNetImpl->mBindFlag && // �����Ƿ���� sock ���ܽ������Կͻ��� sock ������
		serverNetImpl->mListenFlag &&
		clientNetImpl)
	{
		clientNetImpl->mWinSocket = accept(
			serverNetImpl->mWinSocket,
			(struct sockaddr *)&sockAddr,
			&sockAddrSize);
		if (INVALID_SOCKET != clientNetImpl->mWinSocket)
		{
			clientNetImpl->mConnectFlag = T_TRUE;

			return (T_OBJECT)clientNetImpl;
		}
	}

	return 0;
}

int TNetSockSendData(
	T_OBJECT sock,
	const void * data,
	const int bytesToSend,
	int * bytesSended)
{
	int sendRet = 0;

	T_NET * netImpl = (T_NET *)sock;
	if (netImpl &&
		INVALID_SOCKET != netImpl->mWinSocket &&
		netImpl->mConnectFlag && // ֻ���Ѿ��ɹ� connect �� sock ���Է�������
		data &&
		bytesToSend > 0)
	{
		sendRet = send(netImpl->mWinSocket, (const char *)data, bytesToSend, 0);
		if (SOCKET_ERROR != sendRet)
		{
			if (bytesSended)
			{
				*bytesSended = sendRet;
			}

			return T_TRUE;
		}
	}

	return T_FALSE;
}

//
// ����ָ����С�����ݣ�ֱ���������ݷ�����ϣ������
//
int TNetSockSendDataV2(
	T_OBJECT sock,
	const void * data,
	const int bytesToSend)
{
	unsigned char * dataTemp = (unsigned char *)data;
	int bytesRemaind = bytesToSend; // ���ж�������û�з���

	if (sock && dataTemp && bytesRemaind > 0)
	{
		while (T_TRUE)
		{
			int bytesSended = 0; // ���η����˶�������

			if (TNetSockSendData(
				sock,
				&(dataTemp[bytesToSend - bytesRemaind]),
				bytesRemaind,
				&bytesSended))
			{
				bytesRemaind -= bytesSended;
				if (bytesRemaind <= 0)
				{
					return T_TRUE;
				}
			}
			else
			{
				break;
			}
		}
	}

	return T_FALSE;
}

int TNetSockRecvData(
	T_OBJECT sock,
	void * data,
	const int bytesToRecv,
	int * bytesRecved)
{
	int recvRet = 0;

	T_NET * netImpl = (T_NET *)sock;
	if (netImpl &&
		INVALID_SOCKET != netImpl->mWinSocket &&
		netImpl->mConnectFlag && // ֻ���Ѿ��ɹ� connect �� sock ���Խ�������
		data &&
		bytesToRecv > 0)
	{
		recvRet = recv(netImpl->mWinSocket, (char *)data, bytesToRecv, 0);
		if (SOCKET_ERROR != recvRet)
		{
			if (bytesRecved)
			{
				*bytesRecved = recvRet;
			}

			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TNetSockRecvDataV2(
	T_OBJECT sock,
	void * data,
	const int bytesToRecv)
{
	unsigned char * dataTemp = (unsigned char *)data;
	int bytesRemaind = bytesToRecv; // ���ж�������û�ж�ȡ

	if (sock && dataTemp && bytesRemaind > 0)
	{
		while (T_TRUE)
		{
			int bytesReaded = 0; // ���ζ�ȡ�˶�������

			if (TNetSockRecvData(
				sock,
				&(dataTemp[bytesToRecv - bytesRemaind]),
				bytesRemaind,
				&bytesReaded))
			{
				bytesRemaind -= bytesReaded;
				if (bytesRemaind <= 0)
				{
					return T_TRUE;
				}
			}
			else
			{
				break;
			}
		}
	}

	return T_FALSE;
}
