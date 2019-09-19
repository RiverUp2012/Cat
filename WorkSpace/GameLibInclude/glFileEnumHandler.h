
#pragma once

//
// @brief 文件枚举处理类
//
class glFileEnumHandler {
public:
	virtual bool onFileEnumW(
		const wchar_t * filePath,
		const wchar_t * fileName,
		const bool isDirectory) = 0;
};
