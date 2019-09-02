
#include "../Include/Private.h"
#include "../Include/D3D9Common.h"
#include "../Include/CompileConfig.h"

#if defined T_USE_D3D9

typedef HRESULT (WINAPI * TD3DXCreateTextureFromFileExW)(
	LPDIRECT3DDEVICE9         pDevice,
	LPCWSTR                   pSrcFile,
	UINT                      Width,
	UINT                      Height,
	UINT                      MipLevels,
	DWORD                     Usage,
	D3DFORMAT                 Format,
	D3DPOOL                   Pool,
	DWORD                     Filter,
	DWORD                     MipFilter,
	D3DCOLOR                  ColorKey,
	D3DXIMAGE_INFO*           pSrcInfo,
	PALETTEENTRY*             pPalette,
	LPDIRECT3DTEXTURE9*       ppTexture);

#define T_MAX_D3D9TEXTURE (64)
#define T_MAX_D3D9TEXTURE_IMAGE_FILE_NAME_SIZE (520)

typedef struct _T_D3D9TEXTURE
{
	struct IDirect3DTexture9 * mD3DTex9;
	wchar_t mImageFileName[T_MAX_D3D9TEXTURE_IMAGE_FILE_NAME_SIZE];
	int mRefCount;
	float mImageWidth;
	float mImageHeight;
	float mSurfaceWidth;
	float mSurfaceHeight;
}
T_D3D9TEXTURE;

static T_D3D9TEXTURE gD3D9TextureArray[T_MAX_D3D9TEXTURE] = { 0 };
static TD3DXCreateTextureFromFileExW gD3DXCreateTextureFromFileExW = 0;

static T_D3D9TEXTURE * TFindUnuseD3D9Texture(void)
{
	for (int i = 0; i < T_MAX_D3D9TEXTURE; ++i)
	{
		if (!gD3D9TextureArray[i].mD3DTex9)
		{
			return &gD3D9TextureArray[i];
		}
	}

	return 0;
}

static T_D3D9TEXTURE * TFindD3D9TextureByImageFileNameW(
	const wchar_t * imageFileName)
{
	if (imageFileName)
	{
		for (int i = 0; i < T_MAX_D3D9TEXTURE; ++i)
		{
			if (gD3D9TextureArray[i].mD3DTex9 &&
				0 == _wcsicmp(imageFileName, gD3D9TextureArray[i].mImageFileName))
			{
				return &gD3D9TextureArray[i];
			}
		}
	}

	return 0;
}

T_OBJECT TD3D9TextureCreateFromFileW(
	T_OBJECT d3d9PaintDevice,
	const wchar_t * imageFileName,
	const unsigned int colorKey)
{
	struct IDirect3DDevice9 * d3dDev9 = TD3D9PaintDeviceGetIDirect3DDevice9(d3d9PaintDevice);
	T_D3D9TEXTURE * d3d9TextureImpl = 0;
	D3DXIMAGE_INFO imgInfo = { 0 };
	D3DSURFACE_DESC surfDesc;
	
	if (!gD3DXCreateTextureFromFileExW)
	{
		gD3DXCreateTextureFromFileExW = (TD3DXCreateTextureFromFileExW)TModuleGetProcAddress(
			TGetD3DX9Module(),
			L"D3DXCreateTextureFromFileExW");
	}

	if (imageFileName && gD3DXCreateTextureFromFileExW && d3dDev9)
	{
		d3d9TextureImpl = TFindD3D9TextureByImageFileNameW(imageFileName);
		if (d3d9TextureImpl)
		{
			++d3d9TextureImpl->mRefCount;
			return (T_OBJECT)d3d9TextureImpl;
		}
		else
		{
			d3d9TextureImpl = TFindUnuseD3D9Texture();
			if (d3d9TextureImpl)
			{
				if (SUCCEEDED(gD3DXCreateTextureFromFileExW(
					d3dDev9,
					imageFileName,
					D3DX_DEFAULT,
					D3DX_DEFAULT,
					1,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_DEFAULT,
					D3DX_FILTER_NONE,
					D3DX_FILTER_NONE,
					colorKey,
					&imgInfo,
					0,
					&d3d9TextureImpl->mD3DTex9)))
				{
					if (SUCCEEDED(d3d9TextureImpl->mD3DTex9->GetLevelDesc(
						0,
						&surfDesc)))
					{
						TStringCopyW(d3d9TextureImpl->mImageFileName, imageFileName, 0);
						d3d9TextureImpl->mImageWidth = (float)imgInfo.Width;
						d3d9TextureImpl->mImageHeight = (float)imgInfo.Height;
						d3d9TextureImpl->mSurfaceWidth = (float)surfDesc.Width;
						d3d9TextureImpl->mSurfaceHeight = (float)surfDesc.Height;

						return (T_OBJECT)d3d9TextureImpl;
					}

					d3d9TextureImpl->mD3DTex9->Release();
					d3d9TextureImpl->mD3DTex9 = 0;
				}
			}
		}
	}

	return 0;
}

void TD3D9TextureDestroy(
	T_OBJECT d3d9Texture)
{
	T_D3D9TEXTURE * d3d9TextureImpl = (T_D3D9TEXTURE *)d3d9Texture;
	if (d3d9TextureImpl)
	{
		--d3d9TextureImpl->mRefCount;
		if (d3d9TextureImpl->mRefCount <= 0)
		{
			if (d3d9TextureImpl->mD3DTex9)
			{
				d3d9TextureImpl->mD3DTex9->Release();
				d3d9TextureImpl->mD3DTex9 = 0;
			}

			TMemset(d3d9TextureImpl, sizeof(T_D3D9TEXTURE), 0);
		}
	}
}

struct IDirect3DTexture9 * TD3D9TextureGetIDirect3DTexture9(
	T_OBJECT d3d9Texture)
{
	T_D3D9TEXTURE * d3d9TextureImpl = (T_D3D9TEXTURE *)d3d9Texture;

	return d3d9TextureImpl ? d3d9TextureImpl->mD3DTex9 : 0;
}

void TD3D9TextureAddRef(
	T_OBJECT d3d9Texture)
{
	T_D3D9TEXTURE * d3d9TextureImpl = (T_D3D9TEXTURE *)d3d9Texture;
	if (d3d9TextureImpl)
	{
		++d3d9TextureImpl->mRefCount;
	}
}

void TD3D9TextureGetImageSize(
	T_OBJECT d3d9Texture,
	float * imageWidth,
	float * imageHeight)
{
	T_D3D9TEXTURE * d3d9TextureImpl = (T_D3D9TEXTURE *)d3d9Texture;
	if (d3d9TextureImpl)
	{
		if (imageWidth)
		{
			*imageWidth = d3d9TextureImpl->mImageWidth;
		}

		if (imageHeight)
		{
			*imageHeight = d3d9TextureImpl->mImageHeight;
		}
	}
}

void TD3D9TextureGetSurfaceSize(
	T_OBJECT d3d9Texture,
	float * surfaceWidth,
	float * surfaceHeight)
{
	T_D3D9TEXTURE * d3d9TextureImpl = (T_D3D9TEXTURE *)d3d9Texture;
	if (d3d9TextureImpl)
	{
		if (surfaceWidth)
		{
			*surfaceWidth = d3d9TextureImpl->mSurfaceWidth;
		}

		if (surfaceHeight)
		{
			*surfaceHeight = d3d9TextureImpl->mSurfaceHeight;
		}
	}
}

#endif
