
#include "stdafx.h"
#include "CProcessCleanup.h"

// Ĭ��ÿ�����ٺ�������һ�ν��̣�30 ������һ�Σ�
#define DEFAULT_CLEANUP_TIME_INTERVAL (1000 * 30)

namespace {
	// ÿ�����ٺ�������һ�ν���
	static int gCleanupTimeInterval = DEFAULT_CLEANUP_TIME_INTERVAL;
	static std::vector<std::wstring> gProcessExeFileNameArray;
	static wl::Mutex gProcessExeFileNameArrayLock;

	class MyThread : public wl::Thread {
	public:
		void onThreadRun(void) override {
			while (true) {
				wl::ProcessEnumCallbackWarpper pecw;
				pecw.enumProcess();
				for (const auto & processID : pecw.getProcessIDList()) {
					wl::Process process;
					if (process.openByProcessID(
						processID,
						wl::PROCESS_FEATURE_QUERY_INFO | wl::PROCESS_FEATURE_QUERY_INFO)) {
						std::wstring imageFileName;
						if (process.getImageFileNameW(imageFileName)) {
							std::wstring fileName;
							if (wl::PathHelper::getFileNameWithExtW(imageFileName.c_str(), fileName)) {
								if (processCanKillW(imageFileName.c_str())) {
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
			wl::MutexGuard mutexGuard(&gProcessExeFileNameArrayLock);
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
	wl::MutexGuard mutexGuard(&gProcessExeFileNameArrayLock);
	if (processExeFileName) {
		gProcessExeFileNameArray.push_back(processExeFileName);
	}
	return false;
}

void CProcessCleanup::removeAllProcessExeFileName(void) {
	wl::MutexGuard mutexGuard(&gProcessExeFileNameArrayLock);
	gProcessExeFileNameArray.clear();
}
