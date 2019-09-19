
#pragma once

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
};
