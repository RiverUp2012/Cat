
#include "stdafx.h"
#include "CRemoteControlClient.h"
#include "RemoteControlCommon.h"
#include "../Common/CMemoryReader.h"

namespace
{

}

void CRemoteControlClient::startup(void)
{
	shutdown();

	TNetDeviceStartup();
}

void CRemoteControlClient::shutdown(void)
{
	TNetDeviceShutdown();
}

bool CRemoteControlClient::requestUserNameW(
	wchar_t * userName,
	const int userNameSize)
{
	bool ret = false;
	T_OBJECT sock = 0;
	SPack pack;
	CMemoryReader memReader;

	if (userName && userNameSize > 0)
	{
		sock = TNetSockCreateClient();
		if (sock)
		{
			// 连接到服务端

			if (TNetSockConnect(sock, REMOTE_CONTROL_IP, REMOTE_CONTROL_PORT))
			{
				// 向服务端发送请求

				memcpy(pack.mSig, PACK_SIG, sizeof(pack.mSig));
				pack.mVerMajor = PACK_VER_MAJOR;
				pack.mVerMinor = PACK_VER_MINOR;
				pack.mProtocol = PROTOCOL_REQUEST_USER_NAME;

				if (TNetSockSendDataV2(sock, &pack, sizeof(SPackHeader)))
				{
					// 接受来自服务端的响应

					if (TNetSockRecvDataV2(sock, &pack, sizeof(SPackHeader)))
					{
						// 看看服务端的响应是否有效

						if (0 == memcmp(PACK_SIG, pack.mSig, sizeof(pack.mSig)) &&
							PACK_VER_MAJOR == pack.mVerMajor &&
							PACK_VER_MINOR == pack.mVerMinor &&
							PROTOCOL_RESPONSE_USER_NAME == pack.mProtocol)
						{
							pack.mData = TMalloc(pack.mPackSize);
							if (pack.mData)
							{
								if (TNetSockRecvDataV2(sock, pack.mData, pack.mPackSize))
								{
									memReader.bind(pack.mData, pack.mPackSize);

									// 读取用户名

									int stringLength = 0;
									memReader.read(&stringLength);
									if (stringLength < userNameSize)
									{
										memReader.read(userName, sizeof(wchar_t)* stringLength);
										userName[stringLength] = L'\0';

										ret = true;
									}
								}

								TFree(pack.mData);
								pack.mData = 0;
							}
						}
					}
				}
			}

			TNetSockDestroy(sock);
			sock = 0;
		}
	}

	return ret;
}
