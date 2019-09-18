
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

namespace {
	static bool gInitFlag = false;
	static glArray<glStringW> gParamArray;

	static void glInitCmdLine(void) {
		wchar_t * cmdLine = 0;
		wchar_t ** paramArray = 0;
		int paramCount = 0;
		if (!gInitFlag) {
			cmdLine = GetCommandLineW();
			if (cmdLine) {
				paramArray = CommandLineToArgvW(cmdLine, &paramCount);
				if (paramArray && gParamArray.resize(paramCount)) {
					for (int i = 0; i < paramCount; ++i) {
						gParamArray.setAt(i, paramArray[i]);
					}
				}
				else {
					throw glWin32APIException(L"CommandLineToArgvW", GetLastError());
				}
				if (paramArray) {
					LocalFree(paramArray);
					paramArray = 0;
				}
			}
			else {
				throw glWin32APIException(L"GetCommandLineW", GetLastError());
			}
			gInitFlag = true;
		}
	}
}

bool glCmdLine::getParamByIndexW(const int index, glStringW & param) {
	glInitCmdLine();
	if (index >= 0 && index < gParamArray.getCapacity()) {
		param = gParamArray.getAt(index);
		return true;
	}
	return false;
}

bool glCmdLine::isParamExistW(const wchar_t * param, int * index) {
	glInitCmdLine();
	if (param) {
		for (int i = 0; i < gParamArray.getCapacity(); ++i) {
			if (0 == wcscmp(param, gParamArray.getAt(i))) {
				if (index) {
					*index = i;
				}
				return true;
			}
		}
	}
	return false;
}

bool glCmdLine::getSwitchValueW(const wchar_t * switchName, glStringW & value) {
	int paramIndex = 0;
	if (switchName) {
		if (isParamExistW(switchName, &paramIndex)) {
			if (getParamByIndexW(paramIndex + 1, value)) {
				return true;
			}
		}
	}
	return false;
}
