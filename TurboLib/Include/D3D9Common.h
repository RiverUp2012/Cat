
#ifndef D3D9COMMON_H
#define D3D9COMMON_H

#include "CompileConfig.h"
#include "Private.h"

#if defined T_USE_D3D9

#	include "../DependLib/D3D9/d3d9.h"
#	include "../DependLib/D3D9/d3dx9.h"

//---------------------------------------------------------------
// d3d9 graph vertex
// ���� graph ����� d3d9 ����
//---------------------------------------------------------------

typedef struct _T_D3D9VERTEXGRAPH
{
	float x, y, z, rhw;
	unsigned int diffuse;
	float u, v;
}
T_D3D9VERTEXGRAPH;

#define T_D3D9VERTEXGRAPH_STRIDE (sizeof(T_D3D9VERTEXGRAPH))
#define T_D3D9VERTEXGRAPH_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//---------------------------------------------------------------
// d3d9 common
// d3d9 �����ӿ�
//---------------------------------------------------------------

//
// ��ȡ d3dx9_xxx.dll ģ��
//
extern T_OBJECT TGetD3DX9Module(void);

//---------------------------------------------------------------
// d3d9 paint device
// d3d9 ��ͼ�豸��ؽӿ�
//---------------------------------------------------------------

//
// ��ȡ IDirect3DDevice9 �ӿ�
//
extern struct IDirect3DDevice9 * TD3D9PaintDeviceGetIDirect3DDevice9(
	T_OBJECT d3d9PaintDevice);

//
// ���� d3d9 graph
//
extern void TD3D9PaintDevicePaintGraph(
	T_OBJECT d3d9PaintDevice,
	T_D3D9VERTEXGRAPH * vertexList,
	T_OBJECT d3d9Texture);

extern void TD3D9PaintDeviceFlushBatchGraph(
	T_OBJECT d3d9PaintDevice);

//---------------------------------------------------------------
// d3d9 vertex buffer
// d3d9 ���㻺����ؽӿ�
//---------------------------------------------------------------

//
// ���� d3d9 ���㻺��
//
extern T_OBJECT TD3D9VertexBufferCreate(
	T_OBJECT d3d9PaintDevice,
	const int size,
	const int fvf);

//
// ���� d3d9 ���㻺��
//
extern void TD3D9VertexBufferDestroy(
	T_OBJECT d3d9VertexBuffer);

//
// ���� d3d9 ���㻺��
//
extern void * TD3D9VertexBufferLock(
	T_OBJECT d3d9VertexBuffer,
	const int offsetToLock,
	const int bytesToLock);

//
// ���� d3d9 ���㻺��
//
extern int TD3D9VertexBufferUnlock(
	T_OBJECT d3d9VertexBuffer);

//
// ��ȡ IDirect3DVertexBuffer9 �ӿ�
//
extern struct IDirect3DVertexBuffer9 * TD3D9VertexBufferGetIDirect3DVertexBuffer9(
	T_OBJECT d3d9VertexBuffer);

//---------------------------------------------------------------
// d3d9 texture
// d3d9 ������ؽӿ�
//---------------------------------------------------------------

//
// ��ͼ���ļ����� d3d9 ����
//
extern T_OBJECT TD3D9TextureCreateFromFileW(
	T_OBJECT d3d9PaintDevice,
	const wchar_t * imageFileName,
	const unsigned int colorKey);

//
// ���� d3d9 ����
//
extern void TD3D9TextureDestroy(
	T_OBJECT d3d9Texture);

//
// ��ȡ IDirect3DTexture9 �ӿ�
//
extern struct IDirect3DTexture9 * TD3D9TextureGetIDirect3DTexture9(
	T_OBJECT d3d9Texture);

//
// ���� d3d9 �������ü���ֵ
//
extern void TD3D9TextureAddRef(
	T_OBJECT d3d9Texture);

//
// ��ȡ d3d9 ����ͼ���С
//
extern void TD3D9TextureGetImageSize(
	T_OBJECT d3d9Texture,
	float * imageWidth,
	float * imageHeight);

//
// ��ȡ d3d9 ����ҳ���С
//
extern void TD3D9TextureGetSurfaceSize(
	T_OBJECT d3d9Texture,
	float * surfaceWidth,
	float * surfaceHeight);

//---------------------------------------------------------------
// d3d9 batch graph
// d3d9 ���� graph ��Ⱦ��ؽӿ�
//---------------------------------------------------------------

extern T_OBJECT TD3D9BatchGraphCreate(
	T_OBJECT d3d9PaintDevice);

extern void TD3D9BatchGraphDestroy(
	T_OBJECT d3d9BatchGraph);

extern void TD3D9BatchGraphFlush(
	T_OBJECT d3d9BatchGraph,
	T_OBJECT d3d9PaintDevice);

extern void TD3D9BatchGraphPaintGraph(
	T_OBJECT d3d9BatchGraph,
	T_OBJECT d3d9PaintDevice,
	T_D3D9VERTEXGRAPH * vertexList,
	T_OBJECT d3d9Texture);

#endif // T_USE_D3D9

#endif // D3D9COMMON_H
