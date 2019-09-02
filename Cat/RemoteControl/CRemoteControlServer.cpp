
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
	// 服务端处理来自客户端的网络数据包
	//
	static void serverHandlePack(const SPack & pack)
	{
		if (PROTOCOL_REQUEST_USER_NAME == pack.mProtocol)
		{

		}
	}

	//
	// 服务端线程
	//
	static void serverSockThread(
		T_OBJECT thread,
		void * userData)
	{
		bool done = false;

		if (gServerSock)
		{
			// 接受来自客户端的连接

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

				// 读取来自客户端的请求

				if (TNetSockRecvDataV2(gClientSock, &pack, sizeof(SPackHeader)))
				{
					// 看看请求是否有效

					if (0 == memcmp(PACK_SIG, pack.mSig, sizeof(pack.mSig)) &&
						PACK_VER_MAJOR == pack.mVerMajor &&
						PACK_VER_MINOR == pack.mVerMinor &&
						pack.mProtocol > PROTOCOL_FIRST &&
						pack.mPackSize < PROTOCOL_LAST)
					{
						if (0 == pack.mPackSize)
						{
							// 对于不带任何包数据的请求，直接处理请求

							serverHandlePack(pack);
						}
						else
						{
							// 对于带包数据的请求，先读取包数据，再处理请求

							pack.mData = TMalloc(pack.mPackSize);
							if (pack.mData)
							{
								// 读取包数据

								if (TNetSockRecvDataV2(gClientSock, pack.mData, pack.mPackSize))
								{
									// 处理来自客户端的请求

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
