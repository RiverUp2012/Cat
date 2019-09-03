
#ifndef TURBOLIB_H
#define TURBOLIB_H

//---------------------------------------------------------------
// @file TurboLib.h
// @brief 实用函数库
// @author Neko
// @e-mail NekoMasutaDev@gmail.com
// @e-mail NekoMasutaDev@outlook.com
//---------------------------------------------------------------

//---------------------------------------------------------------
// include
// 包含常用的标准 C 头文件
//---------------------------------------------------------------

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <memory.h>

//---------------------------------------------------------------
// define
// 宏定义
//---------------------------------------------------------------

// 逻辑假宏
#define T_FALSE (0)
// 逻辑真宏
#define T_TRUE (1)

//---------------------------------------------------------------
// typedef
// 数据类型别名定义
//---------------------------------------------------------------

// 对象数据类型
typedef void * T_OBJECT;

//---------------------------------------------------------------
// dictionary
// 字典相关接口
//---------------------------------------------------------------

//
// 字典回调函数类型
//
// dictionary 字典对象
// key 键
// data 值
// userData 用户数据
//
typedef int(*TDictionaryCallbackProc)(
	T_OBJECT dictionary,
	const wchar_t * key,
	void * data,
	void * userData);

//
// 创建字典
//
// bucketCount 字典中包含多少个桶，桶的数量最好是质数
//
extern T_OBJECT TDictionaryCreate(
	const int bucketCount);

//
// 销毁字典
//
// dictionary 字典对象
// forEachProc 回调函数，用于在销毁字典的过程中，回调每一个数据给用户
// userData 用户数据，将依样传递给 forEachProc
//
extern void TDictionaryDestroy(
	T_OBJECT dictionary,
	TDictionaryCallbackProc forEachProc,
	void * userData);

//
// 塞数据到字典里面
//
// dictionary 字典对象
// key 键
// data 值
//
// 返回 T_TRUE 表示成功，返回 T_FALSE 表示失败
//
extern int TDictionaryPutData(
	T_OBJECT dictionary,
	const wchar_t * key,
	void * data);

//
// 从字典中取出数据
//
// dictionary 字典对象
// key 键
// error 若不为 0，用于保存错误信息
//
// 返回用户塞进去的数据
//
extern void * TDictionaryGetData(
	T_OBJECT dictionary,
	const wchar_t * key,
	int * error);

//
// 判断字典中是否包含指定键
//
extern int TDictionaryContain(
	T_OBJECT dictionary,
	const wchar_t * key);

//
// 从字典中移除指定键
//
extern int TDictionaryRemove(
	T_OBJECT dictionary,
	const wchar_t * key,
	TDictionaryCallbackProc removeProc,
	void * userData);

//---------------------------------------------------------------
// hash
// 哈希散列相关接口
//---------------------------------------------------------------

//
// 计算指定字符串的哈希值
//
extern int THashStringW(
	const wchar_t * string);
extern int THashStringA(
	const char * string);

//---------------------------------------------------------------
// math
// 数学相关接口
//---------------------------------------------------------------

//
// 计算指定整形值的绝对值
//
extern int TAbsInt(
	const int value);

//
// 计算指定单精度浮点型值的绝对值
//
extern float TAbsFloat(
	const float value);

//
// 计算指定双精度浮点型值的绝对值
//
extern double TAbsDouble(
	const double value);

//
// 初始化随机数
//
extern void TRandInit(void);

//
// 获取浮点型范围随机数
//
extern float TRandFloat(
	const float min,
	const float max);

//
// 获取整型范围随机数
//
extern int TRandInt(
	const int min,
	const int max);

//---------------------------------------------------------------
// string
// 字符串相关接口
//---------------------------------------------------------------

//
// 为字符串分配内存
//
// 使用 TFree() 释放该函数返回的字符串
//
extern wchar_t * TStringAllocW(
	const int capacity);
extern char * TStringAllocA(
	const int capacity);

//
// 计算指定字符串的长度
//
extern int TStringLengthW(
	const wchar_t * string);
extern int TStringLengthA(
	const char * string);

//
// 拷贝字符串，不做内存分配
//
extern wchar_t * TStringCopyW(
	wchar_t * destString,
	const wchar_t * sourceString,
	const int copyChars);
extern char * TStringCopyA(
	char * destString,
	const char * sourceString,
	const int copyChars);

//
// 拷贝字符串，做内存分配
//
// 使用 TFree() 释放该函数返回的字符串
//
extern wchar_t * TStringDuplicateW(
	const wchar_t * string);
