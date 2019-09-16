
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

void wlProcessHelper::enumModule(const unsigned long processId, wlModuleEnumCallback * callback) {
	HANDLE snapshotHandle = 0;
	MODULEENTRY32W moduleEntry = { 0 };
	if (callback) {
		snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
		if (INVALID_HANDLE_VALUE != snapshotHandle) {
			moduleEntry.dwSize = sizeof(moduleEntry);
			if (Module32FirstW(snapshotHandle, &moduleEntry)) {
				do {
					if (!callback->onEnumModuleW(
						moduleEntry.szExePath,
						(void *)moduleEntry.hModule)) {
						break;
					}
				} while (Module32NextW(snapshotHandle, &moduleEntry));
			}
			CloseHandle(snapshotHandle);
			snapshotHandle = 0;
		}
	}
}
