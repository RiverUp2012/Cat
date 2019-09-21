
#include "../GameLibInclude/glUnitTest.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glLog.h"

namespace {
	struct glUnitTestInfo {
		wchar_t mCaseName[260];
		glUnitTestProc mTestProc;
		glUnitTestInfo * mNext;
	};
	static glUnitTestInfo * gTestProcList = 0;
}

void glUnitTest::pushUnitTestProcW(const wchar_t * caseName, glUnitTestProc testProc) {
	if (testProc) {
		glUnitTestInfo * testInfo = new glUnitTestInfo();
		testInfo->mCaseName[0] = glStringW::getNullChar();
		if (caseName) {
			glStringW::copy(testInfo->mCaseName, caseName, 0);
		}
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
		glLog::putMessageW(L"------ Run Test Case : [%s] ------\r\n", testInfo->mCaseName);
		if (testInfo->mTestProc) {
			testInfo->mTestProc();
		}
		delete testInfo;
		testInfo = nextTestInfo;
	}
	gTestProcList = 0;
}
