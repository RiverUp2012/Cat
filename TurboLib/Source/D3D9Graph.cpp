
#include "../Include/Private.h"
#include "../Include/D3D9Common.h"
#include "../Include/CompileConfig.h"

#if defined T_USE_D3D9

typedef struct _T_D3D9GRAPH
{
	T_OBJECT mD3D9Texture;
	T_D3D9VERTEXGRAPH mVertexList[4];
	T_OBJECT mD3D9PaintDevice;
}
T_D3D9GRAPH;

#endif // T_USE_D3D9

T_OBJECT TD3D9GraphCreateFromImageFileW(
	T_OBJECT d3d9PaintDevice,
	const wchar_t * imageFileName,
	const unsigned int colorKey)
{
#if defined T_USE_D3D9

	T_D3D9GRAPH * d3d9GraphImpl = (T_D3D9GRAPH *)TMalloc0(sizeof(T_D3D9GRAPH));
	if (d3d9GraphImpl)
	{
		d3d9GraphImpl->mD3D9Texture = TD3D9TextureCreateFromFileW(
			d3d9PaintDevice,
			imageFileName,
			colorKey);
		if (d3d9GraphImpl->mD3D9Texture)
		{
			for (int i = 0; i < 4; ++i)
			{
				d3d9GraphImpl->mVertexList[i].z = 0.0f;
				d3d9GraphImpl->mVertexList[i].rhw = 1.0f;
				d3d9GraphImpl->mVertexList[i].diffuse = 0xffffffff;
			}

			d3d9GraphImpl->mD3D9PaintDevice = d3d9PaintDevice;

			return (T_OBJECT)d3d9GraphImpl;
		}

		TFree(d3d9GraphImpl);
		d3d9GraphImpl = 0;
	}

#endif // T_USE_D3D9

	return 0;
}

void TD3D9GraphDestroy(
	T_OBJECT d3d9Graph)
{
#if defined T_USE_D3D9

	T_D3D9GRAPH * d3d9GraphImpl = (T_D3D9GRAPH *)d3d9Graph;
	if (d3d9GraphImpl)
	{
		if (d3d9GraphImpl->mD3D9Texture)
		{
			TD3D9TextureDestroy(d3d9GraphImpl->mD3D9Texture);
			d3d9GraphImpl->mD3D9Texture = 0;
		}

		TFree(d3d9GraphImpl);
		d3d9GraphImpl = 0;
	}

#endif // T_USE_D3D9
}

void TD3D9GraphPaintV1(
	T_OBJECT d3d9Graph,
	const float graphX,
	const float graphY)
{
#if defined T_USE_D3D9

	float imageWidth = 0;
	float imageHeight = 0;
	float surfaceWidth = 0;
	float surfaceHeight = 9;

	T_D3D9GRAPH * d3d9GraphImpl = (T_D3D9GRAPH *)d3d9Graph;
	if (d3d9GraphImpl &&
		d3d9GraphImpl->mD3D9Texture &&
		d3d9GraphImpl->mD3D9PaintDevice)
	{
		TD3D9TextureGetImageSize(
			d3d9GraphImpl->mD3D9Texture,
			&imageWidth,
			&imageHeight);
		TD3D9TextureGetSurfaceSize(
			d3d9GraphImpl->mD3D9Texture,
			&surfaceWidth,
			&surfaceHeight);
		if (surfaceWidth > 0 && surfaceHeight > 0)
		{
			d3d9GraphImpl->mVertexList[0].x = graphX;
			d3d9GraphImpl->mVertexList[0].y = graphY;
			d3d9GraphImpl->mVertexList[0].u = 0;
			d3d9GraphImpl->mVertexList[0].v = 0;

			d3d9GraphImpl->mVertexList[1].x = graphX + imageWidth;
			d3d9GraphImpl->mVertexList[1].y = graphY;
			d3d9GraphImpl->mVertexList[1].u = (imageWidth + 0.5f) / surfaceWidth;
			d3d9GraphImpl->mVertexList[1].v = 0;

			d3d9GraphImpl->mVertexList[2].x = graphX;
			d3d9GraphImpl->mVertexList[2].y = graphY + imageHeight;
			d3d9GraphImpl->mVertexList[2].u = 0;
			d3d9GraphImpl->mVertexList[2].v = (imageHeight + 0.5f) / surfaceHeight;

			d3d9GraphImpl->mVertexList[3].x = graphX + imageWidth;
			d3d9GraphImpl->mVertexList[3].y = graphY + imageHeight;
			d3d9GraphImpl->mVertexList[3].u = (imageWidth + 0.5f) / surfaceWidth;
			d3d9GraphImpl->mVertexList[3].v = (imageHeight + 0.5f) / surfaceHeight;

			TD3D9PaintDevicePaintGraph(
				d3d9GraphImpl->mD3D9PaintDevice,
				d3d9GraphImpl->mVertexList,
				d3d9GraphImpl->mD3D9Texture);
		}
	}

#endif // T_USE_D3D9
}