extern char * TStringDuplicateA(
	const char * string);

//
// 判断指定字符串内容是否完全相等
//
extern int TStringIsEqualW(
	const wchar_t * destString,
	const wchar_t * sourceString);
extern int TStringIsEqualA(
	const char * destString,
	const char * sourceString);

//
// 将 wchar_t 字符串转换为 char 字符串
//
// 使用 TFree() 释放该函数返回的字符串
//
extern char * TStringW2A(
	const wchar_t * stringW);

//
// 将 char 字符串转换为 wchar_t 字符串
//
// 使用 TFree() 释放该函数返回的字符串
//
extern wchar_t * TStringA2W(
	const char * stringA);

//
// 格式化字符串
//
// 使用 TFree() 释放该函数返回的字符串
//
extern wchar_t * TStringFormatW(
	const wchar_t * format,
	...);
extern char * TStringFormatA(
	const char * format,
	...);

//
// 格式化字符串
//
// 使用 TFree() 释放该函数返回的字符串
//
extern wchar_t * TStringFormatVW(
	const wchar_t * format,
	const va_list vl);
extern char * TStringFormatVA(
	const char * format,
	const va_list vl);

//---------------------------------------------------------------
// list
// 双向链表相关接口
//---------------------------------------------------------------

//
// 链表回调函数
//
typedef int(*TListCallbackProc)(
	T_OBJECT list,
	void * data,
	void * userData);

//
// 创建链表
//
extern T_OBJECT TListCreate(void);

//
// 销毁链表
//
extern void TListDestroy(
	T_OBJECT list,
	TListCallbackProc forEachProc,
	void * userData);

//
// 获取链表中已经添加了多少数据
//
extern int TListGetNodeCount(
	T_OBJECT list);

//
// 遍历链表中的所有数据
//
extern void TListForEach(
	T_OBJECT list,
	TListCallbackProc forEachProc,
	void * userData);

//
// 将数据添加到链表尾部
//
extern int TListAddDataToTail(
	T_OBJECT list,
	void * data);

//
// 将数据添加到链表头部
//
extern int TListAddDataToHead(
	T_OBJECT list,
	void * data);

//---------------------------------------------------------------
// array
// 自增长数组相关接口
//---------------------------------------------------------------

//
// 数组回调函数
//
typedef int (* TArrayCallbackProc)(
	T_OBJECT array,
	void * data,
	void * userData);

//
// 创建数组
//
// capacity 数组容量
//
extern T_OBJECT TArrayCreate(
	const int capacity);

//
// 销毁数组
//
extern void TArrayDestroy(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData);

//
// 清空数组
//
extern void TArrayClear(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData);

//
// 添加数据到数组，若数组容量不足，自动增长数组容量
//
extern int TArrayAddData(
	T_OBJECT array,
	void * data);

//
// 从数组的指定下标处获取数据
//
extern void * TArrayGetAt(
	T_OBJECT array,
	const int index);

//
// 将数据放入到数组的指定下标处
//
extern int TArraySetAt(
	T_OBJECT array,
	const int index,
	void * data);

//
// 获取数组容量
//
extern int TArrayGetCapacity(
	T_OBJECT array);

//
// 获取数组中已经添加了多少数据
//
extern int TArrayGetAddedItems(
	T_OBJECT array);

//
// 遍历数组中的所有数据
//
extern void TArrayForEach(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData);

//
// 设置数组自增长容量
//
extern void TArraySetGrowUnits(
	T_OBJECT array,
	const int growUnits);

//
// 获取数组自增长容量
//
extern int TArrayGetGrowUnits(
	T_OBJECT array);

//
// 释放数组中的每个数据
//
// array 数组对象
// byCapacity 为真表示按 capacity 清空数组，为假表示按 items 清空数组
// 
// 此时，数组中的每个数据，必须是可以使用 TFree() 函数释放的
//
extern void TArrayFreeAllData(
	T_OBJECT array,
	const int byCapacity);

//
// 查找数组中是否存在数据为空的索引号
//
// array 数组对象
// byCapacity 为真表示按 capacity 查找，为假表示按 items 查找
//
// 若找到，返回下标值，若没找到，返回 -1
//
extern int TArrayFindEmpty(
	T_OBJECT array,
	const int byCapacity);

//---------------------------------------------------------------
// color
// argb 颜色相关接口
//---------------------------------------------------------------

//
// 通过 alpha、red、green、blue 生成 argb 值
//
extern unsigned int TColorGetARGB(
	const unsigned char alpha,
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue);

