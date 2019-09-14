
#pragma once

#include "../SurgeGameEngine.h"

#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <Windows.h>
#include <MMSystem.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <wchar.h>

#include "../DependLib/D3D9/d3d9.h"
#include "../DependLib/D3D9/d3dx9.h"
#include "../DependLib/DS8/dsound.h"

enum sgePrimitiveType
{
	sgePrimitiveTypeUnknown,
	sgePrimitiveTypePoint,
	sgePrimitiveTypeLine,
	sgePrimitiveTypeTriangle,
};

struct sgeSpriteVertex
{
	float x, y, z, rhw;
	unsigned int diffuse;
	float u, v;
};

struct sgePrimitiveVertex
{
	float x, y, z, rhw;
	unsigned int diffuse;
};

class sgeVertexBuffer : public sgeNonCopyable
{
public:
	sgeVertexBuffer();
	virtual ~sgeVertexBuffer();
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

class sgeBatchSprite : public sgeNonCopyable
{
public:
	sgeBatchSprite();
	virtual ~sgeBatchSprite();
public:
	bool create(void);
	void destroy(void);
	bool flush(void);
	bool paintSprite(IDirect3DTexture9 * d3dTex9, sgeSpriteVertex * vertexList);
private:
	void lockVertexBuffer(void);
	void unlockVertexBuffer(void);
private:
	sgeVertexBuffer mVertexBuffer;
	sgeSpriteVertex * mVertexList;
	IDirect3DTexture9 * mD3DTex9;
	int mSpriteCount;
};

class sgeBatchPrimitive : public sgeNonCopyable
{
public:
	sgeBatchPrimitive();
	virtual ~sgeBatchPrimitive();
public:
	bool create(void);
	void destroy(void);
	bool flush(void);
	bool paintPoint(
		const sgePoint<float> & pos,
		const unsigned int color);
	bool paintLine(
		const sgePoint<float> & posStart,
		const sgePoint<float> & posEnd,
		const unsigned int color);
	bool paintTriangle(
		const sgePoint<float> & pt1,
		const sgePoint<float> & pt2,
		const sgePoint<float> & pt3,
		const unsigned int color,
		const bool solid);
	bool paintRectangle(
		const sgePoint<float> & pos,
		const sgeSize<float> & size,
		const unsigned int color,
		const bool solid);
private:
	void lockVertexBuffer(void);
	void unlockVertexBuffer(void);
private:
	sgeVertexBuffer mVertexBuffer;
	sgePrimitiveVertex * mVertexList;
	int mPrimitiveCount;
	sgePrimitiveType mPrimitiveType;
};

class sgeWindow : public sgeNonCopyable
{
public:
	sgeWindow();
	virtual ~sgeWindow();
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

class sgeVideoDevice : public sgeNonCopyable
{
public:
	sgeVideoDevice();
	virtual ~sgeVideoDevice();
public:
	bool create(
		sgeWindow & window,
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

class sgeSoundDevice : public sgeNonCopyable
{
public:
	sgeSoundDevice();
	virtual ~sgeSoundDevice();
public:
	bool create(sgeWindow & window);
	void destroy(void);
	bool isAlready(void) const;
	IDirectSound8 * getIDirectSound8(void) const;
	long engineVolumeToDS8Volume(const float volume) const;
	float ds8VolumeToEngineVolume(const long volume) const;
private:
	IDirectSound8 * mDS8;
	IDirectSoundBuffer * mDSBuf;
};

class sgeWaveReader : public sgeNonCopyable
{
public:
	sgeWaveReader();
	virtual ~sgeWaveReader();
public:
	bool createFromFileW(const wchar_t * fileName);
	void destroy(void);
	unsigned short getChannels(void) const;
	unsigned short getBitsPerSample(void) const;
	unsigned int getSampleRate(void) const;
	unsigned int getPCMDataSize(void) const;
	bool readAllPCMData(void * buffer);
private:
	sgeFile mWaveFile;
	unsigned short mChannels;
	unsigned short mBitsPerSample;
	unsigned int mSampleRate;
	long long int mPCMDataOffset;
	unsigned int mPCMDataSize;
};

class sgePerformanceCounter
{
public:
	sgePerformanceCounter();
	virtual ~sgePerformanceCounter();
public:
	void tick(void);
	float getElapseF32(void) const;
private:
	long long int mFrequency;
	long long int mTimeLastTick;
	long long int mElapse;
};

extern sgeWindow gWindow;
extern sgeVideoDevice gVideoDevice;
extern sgeSoundDevice gSoundDevice;
extern sgeBatchSprite gBatchSprite;
extern sgeBatchPrimitive gBatchPrimitive;
extern sgeModule gModuleD3D9;
extern sgeModule gModuleD3DX9;
extern sgeModule gModuleDSound;
extern sgeModule gModuleUser32;
extern sgeModule gModuleKernel32;
extern sgeModule gModuleGDI32;
