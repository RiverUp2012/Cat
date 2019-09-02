
#include "../Include/Private.h"
#include "../Include/D3D9Common.h"
#include "../Include/CompileConfig.h"

#if defined T_USE_D3D9

#define T_MAX_D3D9BATCHGRAPH (32)
#define T_MAX_D3D9BATCHGRAPH_VERTEX (1024 * 8)

typedef struct _T_D3D9BATCHGRAPH
{
	T_OBJECT mVertexBuffer;
	T_D3D9VERTEXGRAPH * mVertexList;
	T_OBJECT mTexture;
	int mGraphCount;
}
T_D3D9BATCHGRAPH;

static T_D3D9BATCHGRAPH gD3D9BatchGraphArray[T_MAX_D3D9BATCHGRAPH] = { 0 };

static T_D3D9BATCHGRAPH * TFindUnuseD3D9BatchGraph(void)
{
	for (int i = 0; i < T_MAX_D3D9BATCHGRAPH; ++i)
	{
		if (!gD3D9BatchGraphArray[i].mVertexBuffer)
		{
			return &gD3D9BatchGraphArray[i];
		}
	}

	return 0;
}

static void TD3D9BatchGraphLockVertexBuffer(
	T_OBJECT d3d9BatchGraph)
{
	T_D3D9BATCHGRAPH * d3d9BatchGraphImpl = (T_D3D9BATCHGRAPH *)d3d9BatchGraph;
	if (d3d9BatchGraphImpl &&
		d3d9BatchGraphImpl->mVertexBuffer &&
		!d3d9BatchGraphImpl->mVertexList)
	{
		d3d9BatchGraphImpl->mVertexList = (T_D3D9VERTEXGRAPH *)TD3D9VertexBufferLock(
			d3d9BatchGraphImpl->mVertexBuffer,
			0,
			0);
	}
}

static void TD3D9BatchGraphUnlockVertexBuffer(
	T_OBJECT d3d9BatchGraph)
{
	T_D3D9BATCHGRAPH * d3d9BatchGraphImpl = (T_D3D9BATCHGRAPH *)d3d9BatchGraph;
	if (d3d9BatchGraphImpl &&
		d3d9BatchGraphImpl->mVertexBuffer &&
		d3d9BatchGraphImpl->mVertexList)
	{
		if (TD3D9VertexBufferUnlock(d3d9BatchGraphImpl->mVertexBuffer))
		{
			d3d9BatchGraphImpl->mVertexList = 0;
		}
	}
}

T_OBJECT TD3D9BatchGraphCreate(
	T_OBJECT d3d9PaintDevice)
{
	T_D3D9BATCHGRAPH * d3d9BatchGraphImpl = TFindUnuseD3D9BatchGraph();
	if (d3d9BatchGraphImpl)
	{
		d3d9BatchGraphImpl->mVertexBuffer = TD3D9VertexBufferCreate(
			d3d9PaintDevice,
			T_MAX_D3D9BATCHGRAPH_VERTEX * T_D3D9VERTEXGRAPH_STRIDE,
			T_D3D9VERTEXGRAPH_FVF);
		if (d3d9BatchGraphImpl->mVertexBuffer)
		{
			TD3D9BatchGraphLockVertexBuffer(d3d9BatchGraphImpl);;

			return (T_OBJECT)d3d9BatchGraphImpl;
		}
	}

	return 0;
}

void TD3D9BatchGraphDestroy(
	T_OBJECT d3d9BatchGraph)
{
	T_D3D9BATCHGRAPH * d3d9BatchGraphImpl = (T_D3D9BATCHGRAPH *)d3d9BatchGraph;
	if (d3d9BatchGraphImpl)
	{
		if (d3d9BatchGraphImpl->mVertexBuffer)
		{
			TD3D9VertexBufferDestroy(d3d9BatchGraphImpl->mVertexBuffer);
			d3d9BatchGraphImpl->mVertexBuffer = 0;
		}

		if (d3d9BatchGraphImpl->mTexture)
		{
			TD3D9TextureDestroy(d3d9BatchGraphImpl->mTexture);
			d3d9BatchGraphImpl->mTexture = 0;
		}

		d3d9BatchGraphImpl->mGraphCount = 0;
		d3d9BatchGraphImpl->mVertexList = 0;
	}
}

