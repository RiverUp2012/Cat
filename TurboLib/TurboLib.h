
#ifndef TURBOLIB_H
#define TURBOLIB_H

//---------------------------------------------------------------
// @file TurboLib.h
// @brief ʵ�ú�����
// @author Neko
// @e-mail NekoMasutaDev@gmail.com
// @e-mail NekoMasutaDev@outlook.com
//---------------------------------------------------------------

//---------------------------------------------------------------
// include
// �������õı�׼ C ͷ�ļ�
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
// �궨��
//---------------------------------------------------------------

// �߼��ٺ�
#define T_FALSE (0)
// �߼����
#define T_TRUE (1)

//---------------------------------------------------------------
// typedef
// �������ͱ�������
//---------------------------------------------------------------

// ������������
typedef void * T_OBJECT;

//---------------------------------------------------------------
// dictionary
// �ֵ���ؽӿ�
//---------------------------------------------------------------

//
// �ֵ�ص���������
//
// dictionary �ֵ����
// key ��
// data ֵ
// userData �û�����
//
typedef int(*TDictionaryCallbackProc)(
	T_OBJECT dictionary,
	const wchar_t * key,
	void * data,
	void * userData);

//
// �����ֵ�
//
// bucketCount �ֵ��а������ٸ�Ͱ��Ͱ���������������
//
extern T_OBJECT TDictionaryCreate(
	const int bucketCount);

//
// �����ֵ�
//
// dictionary �ֵ����
// forEachProc �ص������������������ֵ�Ĺ����У��ص�ÿһ�����ݸ��û�
// userData �û����ݣ����������ݸ� forEachProc
//
extern void TDictionaryDestroy(
	T_OBJECT dictionary,
	TDictionaryCallbackProc forEachProc,
	void * userData);

//
// �����ݵ��ֵ�����
//
// dictionary �ֵ����
// key ��
// data ֵ
//
// ���� T_TRUE ��ʾ�ɹ������� T_FALSE ��ʾʧ��
//
extern int TDictionaryPutData(
	T_OBJECT dictionary,
	const wchar_t * key,
	void * data);

//
// ���ֵ���ȡ������
//
// dictionary �ֵ����
// key ��
// error ����Ϊ 0�����ڱ��������Ϣ
//
// �����û�����ȥ������
//
extern void * TDictionaryGetData(
	T_OBJECT dictionary,
	const wchar_t * key,
	int * error);

//
// �ж��ֵ����Ƿ����ָ����
//
extern int TDictionaryContain(
	T_OBJECT dictionary,
	const wchar_t * key);

//
// ���ֵ����Ƴ�ָ����
//
extern int TDictionaryRemove(
	T_OBJECT dictionary,
	const wchar_t * key,
	TDictionaryCallbackProc removeProc,
	void * userData);

//---------------------------------------------------------------
// hash
// ��ϣɢ����ؽӿ�
//---------------------------------------------------------------

//
// ����ָ���ַ����Ĺ�ϣֵ
//
extern int THashStringW(
	const wchar_t * string);
extern int THashStringA(
	const char * string);

//---------------------------------------------------------------
// math
// ��ѧ��ؽӿ�
//---------------------------------------------------------------

//
// ����ָ������ֵ�ľ���ֵ
//
extern int TAbsInt(
	const int value);

//
// ����ָ�������ȸ�����ֵ�ľ���ֵ
//
extern float TAbsFloat(
	const float value);

//
// ����ָ��˫���ȸ�����ֵ�ľ���ֵ
//
extern double TAbsDouble(
	const double value);

//
// ��ʼ�������
//
extern void TRandInit(void);

//
// ��ȡ�����ͷ�Χ�����
//
extern float TRandFloat(
	const float min,
	const float max);

//
// ��ȡ���ͷ�Χ�����
//
extern int TRandInt(
	const int min,
	const int max);

//---------------------------------------------------------------
// string
// �ַ�����ؽӿ�
//---------------------------------------------------------------

//
// Ϊ�ַ��������ڴ�
//
// ʹ�� TFree() �ͷŸú������ص��ַ���
//
extern wchar_t * TStringAllocW(
	const int capacity);