//
// 通过 red、green、blue 生成 argb 值，此时 alpha 分量为 255
//
extern unsigned int TColorGetRGB(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue);

//
// 从 argb 中获取 alpha 分量
//
extern unsigned char TColorGetAlpha(
	const unsigned int argb);

//
// 从 argb 中获取 red 分量
//
extern unsigned char TColorGetRed(
	const unsigned int argb);

//
// 从 argb 中获取 green 分量
//
extern unsigned char TColorGetGreen(
	const unsigned int argb);

//
// 从 argb 中获取 blue 分量
//
extern unsigned char TColorGetBlue(
	const unsigned int argb);

//
// 设置 argb 的 alpha 分量
//
extern unsigned int TColorSetAlpha(
	unsigned int * argb,
	const unsigned char alpha);

//
// 设置 argb 的 red 分量
//
extern unsigned int TColorSetRed(
	unsigned int * argb,
	const unsigned char red);

//
// 设置 argb 的 green 分量
//
extern unsigned int TColorSetGreen(
	unsigned int * argb,
	const unsigned char green);

//
// 设置 argb 的 blue 分量
//
extern unsigned int TColorSetBlue(
	unsigned int * argb,
	const unsigned char blue);

//---------------------------------------------------------------
// file
// 文件相关接口
//---------------------------------------------------------------

//
// 打开文件
//
extern T_OBJECT TFileOpenW(
	const wchar_t * fileName,
	const int forRead,
	const int forWrite);
extern T_OBJECT TFileOpenA(
	const char * fileName,
	const int forRead,
	const int forWrite);

//
// 关闭文件
//
extern void TFileClose(
	T_OBJECT file);

//
// 获取文件大小
//
extern int TFileGetSize(
	T_OBJECT file,
	long long int * fileSize);

//
// 从文件中读取数据
//
extern int TFileRead(
	T_OBJECT file,
	void * buffer,
	const int bytesToRead);

//
// 将数据写入到文件
//
extern int TFileWrite(
	T_OBJECT file,
	const void * buffer,
	const int bytesToWrite);

//
// 设置文件指针到指定位置
//
extern int TFileSeekTo(
	T_OBJECT file,
	const long long int toPos);

//
// 设置文件指针到文件起始处
//
extern int TFileSeekToBegin(
	T_OBJECT file);

//
// 设置文件指针到文件结尾处
//
extern int TFileSeekToEnd(
	T_OBJECT file);

//
// 偏移文件指针
//
extern int TFileSeekOffset(
	T_OBJECT file,
	const long long int offset);

//
// 获取文件指针
//
extern int TFileGetPointer(
	T_OBJECT file,
	long long int * pointer);

//---------------------------------------------------------------
// file system
// 文件系统相关接口
//---------------------------------------------------------------

//
// 文件枚举回调函数
//
typedef int(*TEnumFileCallbackProcW)(
	const wchar_t * path,
	const wchar_t * fileName,
	const int isDirectory,
	void * userData);
typedef int(*TEnumFileCallbackProcA)(
	const char * path,
	const char * fileName,
	const int isDirectory,
	void * userData);

//
// 删除文件
//
extern int TFileSystemDeleteFileW(
	const wchar_t * fileName);
extern int TFileSystemDeleteFileA(
	const char * fileName);

//
// 枚举文件
//
extern void TFileSystemEnumFileW(
	const wchar_t * path,
	const wchar_t * fileExt,
	TEnumFileCallbackProcW enumFileProc,
	void * userData);
extern void TFileSystemEnumFileA(
	const char * path,
	const char * fileExt,
	TEnumFileCallbackProcA enumFileProc,
	void * userData);

//
// 判断文件是否存在
//
extern int TFileSystemIsFileExistW(
	const wchar_t * fileName);
extern int TFileSystemIsFileExistA(
	const char * fileName);

//
// 判断指定路径是否目录
//
extern int TFileSystemIsPathDirectoryW(
	const wchar_t * path);
extern int TFileSystemIsPathDirectoryA(
	const char * path);

//
// 创建目录链
//
extern void TFileSystemCreateDirectoryW(
	const wchar_t * directory);
extern void TFileSystemCreateDirectoryA(
	const char * directory);

//---------------------------------------------------------------
// file path
// 文件路径相关接口
//---------------------------------------------------------------

//
// 在路径的末尾追加目录分隔符，如果不存在的话
//
extern wchar_t * TFilePathAppendSlashW(
	wchar_t * path);
extern char * TFilePathAppendSlashA(
	char * path);

//
// 将指定字符串追加到指定路径末尾
//
extern wchar_t * TFilePathAppendW(
	wchar_t * path,
	const wchar_t * append);
