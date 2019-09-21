
#include "stdafx.h"
#include "CRemoteControlClient.h"
#include "RemoteControlCommon.h"

bool CRemoteControlClient::requestUserNameW(
	glStringW & userName,
	const wchar_t * serverIPv4) {
	bool ret = false;
	glSocket clientSocket;
	SPack pack;
	glMemFile memFile;
	//
	// �����ͻ��� socket
	//
	if (clientSocket.createForClient()) {
		//
		// ���ӵ������
		//
		if (clientSocket.connectToServerW(serverIPv4, REMOTE_CONTROL_PORT)) {
			//
			// ����ͷ
			//
			makePackHeader(pack, PROTOCOL_REQUEST_USER_NAME);
			//
			// ���������������
			//
			if (clientSocket.sendAllData(&pack, sizeof(SPackHeader))) {
				//
				// ���ܷ���������Ӧ����ͷ��
				//
				if (clientSocket.recvAllData(&pack, sizeof(SPackHeader))) {
					//
					// �жϰ�ͷ�Ƿ���Ч
					//
					if (isPackValid(pack) && PROTOCOL_RESPONSE_USER_NAME == pack.mProtocol) {
						//
						// Ϊ��������ڴ�
						//
						if (pack.mPackSize > 0) {
							pack.mData = new unsigned char[pack.mPackSize];
							if (pack.mData) {
								memFile.open(pack.mData, pack.mPackSize, true);
								//
								// ���ܷ���������Ӧ�����壩
								//
								if (clientSocket.recvAllData(pack.mData, pack.mPackSize)) {
									if (readMemFileStringW(memFile, userName)) {
										ret = true;
									}
								}
							}
						}
					}
				}
			}
		}
		clientSocket.destroy();
	}
	return ret;
}
