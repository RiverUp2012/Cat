
#pragma once

class glModule;

//
// @brief ģ����Դ������
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
