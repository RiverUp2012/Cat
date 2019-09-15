
#include "../WinLib.h"
#include "../Include/WinLibPrivate.h"

void wlProcessHelper::enumProcess(wlProcessEnumCallback * callback) {
	HANDLE snapshotHandle = 0;
	PROCESSENTRY32W processEntry = { 0 };
	if (callback) {
		snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE != snapshotHandle) {
			processEntry.dwSize = sizeof(processEntry);
			if (Process32FirstW(snapshotHandle, &processEntry)) {
				do {
					if (!callback->onEnumProcessW(
						processEntry.th32ProcessID,
						processEntry.szExeFile)) {
						break;
					}
				} while (Process32NextW(snapshotHandle, &processEntry));
			}
			CloseHandle(snapshotHandle);
			snapshotHandle = 0;
		}
	}
}
