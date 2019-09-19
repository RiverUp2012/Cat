
#pragma once

struct glSpriteVertex {
	float x, y, z, rhw;
	unsigned int diffuse;
	float u, v;
};

struct glPrimitiveVertex {
	float x, y, z, rhw;
	unsigned int diffuse;
};

//
// @brief 时间结构体
//
struct glTime {
	unsigned int mYear;
	unsigned int mMonth;
	unsigned int mDay;
	unsigned int mHour;
	unsigned int mMinute;
	unsigned int mSecond;
	unsigned int mMilliseconds;
};

//
// @brief 内存信息结构体
//
struct glMemoryInfo {
	unsigned long long int mPhysTotal;
	unsigned long long int mPhysAvail;
	unsigned long long int mVirtualTotal;
	unsigned long long int mVirtualAvail;
};
