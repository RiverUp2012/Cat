
#include "stdafx.h"
#include "CRemoteControlServer.h"
#include "RemoteControlCommon.h"

namespace
{
	static T_OBJECT gServerSock = 0;
	static T_OBJECT gClientSock = 0;
	static T_OBJECT gMutex = 0;
	static T_OBJECT gThread = 0;

	//
	// ����˴������Կͻ��˵��������ݰ�
	//
	static void serverHandlePack(const SPack & pack)
	{
		if (PROTOCOL_REQUEST_USER_NAME == pack.mProtocol)
		{

		}
	}

	//
	// ������߳�
	//
	static void serverSockThread(
		T_OBJECT thread,
		void * userData)
	{
		bool done = false;

		if (gServerSock)
		{
			// �������Կͻ��˵�����

			while (!gClientSock)
			{
				gClientSock = TNetSockAcceptConnect(gServerSock);
			}
		}

		if (gClientSock)
		{
			while (!done)
			{
				SPack pack;

				// ��ȡ���Կͻ��˵�����

				if (TNetSockRecvDataV2(gClientSock, &pack, sizeof(SPackHeader)))
				{
					// ���������Ƿ���Ч

					if (0 == memcmp(PACK_SIG, pack.mSig, sizeof(pack.mSig)) &&
						PACK_VER_MAJOR == pack.mVerMajor &&
						PACK_VER_MINOR == pack.mVerMinor &&
						pack.mProtocol > PROTOCOL_FIRST &&
						pack.mPackSize < PROTOCOL_LAST)
					{
						if (0 == pack.mPackSize)
						{
							// ���ڲ����κΰ����ݵ�����ֱ�Ӵ�������

							serverHandlePack(pack);
						}
						else
						{
							// ���ڴ������ݵ������ȶ�ȡ�����ݣ��ٴ�������

							pack.mData = TMalloc(pack.mPackSize);
							if (pack.mData)
							{
								// ��ȡ������

								if (TNetSockRecvDataV2(gClientSock, pack.mData, pack.mPackSize))
								{
									// �������Կͻ��˵�����

									serverHandlePack(pack);
								}
								else
								{
									done = true;
								}

								TFree(pack.mData);
								pack.mData = 0;
							}
						}
					}
					else
					{
						done = true;
					}
				}
				else
				{
					done = true;
				}

				Sleep(100);
			}
		}
	}
}

void CRemoteControlServer::startup(void)
{
	shutdown();

	if (TNetDeviceStartup())
	{
		gServerSock = TNetSockCreateServer(REMOTE_CONTROL_IP, REMOTE_CONTROL_PORT);
		if (gServerSock)
		{
			gMutex = TMutexCreate();
			gThread = TThreadCreateW(serverSockThread, 0, T_TRUE, 0);
		}
	}
}

void CRemoteControlServer::shutdown(void)
{
	TNetDeviceShutdown();
}