extern char * TStringAllocA(
	const int capacity);

//
// ����ָ���ַ����ĳ���
//
extern int TStringLengthW(
	const wchar_t * string);
extern int TStringLengthA(
	const char * string);

//
// �����ַ����������ڴ����
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
// �����ַ��������ڴ����
//
// ʹ�� TFree() �ͷŸú������ص��ַ���
//
extern wchar_t * TStringDuplicateW(
	const wchar_t * string);
extern char * TStringDuplicateA(
	const char * string);

//
// �ж�ָ���ַ��������Ƿ���ȫ���
//
extern int TStringIsEqualW(
	const wchar_t * destString,
	const wchar_t * sourceString);
extern int TStringIsEqualA(
	const char * destString,
	const char * sourceString);

//
// �� wchar_t �ַ���ת��Ϊ char �ַ���
//
// ʹ�� TFree() �ͷŸú������ص��ַ���
//
extern char * TStringW2A(
	const wchar_t * stringW);

//
// �� char �ַ���ת��Ϊ wchar_t �ַ���
//
// ʹ�� TFree() �ͷŸú������ص��ַ���
//
extern wchar_t * TStringA2W(
	const char * stringA);

//
// ��ʽ���ַ���
//
// ʹ�� TFree() �ͷŸú������ص��ַ���
//
extern wchar_t * TStringFormatW(
	const wchar_t * format,
	...);
extern char * TStringFormatA(
	const char * format,
	...);

//
// ��ʽ���ַ���
//
// ʹ�� TFree() �ͷŸú������ص��ַ���
//
extern wchar_t * TStringFormatVW(
	const wchar_t * format,
	const va_list vl);
extern char * TStringFormatVA(
	const char * format,
	const va_list vl);

//---------------------------------------------------------------
// list
// ˫��������ؽӿ�
//---------------------------------------------------------------

//
// ����ص�����
//
typedef int(*TListCallbackProc)(
	T_OBJECT list,
	void * data,
	void * userData);

//
// ��������
//
extern T_OBJECT TListCreate(void);

//
// ��������
//
extern void TListDestroy(
	T_OBJECT list,
	TListCallbackProc forEachProc,
	void * userData);

//
// ��ȡ�������Ѿ�����˶�������
//
extern int TListGetNodeCount(
	T_OBJECT list);

//
// ���������е���������
//
extern void TListForEach(
	T_OBJECT list,
	TListCallbackProc forEachProc,
	void * userData);

//
// ��������ӵ�����β��
//
extern int TListAddDataToTail(
	T_OBJECT list,
	void * data);

//
// ��������ӵ�����ͷ��
//
extern int TListAddDataToHead(
	T_OBJECT list,
	void * data);

//---------------------------------------------------------------
// array
// ������������ؽӿ�
//---------------------------------------------------------------

//
// ����ص�����
//
typedef int (* TArrayCallbackProc)(
	T_OBJECT array,
	void * data,
	void * userData);

//
// ��������
//
// capacity ��������
//
extern T_OBJECT TArrayCreate(
	const int capacity);

//
// ��������
//
extern void TArrayDestroy(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData);

//
// �������
//
extern void TArrayClear(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData);

//
// ������ݵ����飬�������������㣬�Զ�������������
//
extern int TArrayAddData(
	T_OBJECT array,
	void * data);

//
// �������ָ���±괦��ȡ����
//
extern void * TArrayGetAt(
	T_OBJECT array,
	const int index);

//
// �����ݷ��뵽�����ָ���±괦
//
extern int TArraySetAt(
	T_OBJECT array,
	const int index,
	void * data);

//
// ��ȡ��������
//
extern int TArrayGetCapacity(
	T_OBJECT array);

//
// ��ȡ�������Ѿ�����˶�������
//
extern int TArrayGetAddedItems(
	T_OBJECT array);

//
// ���������е���������
//
extern void TArrayForEach(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData);

//
// ������������������
//
extern void TArraySetGrowUnits(
	T_OBJECT array,
	const int growUnits);

//
// ��ȡ��������������
//
extern int TArrayGetGrowUnits(
	T_OBJECT array);

