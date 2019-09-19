
#include "CompileConfig.h"

GL_TEST_CASE(TestWriteFile) {
	try {
		glFile file;
		if (file.openW(L"D:\\unexist-file.ext", false, true)) {
			file.write("aaa", 3);
		}
		file.close();
	}
	catch (const glException & exception) {
		OutputDebugStringW(exception.getMessage());
		OutputDebugStringW(L"\r\n");
	}
}

GL_TEST_CASE(TestReadFile) {
	try {
		glFile file;
		char buffer[32] = { 0 };
		if (file.openW(L"D:\\unexist-file.ext", true, false)) {
			file.read(buffer, 3);
		}
		file.close();
	}
	catch (const glException & exception) {
		OutputDebugStringW(exception.getMessage());
		OutputDebugStringW(L"\r\n");
	}
}

GL_TEST_CASE(TestReadWriteFile) {
	try {
		glFile file;
		char buffer[32] = { 0 };
		if (file.openW(L"D:\\unexist-file.ext", true, true)) {
			file.write("aaa", 3);
			file.seekToBegin();
			file.read(buffer, 3);
		}
		file.close();
	}
	catch (const glException & exception) {
		OutputDebugStringW(exception.getMessage());
		OutputDebugStringW(L"\r\n");
	}
}
