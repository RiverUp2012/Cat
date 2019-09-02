
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
			// ���ӵ������

			if (TNetSockConnect(sock, REMOTE_CONTROL_IP, REMOTE_CONTROL_PORT))
			{
				// �����˷�������

				memcpy(pack.mSig, PACK_SIG, sizeof(pack.mSig));
				pack.mVerMajor = PACK_VER_MAJOR;
				pack.mVerMinor = PACK_VER_MINOR;
				pack.mProtocol = PROTOCOL_REQUEST_USER_NAME;

				if (TNetSockSendDataV2(sock, &pack, sizeof(SPackHeader)))
				{
					// �������Է���˵���Ӧ

					if (TNetSockRecvDataV2(sock, &pack, sizeof(SPackHeader)))
					{
						// ��������˵���Ӧ�Ƿ���Ч

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

									// ��ȡ�û���

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
