
#pragma once

//
// @brief ��ȡ����ʱ��С��֪����������
//
#define GL_DIM(_Array) (sizeof(_Array) / sizeof(_Array[0]))

//
// @brief ��ʽ���ַ���
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
// @brief ��ʽ���ַ���
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
// @brief �� TCHAR �ַ���ת��Ϊ char �ַ���
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
// @brief �� TCHAR �ַ���ת��Ϊ wchar_t �ַ���
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
