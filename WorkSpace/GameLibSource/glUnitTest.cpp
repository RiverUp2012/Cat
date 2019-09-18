
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

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
		testInfo->mCaseName[0] = L'\0';
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
		OutputDebugStringW(L"------ Run Test Case : ");
		OutputDebugStringW(testInfo->mCaseName);
		OutputDebugStringW(L" ------\r\n");
		if (testInfo->mTestProc) {
			testInfo->mTestProc();
		}
		delete testInfo;
		testInfo = nextTestInfo;
	}
}
