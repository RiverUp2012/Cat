
#pragma once

//
// @brief �ļ�ö�ٴ�����
//
class glFileEnumHandler {
public:
	virtual bool onFileEnumW(
		const wchar_t * filePath,
		const wchar_t * fileName,
		const bool isDirectory) = 0;
};
