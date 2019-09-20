
#include "CompileConfig.h"

int main(int argc, char * argv[]) {
	glLog::setAutoAppendNewLine(true);
	glLog::setOutputDebugView(true);
	glUnitTest::runAllTestCase();
	return 0;
}