void TD3D9BatchGraphFlush(
	T_OBJECT d3d9BatchGraph,
	T_OBJECT d3d9PaintDevice)
{
	struct IDirect3DDevice9 * d3dDev9 = TD3D9PaintDeviceGetIDirect3DDevice9(d3d9PaintDevice);
	T_D3D9BATCHGRAPH * d3d9BatchGraphImpl = (T_D3D9BATCHGRAPH *)d3d9BatchGraph;
	if (d3dDev9 &&
		d3d9BatchGraphImpl &&
		d3d9BatchGraphImpl->mVertexBuffer &&
		d3d9BatchGraphImpl->mTexture &&
		d3d9BatchGraphImpl->mGraphCount > 0)
	{
		d3dDev9->SetTexture(
			0,
			(struct IDirect3DBaseTexture9 *)TD3D9TextureGetIDirect3DTexture9(d3d9BatchGraphImpl->mTexture));
		d3dDev9->SetStreamSource(
			0,
			TD3D9VertexBufferGetIDirect3DVertexBuffer9(d3d9BatchGraphImpl->mVertexBuffer),
			0,
			T_D3D9VERTEXGRAPH_STRIDE);
		d3dDev9->SetFVF(
			T_D3D9VERTEXGRAPH_FVF);
		d3dDev9->DrawPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			d3d9BatchGraphImpl->mGraphCount * 2);

		d3d9BatchGraphImpl->mGraphCount = 0;
	}
}

void TD3D9BatchGraphPaintGraph(
	T_OBJECT d3d9BatchGraph,
	T_OBJECT d3d9PaintDevice,
	T_D3D9VERTEXGRAPH * vertexList,
	T_OBJECT d3d9Texture)
{
	T_D3D9BATCHGRAPH * d3d9BatchGraphImpl = (T_D3D9BATCHGRAPH *)d3d9BatchGraph;
	if (d3d9BatchGraphImpl && vertexList && d3d9Texture)
	{
		if (d3d9BatchGraphImpl->mGraphCount * 6 >= T_MAX_D3D9BATCHGRAPH_VERTEX)
		{
			TD3D9BatchGraphFlush(d3d9BatchGraph, d3d9PaintDevice);

			d3d9BatchGraphImpl->mGraphCount = 0;
		}

		if (d3d9BatchGraphImpl->mTexture != d3d9Texture)
		{
			TD3D9BatchGraphFlush(d3d9BatchGraph, d3d9PaintDevice);

			if (d3d9BatchGraphImpl->mTexture)
			{
				TD3D9TextureDestroy(d3d9BatchGraphImpl->mTexture);
				d3d9BatchGraphImpl->mTexture = 0;
			}
			d3d9BatchGraphImpl->mTexture = d3d9Texture;
			TD3D9TextureAddRef(d3d9BatchGraphImpl->mTexture);
		}

		TD3D9BatchGraphLockVertexBuffer(d3d9BatchGraph);
		if (d3d9BatchGraphImpl->mVertexList)
		{
			T_D3D9VERTEXGRAPH * vertexListTemp = &d3d9BatchGraphImpl->mVertexList[
				d3d9BatchGraphImpl->mGraphCount * 6];
				++d3d9BatchGraphImpl->mGraphCount;

				vertexListTemp[0] = vertexList[0];
				vertexListTemp[1] = vertexList[1];
				vertexListTemp[2] = vertexList[2];

				vertexListTemp[3] = vertexList[1];
				vertexListTemp[4] = vertexList[3];
				vertexListTemp[5] = vertexList[2];
		}
	}
}

#endif // T_USE_D3D9
