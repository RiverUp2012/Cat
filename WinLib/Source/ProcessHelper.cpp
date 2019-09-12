
#include "../Include/WinLib.h"

namespace wl {

	void ProcessHelper::enumProcess(ProcessEnumCallback * callback) {
		HANDLE snapshotHandle = 0;
		PROCESSENTRY32W processEntry = { 0 };
		if (callback) {
			snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (INVALID_HANDLE_VALUE != snapshotHandle) {
				processEntry.dwSize = sizeof(processEntry);
				if (Process32FirstW(snapshotHandle, &processEntry)) {
					do {
						if (!callback->onEnumProcess(processEntry.th32ProcessID)) {
							break;
						}
					} while (Process32NextW(snapshotHandle, &processEntry));
				}
				CloseHandle(snapshotHandle);
				snapshotHandle = 0;
			}
		}
	}

} // namespace wl
