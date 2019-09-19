
#include "CompileConfig.h"

GL_TEST_CASE(TestException) {
	try {
		wlProcess process;
		// 尝试打开一个进程 id 为 0 的进程，理论上来讲，必然打开失败，除非你开挂
		process.createByProcessID(0);
	}
	catch (const glException & exception) {
		OutputDebugStringW(exception.getMessage());
		OutputDebugStringW(L"\r\n");
	}
}
