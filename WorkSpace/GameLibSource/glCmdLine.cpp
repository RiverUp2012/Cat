
#include "../GameLibInclude/glCmdLine.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glArray.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glGlobalData.h"

typedef LPWSTR * (WINAPI *glCommandLineToArgvW)(
	LPCWSTR lpCmdLine,
	int* pNumArgs);

namespace {
	static bool gInitFlag = false;
	static glArray<glStringW> gParamArray;
	static glCommandLineToArgvW gCommandLineToArgvW = 0;

	static void glInitCmdLine(void) {
		wchar_t * cmdLine = 0;
		wchar_t ** paramArray = 0;
		int paramCount = 0;
		if (!gModule_Shell32.isAlready()) {
			if (gModule_Shell32.createW(L"shell32.dll")) {
				gCommandLineToArgvW = (glCommandLineToArgvW)
					gModule_Shell32.getProcAddressA("CommandLineToArgvW");
			}
		}
		if (!gInitFlag && gCommandLineToArgvW) {
			cmdLine = GetCommandLineW();
			if (cmdLine) {
				paramArray = gCommandLineToArgvW(cmdLine, &paramCount);
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
