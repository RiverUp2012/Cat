
#pragma once

#include "glString.h"

//
// @brief 路径工具类
//
class glPathHelper {
public:
	static bool getFileNameWithExtW(const wchar_t * path, glStringW & fileNameWithExt);
	static bool getDriveW(const wchar_t * path, glStringW & drive);
	static bool getAppPathW(glStringW & appPath);
	static void pathAppendSlashW(glStringW & path);
	static void createPathW(const wchar_t * path);
};