//
// �ͷ������е�ÿ������
//
// array �������
// byCapacity Ϊ���ʾ�� capacity ������飬Ϊ�ٱ�ʾ�� items �������
// 
// ��ʱ�������е�ÿ�����ݣ������ǿ���ʹ�� TFree() �����ͷŵ�
//
extern void TArrayFreeAllData(
	T_OBJECT array,
	const int byCapacity);

//
// �����������Ƿ��������Ϊ�յ�������
//
// array �������
// byCapacity Ϊ���ʾ�� capacity ���ң�Ϊ�ٱ�ʾ�� items ����
//
// ���ҵ��������±�ֵ����û�ҵ������� -1
//
extern int TArrayFindEmpty(
	T_OBJECT array,
	const int byCapacity);

//---------------------------------------------------------------
// color
// argb ��ɫ��ؽӿ�
//---------------------------------------------------------------

//
// ͨ�� alpha��red��green��blue ���� argb ֵ
//
extern unsigned int TColorGetARGB(
	const unsigned char alpha,
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue);

//
// ͨ�� red��green��blue ���� argb ֵ����ʱ alpha ����Ϊ 255
//
extern unsigned int TColorGetRGB(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue);

//
// �� argb �л�ȡ alpha ����
//
extern unsigned char TColorGetAlpha(
	const unsigned int argb);

//
// �� argb �л�ȡ red ����
//
extern unsigned char TColorGetRed(
	const unsigned int argb);

//
// �� argb �л�ȡ green ����
//
extern unsigned char TColorGetGreen(
	const unsigned int argb);

//
// �� argb �л�ȡ blue ����
//
extern unsigned char TColorGetBlue(
	const unsigned int argb);

//
// ���� argb �� alpha ����
//
extern unsigned int TColorSetAlpha(
	unsigned int * argb,
	const unsigned char alpha);

//
// ���� argb �� red ����
//
extern unsigned int TColorSetRed(
	unsigned int * argb,
	const unsigned char red);

//
// ���� argb �� green ����
//
extern unsigned int TColorSetGreen(
	unsigned int * argb,
	const unsigned char green);

//
// ���� argb �� blue ����
//
extern unsigned int TColorSetBlue(
	unsigned int * argb,
	const unsigned char blue);

//---------------------------------------------------------------
// file
// �ļ���ؽӿ�
//---------------------------------------------------------------

//
// ���ļ�
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
// �ر��ļ�
//
extern void TFileClose(
	T_OBJECT file);

//
// ��ȡ�ļ���С
//
extern int TFileGetSize(
	T_OBJECT file,
	long long int * fileSize);

//
// ���ļ��ж�ȡ����
//
extern int TFileRead(
	T_OBJECT file,
	void * buffer,
	const int bytesToRead);

//
// ������д�뵽�ļ�
//
extern int TFileWrite(
	T_OBJECT file,
	const void * buffer,
	const int bytesToWrite);

//
// �����ļ�ָ�뵽ָ��λ��
//
extern int TFileSeekTo(
	T_OBJECT file,
	const long long int toPos);

//
// �����ļ�ָ�뵽�ļ���ʼ��
//
extern int TFileSeekToBegin(
	T_OBJECT file);

//
// �����ļ�ָ�뵽�ļ���β��
//
extern int TFileSeekToEnd(
	T_OBJECT file);

//
// ƫ���ļ�ָ��
//
extern int TFileSeekOffset(
	T_OBJECT file,
	const long long int offset);

//
// ��ȡ�ļ�ָ��
//
extern int TFileGetPointer(
	T_OBJECT file,
	long long int * pointer);

//---------------------------------------------------------------
// file system
// �ļ�ϵͳ��ؽӿ�
//---------------------------------------------------------------

//
// �ļ�ö�ٻص�����
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
// ɾ���ļ�
//
extern int TFileSystemDeleteFileW(
	const wchar_t * fileName);
extern int TFileSystemDeleteFileA(
	const char * fileName);

//
// ö���ļ�
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
// �ж��ļ��Ƿ����
//
extern int TFileSystemIsFileExistW(
	const wchar_t * fileName);