extern char * TFilePathAppendA(
	char * path,
	const char * append);

//---------------------------------------------------------------
// memory
// 内存相关接口
//---------------------------------------------------------------

//
// 分配内存
//
extern void * TMalloc(
	const int bytesToMalloc);

//
// 分配内存，并将内存区清零
//
extern void * TMalloc0(
	const int bytesToMalloc);

//
// 释放内存
//
extern void TFree(
	void * bufferToFree);

//
// 重新分配内存
//
extern void * TRealloc(
	void * bufferToRealloc,
	const int bytesToRealloc);

//
// 使用指定的值填充内存区
//
extern void * TMemset(
	void * buffer,
	const int bytesToSet,
	const unsigned char valueToSet);

//---------------------------------------------------------------
// thread
// 线程相关接口
//---------------------------------------------------------------

//
// 线程函数
//
typedef void(*TThreadProc)(
	T_OBJECT thread,
	void * userData);

//
// 创建线程
//
extern T_OBJECT TThreadCreateW(
	TThreadProc threadProc,
	void * userData,
	const int runNow,
	const wchar_t * threadName);

//
// 销毁线程
//
extern void TThreadDestroy(
	T_OBJECT thread,
	const int waitTimeout);

//
// 强制杀死线程
//
extern void TThreadKill(
	T_OBJECT thread);

//
// 挂起线程
//
extern int TThreadSuspend(
	T_OBJECT thread);

//
// 恢复线程
//
extern int TThreadResume(
	T_OBJECT thread);

//
// 等待线程
//
extern int TThreadWait(
	T_OBJECT thread,
	const int waitTimeout);

//
// 获取线程用户数据
//
extern void * TThreadGetUserData(
	T_OBJECT thread);

//
// 获取线程函数
//
extern TThreadProc TThreadGetThreadProc(
	T_OBJECT thread);

//
// 获取线程名称
//
extern const wchar_t * TThreadGetNameW(
	T_OBJECT thread);

//
// 获取线程 id
//
extern unsigned int TThreadGetId(
	T_OBJECT thread);

//
// 令当前线程睡眠指定时长
//
extern void TThreadCurrentSleep(
	const int sleepTime);

//
// 获取当前线程对象
//
extern T_OBJECT TThreadGetCurrent(void);

//---------------------------------------------------------------
// mutex
// 互斥量相关接口
//---------------------------------------------------------------

//
// 创建互斥量
//
extern T_OBJECT TMutexCreate(void);

//
// 销毁互斥量
//
extern void TMutexDestroy(
	T_OBJECT mutex);

//
// 锁定互斥量
//
extern void TMutexLock(
	T_OBJECT mutex);

//
// 解锁互斥量
//
extern void TMutexUnlock(
	T_OBJECT mutex);

//---------------------------------------------------------------
// event
// 事件相关接口
//---------------------------------------------------------------

//
// 创建事件
//
extern T_OBJECT TEventCreateW(
	const int manualReset,
	const int initialState,
	const wchar_t * eventName);
extern T_OBJECT TEventCreateA(
	const int manualReset,
	const int initialState,
	const char * eventName);

//
// 打开事件
//
extern T_OBJECT TEventOpenW(
	const wchar_t * eventName);
extern T_OBJECT TEventOpenA(
	const char * eventName);

//
// 销毁事件
//
extern void TEventDestroy(
	T_OBJECT event);

//
// 等待事件进入激发状态
//
extern int TEventWait(
	T_OBJECT event,
	const int waitTimeout);

//
// 令事件进入激发状态
//
extern int TEventSet(
	T_OBJECT event);

//
// 令事件退出激发状态
//
extern int TEventReset(
	T_OBJECT event);

//---------------------------------------------------------------
// window
// 窗口相关接口
//---------------------------------------------------------------

//
// 窗口事件枚举体
//
enum
{
	T_WINDOW_EVENT_MOUSE_MOVE,
	T_WINDOW_EVENT_WHELL_UP,
	T_WINDOW_EVENT_WHELL_DOWN,
	T_WINDOW_EVENT_KEY_UP,
	T_WINDOW_EVENT_KEY_DOWN,
};

//
// 窗口事件回掉函数
//
typedef void(*TWindowEventCallbackProc)(
	T_OBJECT window,
	const int eventType,
	const int mouseX,
	const int mouseY,
	const int key);

//
// 创建窗口
//
extern T_OBJECT TWindowCreateW(
	const wchar_t * windowTitle,
	const int clientWidth,
	const int clientHeight,
	const int showNow);
