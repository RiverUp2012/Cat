
#pragma once

//
// @brief ������Ԫ���Է�֧
//
#define GL_TEST_CASE(_CaseName) \
	extern void GL_TEST_PROC_##_CaseName(); \
class glTestRunner_##_CaseName \
{ \
public: \
	glTestRunner_##_CaseName() \
{ \
	glUnitTest::pushUnitTestProcW(L#_CaseName, GL_TEST_PROC_##_CaseName); \
} \
}; \
	static glTestRunner_##_CaseName gTestRunner##_CaseName; \
	void GL_TEST_PROC_##_CaseName()

//
// @brief ��Ԫ���Ժ���
//
typedef void(*glUnitTestProc)(void);

//
// @brief ��Ԫ������
//
class glUnitTest {
public:
	static void pushUnitTestProcW(const wchar_t * caseName, glUnitTestProc testProc);
	static void runAllTestCase(void);
};