extern int TFileSystemIsFileExistA(
	const char * fileName);

//
// �ж�ָ��·���Ƿ�Ŀ¼
//
extern int TFileSystemIsPathDirectoryW(
	const wchar_t * path);
extern int TFileSystemIsPathDirectoryA(
	const char * path);

//
// ����Ŀ¼��
//
extern void TFileSystemCreateDirectoryW(
	const wchar_t * directory);
extern void TFileSystemCreateDirectoryA(
	const char * directory);

//---------------------------------------------------------------
// file path
// �ļ�·����ؽӿ�
//---------------------------------------------------------------

//
// ��·����ĩβ׷��Ŀ¼�ָ�������������ڵĻ�
//
extern wchar_t * TFilePathAppendSlashW(
	wchar_t * path);
extern char * TFilePathAppendSlashA(
	char * path);

//
// ��ָ���ַ���׷�ӵ�ָ��·��ĩβ
//
extern wchar_t * TFilePathAppendW(
	wchar_t * path,
	const wchar_t * append);
extern char * TFilePathAppendA(
	char * path,
	const char * append);

//---------------------------------------------------------------
// memory
// �ڴ���ؽӿ�
//---------------------------------------------------------------

//
// �����ڴ�
//
extern void * TMalloc(
	const int bytesToMalloc);

//
// �����ڴ棬�����ڴ�������
//
extern void * TMalloc0(
	const int bytesToMalloc);

//
// �ͷ��ڴ�
//
extern void TFree(
	void * bufferToFree);

//
// ���·����ڴ�
//
extern void * TRealloc(
	void * bufferToRealloc,
	const int bytesToRealloc);

//
// ʹ��ָ����ֵ����ڴ���
//
extern void * TMemset(
	void * buffer,
	const int bytesToSet,
	const unsigned char valueToSet);

//---------------------------------------------------------------
// thread
// �߳���ؽӿ�
//---------------------------------------------------------------

//
// �̺߳���
//
typedef void(*TThreadProc)(
	T_OBJECT thread,
	void * userData);

//
// �����߳�
//
extern T_OBJECT TThreadCreateW(
	TThreadProc threadProc,
	void * userData,
	const int runNow,
	const wchar_t * threadName);

//
// �����߳�
//
extern void TThreadDestroy(
	T_OBJECT thread,
	const int waitTimeout);

//
// ǿ��ɱ���߳�
//
extern void TThreadKill(
	T_OBJECT thread);

//
// �����߳�
//
extern int TThreadSuspend(
	T_OBJECT thread);

//
// �ָ��߳�
//
extern int TThreadResume(
	T_OBJECT thread);

//
// �ȴ��߳�
//
extern int TThreadWait(
	T_OBJECT thread,
	const int waitTimeout);

//
// ��ȡ�߳��û�����
//
extern void * TThreadGetUserData(
	T_OBJECT thread);

//
// ��ȡ�̺߳���
//
extern TThreadProc TThreadGetThreadProc(
	T_OBJECT thread);

//
// ��ȡ�߳�����
//
extern const wchar_t * TThreadGetNameW(
	T_OBJECT thread);

//
// ��ȡ�߳� id
//
extern unsigned int TThreadGetId(
	T_OBJECT thread);

//
// �ǰ�߳�˯��ָ��ʱ��
//
extern void TThreadCurrentSleep(
	const int sleepTime);

//
// ��ȡ��ǰ�̶߳���
//
extern T_OBJECT TThreadGetCurrent(void);

//---------------------------------------------------------------
// mutex
// ��������ؽӿ�
//---------------------------------------------------------------

//
// ����������
//
extern T_OBJECT TMutexCreate(void);

//
// ���ٻ�����
//
extern void TMutexDestroy(
	T_OBJECT mutex);

//
// ����������
//
extern void TMutexLock(
	T_OBJECT mutex);

//
// ����������
//
extern void TMutexUnlock(
	T_OBJECT mutex);

//---------------------------------------------------------------
// event
// �¼���ؽӿ�
//---------------------------------------------------------------

//
// �����¼�
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
// ���¼�
//
extern T_OBJECT TEventOpenW(
	const wchar_t * eventName);
