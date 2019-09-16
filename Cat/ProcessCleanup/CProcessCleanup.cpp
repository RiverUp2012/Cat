
#include "stdafx.h"
#include "CProcessCleanup.h"

// 默认每隔多少毫秒清理一次进程（30 秒清理一次）
#define DEFAULT_CLEANUP_TIME_INTERVAL (1000 * 30)

namespace {
	// 每隔多少毫秒清理一次进程
	static int gCleanupTimeInterval = DEFAULT_CLEANUP_TIME_INTERVAL;
	static std::vector<std::wstring> gProcessExeFileNameArray;
	static glMutex gProcessExeFileNameArrayLock;

	class MyThread : public glThread {
	public:
		void onThreadRun(void) override {
			while (true) {
				wlProcessEnumCallbackWarpper pecw;
				pecw.enumProcess();
				for (auto iter = pecw.getProcessInfoList().begin(); iter.isValid(); iter.moveNext()) {
					wlProcess process;
					if (process.openByProcessID(
						iter.getData().mProcessID,
						WL_PROCESS_FEATURE_QUERY_INFO | WL_PROCESS_FEATURE_QUERY_INFO)) {
						glStringW imageFileName;
						if (process.getImageFileNameW(imageFileName)) {
							glStringW fileName;
							if (glPathHelper::getFileNameWithExtW(imageFileName.getString(), fileName)) {
								if (processCanKillW(imageFileName.getString())) {
									process.terminate();
								}
							}
						}
						process.close();
					}
				}
				Sleep(gCleanupTimeInterval);
			}
		}
	private:
		bool processCanKillW(const wchar_t * imageFileName) const {
			glMutexGuard mutexGuard(&gProcessExeFileNameArrayLock);
			if (imageFileName) {
				for (const auto & processExeFileName : gProcessExeFileNameArray) {
					if (0 == _wcsicmp(imageFileName, processExeFileName.c_str())) {
						return true;
					}
				}
			}
			return false;
		}
	};

	static MyThread gThread;
}

void CProcessCleanup::startup(
	const int cleanupTimeInterval) {
	gCleanupTimeInterval = cleanupTimeInterval;
	if (gCleanupTimeInterval <= 0) {
		gCleanupTimeInterval = DEFAULT_CLEANUP_TIME_INTERVAL;
	}
	gThread.create(true);
}

void CProcessCleanup::shutdown(void) {

}

bool CProcessCleanup::addProcessExeFileNameW(
	const wchar_t * processExeFileName) {
	glMutexGuard mutexGuard(&gProcessExeFileNameArrayLock);
	if (processExeFileName) {
		gProcessExeFileNameArray.push_back(processExeFileName);
	}
	return false;
}

void CProcessCleanup::removeAllProcessExeFileName(void) {
	glMutexGuard mutexGuard(&gProcessExeFileNameArrayLock);
	gProcessExeFileNameArray.clear();
}