extern T_OBJECT TWindowCreateA(
	const char * windowTitle,
	const int clientWidth,
	const int clientHeight,
	const int showNow);

//
// 销毁窗口
//
extern void TWindowDestroy(
	T_OBJECT window);

//
// 显示或隐藏窗口
//
extern int TWindowShow(
	T_OBJECT window,
	const int showOrHide);

//
// 处理所有窗口消息
//
extern int TWindowProcessMessage(void);

//
// 等待窗口消息
//
extern void TWindowWaitMessage(void);

//
// 判断指定窗口是否有效
//
extern int TWindowIsValid(
	T_OBJECT window);

//
// 将窗口放置于桌面中央
//
extern int TWindowPutDesktopCenter(
	T_OBJECT window);

//
// 设置窗口事件回掉函数
//
extern void TWindowSetEventCallback(
	T_OBJECT window,
	TWindowEventCallbackProc eventProc);

//
// 获取窗口事件回掉函数
//
extern TWindowEventCallbackProc TWindowGetEventCallback(
	T_OBJECT window);

//---------------------------------------------------------------
// module
// 模块相关接口
//---------------------------------------------------------------

//
// 加载模块
//
extern T_OBJECT TModuleLoadW(
	const wchar_t * moduleFileName);
extern T_OBJECT TModuleLoadA(
	const char * moduleFileName);

//
// 卸载模块
//
extern void TModuleUnload(
	T_OBJECT module);

//
// 从模块中导出函数地址
//
extern void * TModuleGetProcAddress(
	T_OBJECT module,
	const wchar_t * procName);

//
// 判断指定模块是否已经加载
//
extern int TModuleIsLoadedW(
	const wchar_t * moduleFileName);
extern int TModuleIsLoadedA(
	const char * moduleFileName);

//---------------------------------------------------------------
// resource
// 资源相关接口
//---------------------------------------------------------------

//
// 资源结构体
//
typedef struct _T_RESOURCE
{
	// 资源数据（只读）
	void * mData;
	// 资源大小
	int mSize;
}
T_RESOURCE;

//
// 加载资源
//
extern int TResourceLoadW(
	T_OBJECT module,
	const wchar_t * resourceType,
	const int resourceId,
	T_RESOURCE * resource);
extern int TResourceLoadA(
	T_OBJECT module,
	const char * resourceType,
	const int resourceId,
	T_RESOURCE * resource);

//
// 导出资源到指定文件
//
extern int TResourceExportToFileW(
	T_OBJECT module,
	const wchar_t * resourceType,
	const int resourceId,
	const wchar_t * fileName);
extern int TResourceExportToFileA(
	T_OBJECT module,
	const char * resourceType,
	const int resourceId,
	const char * fileName);

//---------------------------------------------------------------
// cmd line
// 命令行相关接口
//---------------------------------------------------------------

//
// 读取参数
//
extern int TCmdLineReadParam(
	const int paramIndex,
	wchar_t * param,
	const int paramSize);

//
// 判断指定参数是否存在
//
extern int TCmdLineIsParamPresented(
	const wchar_t * param,
	int * paramIndex);

//---------------------------------------------------------------
// os info
// 操作系统信息相关接口
//---------------------------------------------------------------

//
// 操作系统版本枚举体
//
enum
{
	T_OSVER_FIRST,
	T_OSVER_WIN2K,
	T_OSVER_WINXP,
	T_OSVER_WINXPSP1,
	T_OSVER_WINXPSP2,
	T_OSVER_WINXPSP3,
	T_OSVER_WINVISTA,
	T_OSVER_WINVISTASP1,
	T_OSVER_WINVISTASP2,
	T_OSVER_WIN7,
	T_OSVER_WIN7SP1,
	T_OSVER_WIN8,
	T_OSVER_WIN81,
	T_OSVER_WIN10,
};

//
// 操作系统功能枚举体
//
enum
{
	T_OSSETTING_FIRST,
	// 客户区动画功能
	T_OSSETTING_CLIENT_AREA_ANIMATION,
	// 窗口边缘阴影
	T_OSSETTING_DROP_SHADOW,
};

//
// 任务栏停靠在屏幕中的位置
//
enum
{
	//
	T_APPBAR_EDGE_FIRST,
	// 停靠在屏幕顶部
	T_APPBAR_EDGE_TOP,
	// 停靠在屏幕底部
	T_APPBAR_EDGE_BOTTOM,
	// 停靠在屏幕左侧
	T_APPBAR_EDGE_LEFT,
	// 停靠在屏幕右侧
	T_APPBAR_EDGE_RIGHT,
};

