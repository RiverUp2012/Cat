
#include "CompileConfig.h"

GL_TEST_CASE(TestException) {
	try {
		wlProcess process;
		// ���Դ�һ������ id Ϊ 0 �Ľ��̣���������������Ȼ��ʧ�ܣ������㿪��
		process.createByProcessID(0);
	}
	catch (const glException & exception) {
		OutputDebugStringW(exception.getMessage());
		OutputDebugStringW(L"\r\n");
	}
}
