
#pragma once

//
// @brief 图元类型枚举体
//
enum glPrimitiveType {
	// 未知
	glPrimitiveTypeUnknown,
	// 点
	glPrimitiveTypePoint,
	// 线段
	glPrimitiveTypeLine,
	// 实心三角形
	glPrimitiveTypeTriangle,
};

//
// @brief 输入类型枚举体
//
enum glInputType {
	// 按键按下
	glInputTypeKeyDown,
	// 按键弹起
	glInputTypeKeyUp,
	// 鼠标移动
	glInputTypeMouseMove,
};
