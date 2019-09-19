
#pragma once

enum glPrimitiveType {
	glPrimitiveTypeUnknown,
	glPrimitiveTypePoint,
	glPrimitiveTypeLine,
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
