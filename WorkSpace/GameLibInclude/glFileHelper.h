
#pragma once

class glFileEnumHandler;

//
// @brief 文件工具类
//
class glFileHelper {
public:
	static bool deleteFileW(const wchar_t * fileName);
	static void enumFileW(
		const wchar_t * path,
		const wchar_t * fileExt,
		glFileEnumHandler * enumHandler);
};
