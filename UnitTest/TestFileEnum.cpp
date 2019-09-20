
#include "CompileConfig.h"

class MyFileEnumHandler : public glFileEnumHandler {
public:
	virtual bool onFileEnumW(
		const wchar_t * filePath,
		const wchar_t * fileName,
		const bool isDirectory) override {
		glLog::putMessageW(L"%s%s", filePath, fileName);
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