extern T_OBJECT TEventOpenA(
	const char * eventName);

//
// �����¼�
//
extern void TEventDestroy(
	T_OBJECT event);

//
// �ȴ��¼����뼤��״̬
//
extern int TEventWait(
	T_OBJECT event,
	const int waitTimeout);

//
// ���¼����뼤��״̬
//
extern int TEventSet(
	T_OBJECT event);

//
// ���¼��˳�����״̬
//
extern int TEventReset(
	T_OBJECT event);

//---------------------------------------------------------------
// window
// ������ؽӿ�
//---------------------------------------------------------------

//
// �����¼�ö����
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
// �����¼��ص�����
//
typedef void(*TWindowEventCallbackProc)(
	T_OBJECT window,
	const int eventType,
	const int mouseX,
	const int mouseY,
	const int key);

//
// ��������
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
// ���ٴ���
//
extern void TWindowDestroy(
	T_OBJECT window);

//
// ��ʾ�����ش���
//
extern int TWindowShow(
	T_OBJECT window,
	const int showOrHide);

//
// �������д�����Ϣ
//
extern int TWindowProcessMessage(void);

//
// �ȴ�������Ϣ
//
extern void TWindowWaitMessage(void);

//
// �ж�ָ�������Ƿ���Ч
//
extern int TWindowIsValid(
	T_OBJECT window);

//
// �����ڷ�������������
//
extern int TWindowPutDesktopCenter(
	T_OBJECT window);

//
// ���ô����¼��ص�����
//
extern void TWindowSetEventCallback(
	T_OBJECT window,
	TWindowEventCallbackProc eventProc);

//
// ��ȡ�����¼��ص�����
//
extern TWindowEventCallbackProc TWindowGetEventCallback(
	T_OBJECT window);

//---------------------------------------------------------------
// module
// ģ����ؽӿ�
//---------------------------------------------------------------

//
// ����ģ��
//
extern T_OBJECT TModuleLoadW(
	const wchar_t * moduleFileName);
extern T_OBJECT TModuleLoadA(
	const char * moduleFileName);

//
// ж��ģ��
//
extern void TModuleUnload(
	T_OBJECT module);

//
// ��ģ���е���������ַ
//
extern void * TModuleGetProcAddress(
	T_OBJECT module,
	const wchar_t * procName);

//
// �ж�ָ��ģ���Ƿ��Ѿ�����
//
extern int TModuleIsLoadedW(
	const wchar_t * moduleFileName);
extern int TModuleIsLoadedA(
	const char * moduleFileName);

//---------------------------------------------------------------
// resource
// ��Դ��ؽӿ�
//---------------------------------------------------------------

//
// ��Դ�ṹ��
//
typedef struct _T_RESOURCE
{
	// ��Դ���ݣ�ֻ����
	void * mData;
	// ��Դ��С
	int mSize;
}
T_RESOURCE;

//
// ������Դ
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
// ������Դ��ָ���ļ�
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
// ��������ؽӿ�
//---------------------------------------------------------------

//
// ��ȡ����
//
extern int TCmdLineReadParam(
	const int paramIndex,
	wchar_t * param,
	const int paramSize);

//
// �ж�ָ�������Ƿ����
//
extern int TCmdLineIsParamPresented(
	const wchar_t * param,
	int * paramIndex);

//---------------------------------------------------------------
// os info
// ����ϵͳ��Ϣ��ؽӿ�
//---------------------------------------------------------------

//
// ����ϵͳ�汾ö����
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
// ����ϵͳ����ö����
//
enum
{
	T_OSSETTING_FIRST,
	// �ͻ�����������
	T_OSSETTING_CLIENT_AREA_ANIMATION,
	// ���ڱ�Ե��Ӱ
	T_OSSETTING_DROP_SHADOW,
};

//
// ������ͣ������Ļ�е�λ��
//
enum
{
	//
	T_APPBAR_EDGE_FIRST,
	// ͣ������Ļ����
	T_APPBAR_EDGE_TOP,
	// ͣ������Ļ�ײ�
	T_APPBAR_EDGE_BOTTOM,
	// ͣ������Ļ���
	T_APPBAR_EDGE_LEFT,
	// ͣ������Ļ�Ҳ�
	T_APPBAR_EDGE_RIGHT,
};