//
// 查询操作系统版本
//
extern int TOSInfoQueryVersion(
	int * osVer);

//
// 将操作系统版本号转换为容易阅读的字符串
//
extern int TOSInfoOSVersionToStringW(
	const int osVer,
	wchar_t * string,
	const int stringSize);
extern int TOSInfoOSVersionToStringA(
	const int osVer,
	char * string,
	const int stringSize);

//
// 获取操作系统是否 x64
//
extern int TOSInfoIsOSx64(
	int * isX64);

//
// 开启或关闭操作系统中的指定功能
//
extern int TOSInfoSettingTurn(
	const int settingType,
	const int onOrOff);

//
// 获取当前登录用户名称
//
extern int TOSInfoGetUserNameW(
	wchar_t * userName,
	const int userNameSize);
extern int TOSInfoGetUserNameA(
	char * userName,
	const int userNameSize);

//
// 获取任务栏在屏幕中的停靠位置
//
extern int TOSInfoGetAppBarEdge(
	int * appBarEdge);

//
// 获取任务栏在屏幕中的矩形区域
//
extern int TOSInfoGetAppBarRect(
	int * appBarLeft,
	int * appBarTop,
	int * appBarWidth,
	int * appBarHeight);

//
// 获取桌面大小
//
extern int TOSInfoGetDesktopSize(
	int * desktopWidth,
	int * desktopHeight);

//---------------------------------------------------------------
// hardware
// 硬件相关接口
//---------------------------------------------------------------

//
// 内存状态结构体
//
typedef struct _T_MEMORY_STATE
{
	// 总物理内存
	unsigned long long int mTotalPhys;
	// 可用物理内存
	unsigned long long int mAvailPhys;
	// 总虚拟内存
	unsigned long long int mTotalVirtual;
	// 可用虚拟内存
	unsigned long long int mAvailVirtual;
}
T_MEMORY_STATE;

//
// 获取内存状态
//
extern int TMemoryQueryState(
	T_MEMORY_STATE * memoryState);

//---------------------------------------------------------------
// process
// 进程相关接口
//---------------------------------------------------------------

//
// 进程回调函数
//
typedef int(*TProcessCallbackProc)(
	const unsigned int processId,
	void * userData);

//
// 获取当前进程是否 x64 进程
//
extern int TProcessIsX64(void);

//
// 枚举所有进程
//
extern int TProcessEnum(
	TProcessCallbackProc enumProc,
	void * userData);

//
// 通过进程 id，查询进程 exe 文件路径
//
extern int TProcessQueryImageNameByProcessIdW(
	const unsigned int processId,
	wchar_t * imageName,
	const int imageNameSize);

//
// 终止指定进程
//
extern int TProcessTerminate(
	const unsigned int processId);

//---------------------------------------------------------------
// share memory
// 共享内存相关接口
//---------------------------------------------------------------

//
// 打开共享内存，若不存在，则创建
//
extern T_OBJECT TShareMemoryOpenW(
	const wchar_t * name,
	const int sizeForCreate);
extern T_OBJECT TShareMemoryOpenA(
	const char * name,
	const int sizeForCreate);

//
// 关闭共享内存
//
extern void TShareMemoryClose(
	T_OBJECT shareMemory);

//
// 将数据写入共享内存
//
extern int TShareMemoryWrite(
	T_OBJECT shareMemory,
	const void * data,
	const int offset,
	const int bytesToWrite);

//
// 从共享内存中读取数据
//
extern int TShareMemoryRead(
	T_OBJECT shareMemory,
	void * data,
	const int offset,
	const int bytesToRead);

//---------------------------------------------------------------
// directory
// 目录相关接口
//---------------------------------------------------------------

//
// 获取应用程序所在目录
//
extern int TDirectoryGetAppW(
	wchar_t * appDir,
	const int appDirSize);
extern int TDirectoryGetAppA(
	char * appDir,
	const int appDirSize);

//---------------------------------------------------------------
// d3d9 paint device
// d3d9 绘图设备相关接口
//---------------------------------------------------------------

//
// 创建 d3d9 绘图设备
//
extern T_OBJECT TD3D9PaintDeviceCreate(
	T_OBJECT window,
	const int bufferWidth,
	const int bufferHeight,
	const int fullscreen,
	const int vsync);

//
// 销毁 d3d9 绘图设备
//
extern void TD3D9PaintDeviceDestroy(
	T_OBJECT d3d9PaintDevice);

