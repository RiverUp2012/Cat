
#include "stdafx.h"
#include "CRemoteControlClient.h"
#include "RemoteControlCommon.h"

namespace {
	static glSocket gClientSocket;
}

bool CRemoteControlClient::startupW(const wchar_t * serverIPv4, const short int serverPort) {
	GL_LOG_FUNC;
	shutdown();
	if (gClientSocket.createForClient()) {
		if (gClientSocket.connectToServerW(serverIPv4, serverPort)) {
			return true;
		}
	}
	return false;
}

void CRemoteControlClient::shutdown(void) {
	GL_LOG_FUNC;
	gClientSocket.destroy();
}

bool CRemoteControlClient::requestUserNameW(glStringW & userName) {
	bool ret = false;
	SPack pack;
	glMemFile memFile;
	//
	// ����ͷ
	//
	makePackHeader(pack, PROTOCOL_REQUEST_USER_NAME);
	//
	// ���������������
	//
	if (gClientSocket.sendAllData(&pack, sizeof(SPackHeader))) {
		//
		// ���ܷ���������Ӧ����ͷ��
		//
		if (gClientSocket.recvAllData(&pack, sizeof(SPackHeader))) {
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
						if (gClientSocket.recvAllData(pack.mData, pack.mPackSize)) {
							if (readMemFileStringW(memFile, userName)) {
								ret = true;
							}
						}
					}
				}
			}
		}
	}
	return ret;
}
