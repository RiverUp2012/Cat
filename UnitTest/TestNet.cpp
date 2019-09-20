
#include "CompileConfig.h"

GL_TEST_CASE(TestNet) {
	glStringW ipV4;
	if (glNetHelper::getLocalMachineIPv4W(ipV4)) {
		glLog::putMessageW(ipV4);
	}
}