//
// 清空 d3d9 绘图设备
//
extern int TD3D9PaintDeviceClear(
	T_OBJECT d3d9PaintDevice,
	const unsigned int clearColor);

//
// 呈现 d3d9 绘图设备
//
extern int TD3D9PaintDevicePresent(
	T_OBJECT d3d9PaintDevice);

//---------------------------------------------------------------
// d3d9 font
// d3d9 字体相关接口
//---------------------------------------------------------------

//
// 创建 d3d9 字体
//
extern T_OBJECT TD3D9FontCreateW(
	T_OBJECT d3d9PaintDevice,
	const wchar_t * fontName,
	const int fontWidth,
	const int fontHeight);
extern T_OBJECT TD3D9FontCreateA(
	T_OBJECT d3d9PaintDevice,
	const char * fontName,
	const int fontWidth,
	const int fontHeight);

//
// 销毁 d3d9 字体
//
extern void TD3D9FontDestroy(
	T_OBJECT d3d9Font);

//
// 绘制字符串
//
extern int TD3D9FontPaintTextW(
	T_OBJECT d3d9Font,
	const wchar_t * text,
	const int charsToPaint,
	const int x,
	const int y,
	const int width,
	const int height,
	const unsigned int format,
	const unsigned int color);

//
// 计算字符串大小
//
extern int TD3D9FontCalcTextSizeW(
	T_OBJECT d3d9Font,
	const wchar_t * text,
	const int charsToCalc,
	const int layoutWidth,
	const int layoutHeight,
	const unsigned int format,
	int * width,
	int * height);

//---------------------------------------------------------------
// d3d9 graph
// d3d9 graph 相关接口
//---------------------------------------------------------------

//
// 从图像文件创建 d3d9 graph
//
extern T_OBJECT TD3D9GraphCreateFromImageFileW(
	T_OBJECT d3d9PaintDevice,
	const wchar_t * imageFileName,
	const unsigned int colorKey);

//
// 销毁 d3d9 graph 对象
//
extern void TD3D9GraphDestroy(
	T_OBJECT d3d9Graph);

//
// 绘制 d3d9 graph 对象到指定位置
//
extern void TD3D9GraphPaintV1(
	T_OBJECT d3d9Graph,
	const float graphX,
	const float graphY);

//---------------------------------------------------------------
// ds8 sound device
// ds8 音频设备相关接口
//---------------------------------------------------------------

//
// 创建 ds8 音频设备
//
extern T_OBJECT TDS8SoundDeviceCreate(
	T_OBJECT window);

//
// 销毁 ds8 音频设备
//
extern void TDS8SoundDeviceDestroy(
	T_OBJECT ds8SoundDevice);

//---------------------------------------------------------------
// ds8 sound buffer
// ds8 音频缓冲相关接口
//---------------------------------------------------------------

//
// 创建 ds8 音频缓冲
//
extern T_OBJECT TDS8SoundBufferCreate(
	T_OBJECT ds8SoundDevice,
	const unsigned int bufferSize,
	const unsigned short channels,
	const unsigned short bitsPerSample,
	const unsigned int sampleRate);

//
// 通过 wave 文件，创建 ds8 音频缓冲
//
extern T_OBJECT TDS8SoundBufferCreateFromWaveFileW(
	T_OBJECT ds8SoundDevice,
	const wchar_t * waveFileName);

//
// 销毁 ds8 音频缓冲区
//
extern void TDS8SoundBufferDestroy(
	T_OBJECT ds8SoundBuffer);

//
// 播放 ds8 音频缓冲区
//
extern int TDS8SoundBufferPlay(
	T_OBJECT ds8SoundBuffer,
	const int loop);

//
// 停止 ds8 音频缓冲区
//
extern int TDS8SoundBufferStop(
	T_OBJECT ds8SoundBuffer);

//
// 设置 ds8 音频缓冲区音量
//
extern int TDS8SoundBufferSetVolume(
	T_OBJECT ds8SoundBuffer,
	const float volume);

//
// 获取 ds8 音频缓冲区音量
//
extern int TDS8SoundBufferGetVolume(
	T_OBJECT ds8SoundBuffer,
	float * volume);

//
// 锁定 ds8 音频缓冲区音量
//
extern void * TDS8SoundBufferLock(
	T_OBJECT ds8SoundBuffer,
	const int offsetToLock,
	const int bytesToLock);

//
// 解锁 ds8 音频缓冲区音量
//
extern int TDS8SoundBufferUnlock(
	T_OBJECT ds8SoundBuffer);

//---------------------------------------------------------------
// ini file
// ini 配置文件相关接口
//---------------------------------------------------------------

