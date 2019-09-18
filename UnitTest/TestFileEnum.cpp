
#include "../WorkSpace/GameLib.h"
#include <Windows.h>

class MyFileEnumHandler : public glFileEnumHandler {
public:
	virtual bool onFileEnumW(
		const wchar_t * filePath,
		const wchar_t * fileName,
		const bool isDirectory) override {
		OutputDebugStringW(filePath);
		OutputDebugStringW(fileName);
		OutputDebugStringW(L"\r\n");
		if (0 == _wcsicmp(L"Boot", fileName)) {
			glFileHelper::enumFileW(glStringW(filePath) + fileName, L"*.*", this);
		}
		return true;
	}
};

GL_TEST_CASE(TestFileEnum) {
	MyFileEnumHandler fileEnumHandler;
	glFileHelper::enumFileW(L"C:\\", L"*.*", &fileEnumHandler);
}