//
// ��ѯ����ϵͳ�汾
//
extern int TOSInfoQueryVersion(
	int * osVer);

//
// ������ϵͳ�汾��ת��Ϊ�����Ķ����ַ���
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
// ��ȡ����ϵͳ�Ƿ� x64
//
extern int TOSInfoIsOSx64(
	int * isX64);

//
// ������رղ���ϵͳ�е�ָ������
//
extern int TOSInfoSettingTurn(
	const int settingType,
	const int onOrOff);

//
// ��ȡ��ǰ��¼�û�����
//
extern int TOSInfoGetUserNameW(
	wchar_t * userName,
	const int userNameSize);
extern int TOSInfoGetUserNameA(
	char * userName,
	const int userNameSize);

//
// ��ȡ����������Ļ�е�ͣ��λ��
//
extern int TOSInfoGetAppBarEdge(
	int * appBarEdge);

//
// ��ȡ����������Ļ�еľ�������
//
extern int TOSInfoGetAppBarRect(
	int * appBarLeft,
	int * appBarTop,
	int * appBarWidth,
	int * appBarHeight);

//
// ��ȡ�����С
//
extern int TOSInfoGetDesktopSize(
	int * desktopWidth,
	int * desktopHeight);

//---------------------------------------------------------------
// hardware
// Ӳ����ؽӿ�
//---------------------------------------------------------------

//
// �ڴ�״̬�ṹ��
//
typedef struct _T_MEMORY_STATE
{
	// �������ڴ�
	unsigned long long int mTotalPhys;
	// ���������ڴ�
	unsigned long long int mAvailPhys;
	// �������ڴ�
	unsigned long long int mTotalVirtual;
	// ���������ڴ�
	unsigned long long int mAvailVirtual;
}
T_MEMORY_STATE;

//
// ��ȡ�ڴ�״̬
//
extern int TMemoryQueryState(
	T_MEMORY_STATE * memoryState);

//---------------------------------------------------------------
// process
// ������ؽӿ�
//---------------------------------------------------------------

//
// ���̻ص�����
//
typedef int(*TProcessCallbackProc)(
	const unsigned int processId,
	void * userData);

//
// ��ȡ��ǰ�����Ƿ� x64 ����
//
extern int TProcessIsX64(void);

//
// ö�����н���
//
extern int TProcessEnum(
	TProcessCallbackProc enumProc,
	void * userData);

//
// ͨ������ id����ѯ���� exe �ļ�·��
//
extern int TProcessQueryImageNameByProcessIdW(
	const unsigned int processId,
	wchar_t * imageName,
	const int imageNameSize);

//
// ��ָֹ������
//
extern int TProcessTerminate(
	const unsigned int processId);

//---------------------------------------------------------------
// share memory
// �����ڴ���ؽӿ�
//---------------------------------------------------------------

//
// �򿪹����ڴ棬�������ڣ��򴴽�
//
extern T_OBJECT TShareMemoryOpenW(
	const wchar_t * name,
	const int sizeForCreate);
extern T_OBJECT TShareMemoryOpenA(
	const char * name,
	const int sizeForCreate);

//
// �رչ����ڴ�
//
extern void TShareMemoryClose(
	T_OBJECT shareMemory);

//
// ������д�빲���ڴ�
//
extern int TShareMemoryWrite(
	T_OBJECT shareMemory,
	const void * data,
	const int offset,
	const int bytesToWrite);

//
// �ӹ����ڴ��ж�ȡ����
//
extern int TShareMemoryRead(
	T_OBJECT shareMemory,
	void * data,
	const int offset,
	const int bytesToRead);

//---------------------------------------------------------------
// directory
// Ŀ¼��ؽӿ�
//---------------------------------------------------------------

//
// ��ȡӦ�ó�������Ŀ¼
//
extern int TDirectoryGetAppW(
	wchar_t * appDir,
	const int appDirSize);
extern int TDirectoryGetAppA(
	char * appDir,
	const int appDirSize);

