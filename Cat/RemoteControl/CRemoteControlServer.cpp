
#include "stdafx.h"
#include "CRemoteControlServer.h"
#include "RemoteControlCommon.h"

namespace {
	static glSocket gServerSocket;
	static glSocket gClientSocket;
	static glMutex gMutex;
	static bool gQuitFlag = false;

	class ServerThread : public glThread {
	public:
		void onThreadRun(void) override {
			while (!gQuitFlag) {
				glMutexGuard mutexGuard(&gMutex);
				if (!gClientSocket.isAlready()) {
					if (gServerSocket.canReadNow()) {
						if (!gServerSocket.acceptClientConnect(gClientSocket)) {
							glLog::putMessageA("gServerSocket.acceptClientConnect() failed");
							break;
						}
					}
					else {
						glThread::sleepCurrentThread(1);
					}
				}
				else {
					if (gClientSocket.canReadNow()) {
						SPack pack;
						bool done = false;
						if (gClientSocket.recvAllData(&pack, sizeof(SPackHeader))) {
							if (isPackValid(pack)) {
								if (pack.mPackSize > 0) {
									pack.mData = malloc(pack.mPackSize);
									if (pack.mData) {
										if (gClientSocket.recvAllData(pack.mData, pack.mPackSize)) {
											done = true;
										}
									}
									else {
										break;
									}
								}
								else {
									done = true;
								}
								if (done) {
									handlePack(pack);
								}
								if (pack.mData) {
									free(pack.mData);
									pack.mData = 0;
								}
							}
							else {
								glLog::putMessageA("invalid pack header");
							}
						}
						else {
							break;
						}
					}
					else {
						glThread::sleepCurrentThread(1);
					}
				}
			}
		}
	private:
		void handlePack(const SPack & pack) const {
			if (PROTOCOL_REQUEST_USER_NAME == pack.mProtocol) {
				handleRequestUserName();
			}
		}
	private:
		bool handleRequestUserName(void) const {
			bool ret = false;
			glStringW userName;
			glMemFile memFile;
			SPack pack;
			//
			// 填充包头
			//
			makePackHeader(pack, PROTOCOL_RESPONSE_USER_NAME);
			if (glSystemHelper::getCurrentUserNameW(userName)) {
				//
				// 为包体分配内存
				//
				pack.mPackSize = calcMemStringSizeW(userName);
				pack.mData = new unsigned char[pack.mPackSize];
				if (pack.mData) {
					memFile.open(pack.mData, pack.mPackSize, true);
					//
					// 填充包体
					//
					if (writeMemFileStringW(memFile, userName)) {
						//
						// 发送包头
						//
						if (gClientSocket.sendAllData(&pack, sizeof(SPackHeader))) {
							//
							// 发送包体
							//
							if (gClientSocket.sendAllData(pack.mData, pack.mPackSize)) {
								ret = true;
							}
						}
					}
				}
			}
			return ret;
		}
	};

	static ServerThread gServerThread;
}

bool CRemoteControlServer::startup(void) {
	GL_LOG_FUNC;
	glStringA localIpV4;
	shutdown();
	gQuitFlag = false;
	glMutexGuard mutexGuard(&gMutex);
	if (glNetHelper::getLocalMachineIPv4A(localIpV4)) {
		if (gServerSocket.createForServerA(localIpV4, REMOTE_CONTROL_PORT)) {
			if (gServerThread.create(true)) {
				return true;
			}
		}
	}
	return false;
}

void CRemoteControlServer::shutdown(void) {
	GL_LOG_FUNC;
	gQuitFlag = true;
	glMutexGuard mutexGuard(&gMutex);
	try {
		gServerThread.wait(1000);
		gServerThread.destroy();
		gClientSocket.destroy();
		gServerSocket.destroy();
	}
	catch (const glException & exception) {
		glLog::putMessageW(L"exception : %s", exception.getMessage());
	}
}
