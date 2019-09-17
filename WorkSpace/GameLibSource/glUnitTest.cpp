
#include "../GameLib.h"

namespace {
	static glList<glUnitTestProc> gTestProcList;
}

void glUnitTest::pushUnitTestProc(glUnitTestProc testProc) {
	if (testProc) {
		gTestProcList.pushBack(testProc);
	}
}

void glUnitTest::runAllTestProc(void) {
	for (glList<glUnitTestProc>::glIterator iter = gTestProcList.begin(); iter.isValid(); iter.moveNext()) {
		glUnitTestProc testProc = iter.getData();
		if (testProc) {
			testProc();
		}
	}
}