//---------------------------------------------------------------
// d3d9 paint device
// d3d9 ��ͼ�豸��ؽӿ�
//---------------------------------------------------------------

//
// ���� d3d9 ��ͼ�豸
//
extern T_OBJECT TD3D9PaintDeviceCreate(
	T_OBJECT window,
	const int bufferWidth,
	const int bufferHeight,
	const int fullscreen,
	const int vsync);

//
// ���� d3d9 ��ͼ�豸
//
extern void TD3D9PaintDeviceDestroy(
	T_OBJECT d3d9PaintDevice);

//
// ��� d3d9 ��ͼ�豸
//
extern int TD3D9PaintDeviceClear(
	T_OBJECT d3d9PaintDevice,
	const unsigned int clearColor);

//
// ���� d3d9 ��ͼ�豸
//
extern int TD3D9PaintDevicePresent(
	T_OBJECT d3d9PaintDevice);

//---------------------------------------------------------------
// d3d9 font
// d3d9 ������ؽӿ�
//---------------------------------------------------------------

//
// ���� d3d9 ����
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
// ���� d3d9 ����
//
extern void TD3D9FontDestroy(
	T_OBJECT d3d9Font);

//
// �����ַ���
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
// �����ַ�����С
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
// d3d9 graph ��ؽӿ�
//---------------------------------------------------------------

//
// ��ͼ���ļ����� d3d9 graph
//
extern T_OBJECT TD3D9GraphCreateFromImageFileW(
	T_OBJECT d3d9PaintDevice,
	const wchar_t * imageFileName,
	const unsigned int colorKey);

//
// ���� d3d9 graph ����
//
extern void TD3D9GraphDestroy(
	T_OBJECT d3d9Graph);

//
// ���� d3d9 graph ����ָ��λ��
//
extern void TD3D9GraphPaintV1(
	T_OBJECT d3d9Graph,
	const float graphX,
	const float graphY);

//---------------------------------------------------------------
// ds8 sound device
// ds8 ��Ƶ�豸��ؽӿ�
//---------------------------------------------------------------

//
// ���� ds8 ��Ƶ�豸
//
extern T_OBJECT TDS8SoundDeviceCreate(
	T_OBJECT window);

//
// ���� ds8 ��Ƶ�豸
//
extern void TDS8SoundDeviceDestroy(
	T_OBJECT ds8SoundDevice);

//---------------------------------------------------------------
// ds8 sound buffer
// ds8 ��Ƶ������ؽӿ�
//---------------------------------------------------------------

//
// ���� ds8 ��Ƶ����
//
extern T_OBJECT TDS8SoundBufferCreate(
	T_OBJECT ds8SoundDevice,
	const unsigned int bufferSize,
	const unsigned short channels,
	const unsigned short bitsPerSample,
	const unsigned int sampleRate);

//
// ͨ�� wave �ļ������� ds8 ��Ƶ����
//
extern T_OBJECT TDS8SoundBufferCreateFromWaveFileW(
	T_OBJECT ds8SoundDevice,
	const wchar_t * waveFileName);

//
// ���� ds8 ��Ƶ������
//
extern void TDS8SoundBufferDestroy(
	T_OBJECT ds8SoundBuffer);

//
// ���� ds8 ��Ƶ������
//
extern int TDS8SoundBufferPlay(
	T_OBJECT ds8SoundBuffer,
	const int loop);

//
// ֹͣ ds8 ��Ƶ������
//
extern int TDS8SoundBufferStop(
	T_OBJECT ds8SoundBuffer);

//
// ���� ds8 ��Ƶ����������
//
extern int TDS8SoundBufferSetVolume(
	T_OBJECT ds8SoundBuffer,
	const float volume);

//
// ��ȡ ds8 ��Ƶ����������
//
extern int TDS8SoundBufferGetVolume(
	T_OBJECT ds8SoundBuffer,
	float * volume);

//
// ���� ds8 ��Ƶ����������
//
extern void * TDS8SoundBufferLock(
	T_OBJECT ds8SoundBuffer,
	const int offsetToLock,
	const int bytesToLock);