//
// 创建 ini 配置文件
//
extern T_OBJECT TIniFileCreateW(
	const wchar_t * iniFileName);

//
// 销毁 ini 配置文件
//
extern void TIniFileDestroy(
	T_OBJECT iniFile);

//
// 从 ini 配置文件读取字符串
//
extern int TIniFileReadStringW(
	T_OBJECT iniFile,
	const wchar_t * sectionName,
	const wchar_t * keyName,
	wchar_t * value,
	const int valueSize);

//
// 从 ini 配置文件读取整形
//
extern int TIniFileReadIntW(
	T_OBJECT iniFile,
	const wchar_t * sectionName,
	const wchar_t * keyName,
	int * value);

//---------------------------------------------------------------
// page
// 分页相关接口
//---------------------------------------------------------------

extern T_OBJECT TPageCreate(
	const int itemPerPage);

extern void TPageDestroy(
	T_OBJECT page,
	TArrayCallbackProc forEachProc,
	void * userData);

extern void TPageNextItem(
	T_OBJECT page);

extern void TPagePrevItem(
	T_OBJECT page);

extern void TPageNextPage(
	T_OBJECT page);

extern void TPagePrevPage(
	T_OBJECT page);

extern int TPageAddItem(
	T_OBJECT page,
	void * item);

extern void * TPageGetCurrentItem(
	T_OBJECT page);

extern int TPageGetTotalItem(
	T_OBJECT page);

extern int TPageGetCurrentPage(
	T_OBJECT page);

extern int TPageGetTotalPage(
	T_OBJECT page);

//---------------------------------------------------------------
// log
// 日志相关接口
//---------------------------------------------------------------

//
// 启动日志
//
extern int TLogStartupW(
	const wchar_t * logFileName,
	const int toDebugView);
extern int TLogStartupA(
	const char * logFileName,
	const int toDebugView);

//
// 关闭日志
//
extern void TLogShutdown(void);

//
// 写入格式化日志信息
//
extern int TLogWriteFormatMessageW(
	const wchar_t * format,
	...);
extern int TLogWriteFormatMessageA(
	const char * format,
	...);

//
// 写入日志信息
//
extern int TLogWriteMesageW(
	const wchar_t * message);
extern int TLogWriteMesageA(
	const char * message);

//---------------------------------------------------------------
// net
// 网络相关接口
//---------------------------------------------------------------

//
// 启动网络设备
//
extern int TNetDeviceStartup(void);

//
// 关闭网络设备
//
extern void TNetDeviceShutdown(void);

//
// 创建一个客户端 sock
//
extern T_OBJECT TNetSockCreateClient(void);

//
// 创建一个服务端 sock
//
extern T_OBJECT TNetSockCreateServer(
	const char * ipV4,
	const short int port);

//
// 销毁 sock
//
extern void TNetSockDestroy(
	T_OBJECT sock);

//
// 令客户端 sock 连接到服务端 sock
//
extern int TNetSockConnect(
	T_OBJECT sock,
	const char * ipV4,
	const short int port);

//
// 令服务端 sock 等待客户端 sock 的连接
//
extern T_OBJECT TNetSockAcceptConnect(
	T_OBJECT sock);

//
// 发送数据到指定 sock
//
extern int TNetSockSendData(
	T_OBJECT sock,
	const void * data,
	const int bytesToSend,
	int * bytesSended);

//
// 发送指定大小的数据到指定 sock，直到所有数据发送完毕，或出错
//
extern int TNetSockSendDataV2(
	T_OBJECT sock,
	const void * data,
	const int bytesToSend);

//
// 从指定 sock 读取数据
//
extern int TNetSockRecvData(
	T_OBJECT sock,
	void * data,
	const int bytesToRecv,
	int * bytesRecved);

//
// 从指定 sock 读取指定大小的数据，直到所有数据读取完毕，或出错
//
extern int TNetSockRecvDataV2(
	T_OBJECT sock,
	void * data,
	const int bytesToRecv);

//---------------------------------------------------------------
// path
// 文件路径相关接口
//---------------------------------------------------------------

//
// 从路径中抽取出包含扩展名的文件名
//
// path 要抽取文件名的文件路径
// fileNameWithExt 用于保存抽取出来的文件名
// fileNameWithExtSize fileNameWithExt 参数的容量
//
// 返回真表示成功，返回假表示失败
//
extern int TPathExtractFileNameWithExtW(
	const wchar_t * path,
	wchar_t * fileNameWithExt,
	const int fileNameWithExtSize);

#endif // TURBOLIB_H
