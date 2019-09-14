
#include "../Include/WinLib.h"

namespace wl {

	static Mutex gMutex;

	bool Log::openW(const wchar_t * logFileName) {
		MutexGuard mutexGuard(&gMutex);
		if (logFileName) {
			return true;
		}
		return false;
	}

	void Log::close(void) {
		MutexGuard mutexGuard(&gMutex);
	}

	bool Log::putMessageW(const wchar_t * format, ...) {
		MutexGuard mutexGuard(&gMutex);
		if (format) {
			
		}
		return false;
	}

} // namespace wl
