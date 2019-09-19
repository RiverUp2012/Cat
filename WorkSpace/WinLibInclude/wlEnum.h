
#pragma once

//
// @brief 进程特性枚举体
//
enum wlProcessFeature {
	// 终止进程
	WL_PROCESS_FEATURE_TERMINATE = (1 << 0),
	// 查询进程信息
	WL_PROCESS_FEATURE_QUERY_INFO = (1 << 2),
	// 操纵进程虚拟内存
	WL_PROCESS_FEATURE_VM_OPERATION = (1 << 3),
};
