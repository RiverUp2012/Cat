
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
	// 创建客户端 socket
	//
	if (clientSocket.createForClient()) {
		//
		// 连接到服务端
		//
		if (clientSocket.connectToServerW(serverIPv4, REMOTE_CONTROL_PORT)) {
			//
			// 填充包头
			//
			makePackHeader(pack, PROTOCOL_REQUEST_USER_NAME);
			//
			// 向服务器发送请求
			//
			if (clientSocket.sendAllData(&pack, sizeof(SPackHeader))) {
				//
				// 接受服务器的响应（包头）
				//
				if (clientSocket.recvAllData(&pack, sizeof(SPackHeader))) {
					//
					// 判断包头是否有效
					//
					if (isPackValid(pack) && PROTOCOL_RESPONSE_USER_NAME == pack.mProtocol) {
						//
						// 为包体分配内存
						//
						if (pack.mPackSize > 0) {
							pack.mData = new unsigned char[pack.mPackSize];
							if (pack.mData) {
								memFile.open(pack.mData, pack.mPackSize, true);
								//
								// 接受服务器的响应（包体）
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
