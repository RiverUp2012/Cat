
#pragma once

//
// @brief 求取编译时大小已知的数组容量
//
#define GL_DIM(_Array) (sizeof(_Array) / sizeof(_Array[0]))

//
// @brief 格式化字符串
//
#define GL_FORMAT_W(_Format, _String, _Ret) \
{ \
if (_Format) \
{ \
	va_list vl = { 0 }; \
	va_start(vl, _Format); \
	_Ret = glStringHelper::formatW(_Format, vl, _String); \
	va_end(vl); \
} \
}

//
// @brief 格式化字符串
//
#define GL_FORMAT_A(_Format, _String, _Ret) \
{ \
if (_Format) \
{ \
	va_list vl = { 0 }; \
	va_start(vl, _Format); \
	_Ret = glStringHelper::formatA(_Format, vl, _String); \
	va_end(vl); \
} \
}

//
// @brief 将 TCHAR 字符串转换为 char 字符串
//
#if defined UNICODE || defined _UNICODE
#define GL_T2A(_StringT, _StringA, _Ret) \
{ \
	_Ret = glStringHelper::w2a(_StringT, _StringA); \
}
#else
#define GL_T2A(_StringT, _StringA, _Ret) \
{ \
	_StringT = _StringA; \
	_Ret = true; \
}
#endif

//
// @brief 将 TCHAR 字符串转换为 wchar_t 字符串
//
#if defined UNICODE || defined _UNICODE
#define GL_T2W(_StringT, _StringW, _Ret) \
{ \
	_StringW = _StringT; \
	_Ret = true; \
}
#else
#define GL_T2W(_StringT, _StringW, _Ret) \
{ \
	_Ret = glStringHelper::a2w(_StringT, _StringW); \
}
#endif