//
// ���� ds8 ��Ƶ����������
//
extern int TDS8SoundBufferUnlock(
	T_OBJECT ds8SoundBuffer);

//---------------------------------------------------------------
// ini file
// ini �����ļ���ؽӿ�
//---------------------------------------------------------------

//
// ���� ini �����ļ�
//
extern T_OBJECT TIniFileCreateW(
	const wchar_t * iniFileName);

//
// ���� ini �����ļ�
//
extern void TIniFileDestroy(
	T_OBJECT iniFile);

//
// �� ini �����ļ���ȡ�ַ���
//
extern int TIniFileReadStringW(
	T_OBJECT iniFile,
	const wchar_t * sectionName,
	const wchar_t * keyName,
	wchar_t * value,
	const int valueSize);

//
// �� ini �����ļ���ȡ����
//
extern int TIniFileReadIntW(
	T_OBJECT iniFile,
	const wchar_t * sectionName,
	const wchar_t * keyName,
	int * value);

//---------------------------------------------------------------
// page
// ��ҳ��ؽӿ�
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
// ��־��ؽӿ�
//---------------------------------------------------------------

//
// ������־
//
extern int TLogStartupW(
	const wchar_t * logFileName,
	const int toDebugView);
extern int TLogStartupA(
	const char * logFileName,
	const int toDebugView);

//
// �ر���־
//
extern void TLogShutdown(void);

//
// д���ʽ����־��Ϣ
//
extern int TLogWriteFormatMessageW(
	const wchar_t * format,
	...);
extern int TLogWriteFormatMessageA(
	const char * format,
	...);

//
// д����־��Ϣ
//
extern int TLogWriteMesageW(
	const wchar_t * message);
extern int TLogWriteMesageA(
	const char * message);

//---------------------------------------------------------------
// net
// ������ؽӿ�
//---------------------------------------------------------------

//
// ���������豸
//
extern int TNetDeviceStartup(void);

//
// �ر������豸
//
extern void TNetDeviceShutdown(void);

//
// ����һ���ͻ��� sock
//
extern T_OBJECT TNetSockCreateClient(void);

//
// ����һ������� sock
//
extern T_OBJECT TNetSockCreateServer(
	const char * ipV4,
	const short int port);

//
// ���� sock
//
extern void TNetSockDestroy(
	T_OBJECT sock);

//
// ��ͻ��� sock ���ӵ������ sock
//
extern int TNetSockConnect(
	T_OBJECT sock,
	const char * ipV4,
	const short int port);

//
// ������ sock �ȴ��ͻ��� sock ������
//
extern T_OBJECT TNetSockAcceptConnect(
	T_OBJECT sock);

//
// �������ݵ�ָ�� sock
//
extern int TNetSockSendData(
	T_OBJECT sock,
	const void * data,
	const int bytesToSend,
	int * bytesSended);

//
// ����ָ����С�����ݵ�ָ�� sock��ֱ���������ݷ�����ϣ������
//
extern int TNetSockSendDataV2(
	T_OBJECT sock,
	const void * data,
	const int bytesToSend);

//
// ��ָ�� sock ��ȡ����
//
extern int TNetSockRecvData(
	T_OBJECT sock,
	void * data,
	const int bytesToRecv,
	int * bytesRecved);

//
// ��ָ�� sock ��ȡָ����С�����ݣ�ֱ���������ݶ�ȡ��ϣ������
//
extern int TNetSockRecvDataV2(
	T_OBJECT sock,
	void * data,
	const int bytesToRecv);

//---------------------------------------------------------------
// path
// �ļ�·����ؽӿ�
//---------------------------------------------------------------

//
// ��·���г�ȡ��������չ�����ļ���
//
// path Ҫ��ȡ�ļ������ļ�·��
// fileNameWithExt ���ڱ����ȡ�������ļ���
// fileNameWithExtSize fileNameWithExt ����������
//
// �������ʾ�ɹ������ؼٱ�ʾʧ��
//
extern int TPathExtractFileNameWithExtW(
	const wchar_t * path,
	wchar_t * fileNameWithExt,
	const int fileNameWithExtSize);

#endif // TURBOLIB_H
