
#include "CompileConfig.h"

GL_TEST_CASE(TestException) {
	try {
		wlProcess process;
		process.createByProcessID(0);
	}
	catch (const glException & exception) {
		OutputDebugStringW(exception.getMessage());
		OutputDebugStringW(L"\r\n");
	}
}
