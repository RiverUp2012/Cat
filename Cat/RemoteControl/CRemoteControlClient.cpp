
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
	// 填充包头
	//
	makePackHeader(pack, PROTOCOL_REQUEST_USER_NAME);
	//
	// 向服务器发送请求
	//
	if (gClientSocket.sendAllData(&pack, sizeof(SPackHeader))) {
		//
		// 接受服务器的响应（包头）
		//
		if (gClientSocket.recvAllData(&pack, sizeof(SPackHeader))) {
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
