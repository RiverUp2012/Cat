
#include "../Include/Private.h"
#include "../Include/D3D9Common.h"
#include "../Include/CompileConfig.h"

#if defined T_USE_D3D9

#define T_MAX_D3D9VERTEXBUFFER (32)

typedef struct _T_D3D9VERTEXBUFFER
{
	struct IDirect3DVertexBuffer9 * mD3DVB9;
}
T_D3D9VERTEXBUFFER;

static T_D3D9VERTEXBUFFER gD3D9VertexBufferArray[T_MAX_D3D9VERTEXBUFFER] = { 0 };

static T_D3D9VERTEXBUFFER * TFindUnuseD3D9VertexBuffer(void)
{
	for (int i = 0; i < T_MAX_D3D9VERTEXBUFFER; ++i)
	{
		if (!gD3D9VertexBufferArray[i].mD3DVB9)
		{
			return &gD3D9VertexBufferArray[i];
		}
	}

	return 0;
}

T_OBJECT TD3D9VertexBufferCreate(
	T_OBJECT d3d9PaintDevice,
	const int size,
	const int fvf)
{
	struct IDirect3DDevice9 * d3dDev9 = TD3D9PaintDeviceGetIDirect3DDevice9(d3d9PaintDevice);
	T_D3D9VERTEXBUFFER * d3d9VertexBufferImpl = TFindUnuseD3D9VertexBuffer();

	if (d3dDev9 && d3d9VertexBufferImpl && size > 0 && fvf > 0)
	{
		if (SUCCEEDED(d3dDev9->CreateVertexBuffer(
			size,
			0,
			fvf,
			D3DPOOL_DEFAULT,
			&d3d9VertexBufferImpl->mD3DVB9,
			0)))
		{
			return (T_OBJECT)d3d9VertexBufferImpl;
		}
	}

	return 0;
}

void TD3D9VertexBufferDestroy(
	T_OBJECT d3d9VertexBuffer)
{
	T_D3D9VERTEXBUFFER * d3d9VertexBufferImpl = (T_D3D9VERTEXBUFFER *)d3d9VertexBuffer;
	if (d3d9VertexBufferImpl)
	{
		if (d3d9VertexBufferImpl->mD3DVB9)
		{
			d3d9VertexBufferImpl->mD3DVB9->Release();
			d3d9VertexBufferImpl->mD3DVB9 = 0;
		}
	}
}

void * TD3D9VertexBufferLock(
	T_OBJECT d3d9VertexBuffer,
	const int offsetToLock,
	const int bytesToLock)
{
	void * buffer = 0;

	T_D3D9VERTEXBUFFER * d3d9VertexBufferImpl = (T_D3D9VERTEXBUFFER *)d3d9VertexBuffer;
	if (d3d9VertexBufferImpl && d3d9VertexBufferImpl->mD3DVB9)
	{
		if (SUCCEEDED(d3d9VertexBufferImpl->mD3DVB9->Lock(
			offsetToLock,
			bytesToLock,
			&buffer,
			0)))
		{
			return buffer;
		}
	}

	return 0;
}

int TD3D9VertexBufferUnlock(
	T_OBJECT d3d9VertexBuffer)
{
	T_D3D9VERTEXBUFFER * d3d9VertexBufferImpl = (T_D3D9VERTEXBUFFER *)d3d9VertexBuffer;
	if (d3d9VertexBufferImpl && d3d9VertexBufferImpl->mD3DVB9)
	{
		if (SUCCEEDED(d3d9VertexBufferImpl->mD3DVB9->Unlock()))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

struct IDirect3DVertexBuffer9 * TD3D9VertexBufferGetIDirect3DVertexBuffer9(
	T_OBJECT d3d9VertexBuffer)
{
	T_D3D9VERTEXBUFFER * d3d9VertexBufferImpl = (T_D3D9VERTEXBUFFER *)d3d9VertexBuffer;

	return d3d9VertexBufferImpl ? d3d9VertexBufferImpl->mD3DVB9 : 0;
}

#endif
