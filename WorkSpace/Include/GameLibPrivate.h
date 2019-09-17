
#pragma once

//#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <Windows.h>
//#include <WinSock2.h>
#include <MMSystem.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <wchar.h>
#include "../DependLib/D3D9/d3d9.h"
#include "../DependLib/D3D9/d3dx9.h"
#include "../DependLib/DS8/dsound.h"
#include "../GameLib.h"

enum glPrimitiveType {
	glPrimitiveTypeUnknown,
	glPrimitiveTypePoint,
	glPrimitiveTypeLine,
	glPrimitiveTypeTriangle,
};

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
// @brief 顶点缓冲区类
//
class glVertexBuffer : public glNonCopyable {
public:
	glVertexBuffer();
	virtual ~glVertexBuffer();
public:
	bool create(const int size, const int fvf);
	void destroy(void);
	bool isAlready(void) const;
	void * lock(const int offset = 0, const int size = 0);
	bool unlock(void);
	IDirect3DVertexBuffer9 * getIDirect3DVertexBuffer9(void) const;
private:
	IDirect3DVertexBuffer9 * mD3DVB9;
};

//
// @brief 批量精灵渲染类
//
class glBatchSprite : public glNonCopyable {
public:
	glBatchSprite();
	virtual ~glBatchSprite();
public:
	bool create(void);
	void destroy(void);
	bool flush(void);
	bool paintSprite(IDirect3DTexture9 * d3dTex9, glSpriteVertex * vertexList);
private:
	void lockVertexBuffer(void);
	void unlockVertexBuffer(void);
private:
	glVertexBuffer mVertexBuffer;
	glSpriteVertex * mVertexList;
	IDirect3DTexture9 * mD3DTex9;
	int mSpriteCount;
};

//
// @brief 批量图元渲染类
//
class glBatchPrimitive : public glNonCopyable {
public:
	glBatchPrimitive();
	virtual ~glBatchPrimitive();
public:
	bool create(void);
	void destroy(void);
	bool flush(void);
	bool paintPoint(
		const glPoint<float> & pos,
		const unsigned int color);
	bool paintLine(
		const glPoint<float> & posStart,
		const glPoint<float> & posEnd,
		const unsigned int color);
	bool paintTriangle(
		const glPoint<float> & pt1,
		const glPoint<float> & pt2,
		const glPoint<float> & pt3,
		const unsigned int color,
		const bool solid);
	bool paintRectangle(
		const glPoint<float> & pos,
		const glSize<float> & size,
		const unsigned int color,
		const bool solid);
private:
	void lockVertexBuffer(void);
	void unlockVertexBuffer(void);
private:
	glVertexBuffer mVertexBuffer;
	glPrimitiveVertex * mVertexList;
	int mPrimitiveCount;
	glPrimitiveType mPrimitiveType;
};

//
// @brief 窗口类
//
class glWindow : public glNonCopyable {
public:
	glWindow();
	virtual ~glWindow();
public:
	bool createW(
		const wchar_t * windowTitle,
		const int screenWidth,
		const int screenHeight);
	void destroy(void);
	bool isAlready(void) const;
	void * getHandle(void) const;
private:
	void * mWindowHandle;
};

//
// @brief 视频设备类
//
class glVideoDevice : public glNonCopyable {
public:
	glVideoDevice();
	virtual ~glVideoDevice();
public:
	bool create(
		glWindow & window,
		const int screenWidth,
		const int screenHeight);
	void destroy(void);
	bool isAlready(void) const;
	IDirect3DDevice9 * getIDirect3DDevice9(void) const;
	bool clear(const unsigned int clearColor);
	bool present(void);
private:
	void setupDefaultRenderStatus(void);
private:
	IDirect3DDevice9 * mD3DDev9;
};

//
// @brief 声音设备类
//
class glSoundDevice : public glNonCopyable {
public:
	glSoundDevice();
	virtual ~glSoundDevice();
public:
	bool create(glWindow & window);
	void destroy(void);
	bool isAlready(void) const;
	IDirectSound8 * getIDirectSound8(void) const;
	long engineVolumeToDS8Volume(const float volume) const;
	float ds8VolumeToEngineVolume(const long volume) const;
private:
	IDirectSound8 * mDS8;
	IDirectSoundBuffer * mDSBuf;
};

//
// @brief wave 读取类
//
class glWaveReader : public glNonCopyable {
public:
	glWaveReader();
	virtual ~glWaveReader();
public:
	bool createFromFileW(const wchar_t * fileName);
	void destroy(void);
	unsigned short getChannels(void) const;
	unsigned short getBitsPerSample(void) const;
	unsigned int getSampleRate(void) const;
	unsigned int getPCMDataSize(void) const;
	bool readAllPCMData(void * buffer);
private:
	glFile mWaveFile;
	unsigned short mChannels;
	unsigned short mBitsPerSample;
	unsigned int mSampleRate;
	long long int mPCMDataOffset;
	unsigned int mPCMDataSize;
};

//
// @brief 性能计数器类
//
class glPerformanceCounter {
public:
	glPerformanceCounter();
	virtual ~glPerformanceCounter();
public:
	void tick(void);
	float getElapseF32(void) const;
private:
	long long int mFrequency;
	long long int mTimeLastTick;
	long long int mElapse;
};

//
// @brief 网络设备类
//
class glNetDevice {
public:
	static bool create(void);
	static void destroy(void);
};

//
// @brief 可等待定时器类
//
class glWaitableTimer : public glNonCopyable {
public:
	glWaitableTimer();
	virtual ~glWaitableTimer();
public:
	bool create(void);
	void destroy(void);
	bool isAlready(void) const;
	bool wait(const int timeOut);
private:
	void * mTimerHandle;
};

extern glWindow gWindow;
extern glVideoDevice gVideoDevice;
extern glSoundDevice gSoundDevice;
extern glBatchSprite gBatchSprite;
extern glBatchPrimitive gBatchPrimitive;
extern glModule gModuleD3D9;
extern glModule gModuleD3DX9;
extern glModule gModuleDSound;
extern glModule gModuleUser32;
extern glModule gModuleKernel32;
extern glModule gModuleGDI32;
extern glModule gModulePsapi;
