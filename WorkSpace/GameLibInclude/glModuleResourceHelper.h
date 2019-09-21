
#pragma once

class glModule;

//
// @brief 模块资源助手类
//
class glModuleResourceHelper {
public:
	struct glResourceInfo {
		void * mData;
		int mSize;
	};
public:
	static bool getResourceW(
		const int resourceID,
		const wchar_t * resourceType,
		glResourceInfo & resourceInfo);
	static bool getResourceW(
		const glModule & module,
		const int resourceID,
		const wchar_t * resourceType,
		glResourceInfo & resourceInfo);
};
