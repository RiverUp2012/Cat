
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
			glMutexGuard mutexGuard(&gMutex);
			while (!gQuitFlag) {
				if (!gClientSocket.isAlready()) {
					if (!gServerSocket.acceptClientConnect(gClientSocket)) {
						glLog::putMessageA("gServerSocket.acceptClientConnect() failed");
						break;
					}
				}
				else {
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
								done = false;
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
			glStringW userName;
			glMemFile memFile;
			SPack pack;
			makePackHeader(pack, PROTOCOL_RESPONSE_USER_NAME);
			if (glSystemHelper::getCurrentUserNameW(userName)) {
				pack.mPackSize = userName.getBufferSize();
				pack.mData = malloc(pack.mPackSize);
				memFile.open(pack.mData, pack.mPackSize, true);
				memFile.write(userName.getBuffer(), userName.getBufferSize());
				if (gServerSocket.sendAllData(&pack, sizeof(SPackHeader))) {
					if (gServerSocket.sendAllData(pack.mData, pack.mPackSize)) {
						return true;
					}
				}
			}
			return false;
		}
	};

	static ServerThread gServerThread;
}

bool CRemoteControlServer::startup(const short int serverPort) {
	glStringA localIpV4;
	shutdown();
	glMutexGuard mutexGuard(&gMutex);
	if (glNetHelper::getLocalMachineIPv4A(localIpV4)) {
		if (gServerSocket.createForServerA(localIpV4, serverPort)) {
			gQuitFlag = false;
			if (gServerThread.create(true)) {
				return true;
			}
		}
	}
	return false;
}

void CRemoteControlServer::shutdown(void) {
	glMutexGuard mutexGuard(&gMutex);
	gQuitFlag = true;
	gServerThread.wait(1000);
	gServerThread.destroy();
	gClientSocket.destroy();
	gServerSocket.destroy();
}
