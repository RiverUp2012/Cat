
#include "../GameLib.h"

namespace {
	struct glUnitTestInfo {
		glUnitTestProc mTestProc;
		glUnitTestInfo * mNext;
	};
	static glUnitTestInfo * gTestProcList = 0;
}

void glUnitTest::pushUnitTestProc(glUnitTestProc testProc) {
	if (testProc) {
		glUnitTestInfo * testInfo = new glUnitTestInfo();
		testInfo->mTestProc = testProc;
		testInfo->mNext = 0;
		if (!gTestProcList) {
			gTestProcList = testInfo;
		}
		else {
			testInfo->mNext = gTestProcList;
			gTestProcList = testInfo;
		}
	}
}

void glUnitTest::runAllTestCase(void) {
	glUnitTestInfo * testInfo = gTestProcList;
	while (testInfo) {
		glUnitTestInfo * nextTestInfo = testInfo->mNext;
		if (testInfo->mTestProc) {
			testInfo->mTestProc();
		}
		delete testInfo;
		testInfo = nextTestInfo;
	}
}
