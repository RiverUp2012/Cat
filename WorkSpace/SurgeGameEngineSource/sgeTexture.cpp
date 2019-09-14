
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

typedef HRESULT (WINAPI * sgeD3DXCreateTextureFromFileExW)(
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

typedef HRESULT (WINAPI * sgeD3DXCreateTextureFromFileInMemoryEx)(
	LPDIRECT3DDEVICE9         pDevice,
	LPCVOID                   pSrcData,
	UINT                      SrcDataSize,
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

sgeTexture::sgeTexture()
{
	mD3DTex9 = 0;
}

sgeTexture::~sgeTexture()
{
	destroy();
}

bool sgeTexture::createFromFileW(
	const wchar_t * fileName,
	const unsigned int colorKey)
{
	D3DXIMAGE_INFO imgInfo = { 0 };
	D3DSURFACE_DESC surfDesc;
	IDirect3DTexture9 * d3dTex9 = 0;

	destroy();

	IDirect3DDevice9 * d3dDev9 = gVideoDevice.getIDirect3DDevice9();
	sgeD3DXCreateTextureFromFileExW d3dXCreateTextureFromFileExW = (sgeD3DXCreateTextureFromFileExW)
		gModuleD3DX9.getProcAddressA("D3DXCreateTextureFromFileExW");
	if (d3dDev9 && fileName && d3dXCreateTextureFromFileExW)
	{
		if (SUCCEEDED(d3dXCreateTextureFromFileExW(
			d3dDev9,
			fileName,
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
			&d3dTex9)))
		{
			mImageSize = sgeSize<float>((float)imgInfo.Width, (float)imgInfo.Height);

			if (SUCCEEDED(d3dTex9->GetLevelDesc(0, &surfDesc)))
			{
				mSurfaceSize = sgeSize<float>((float)surfDesc.Width, (float)surfDesc.Height);
				mImageFileName = fileName;
				mD3DTex9 = (void *)d3dTex9;

				return true;
			}
		}
	}

	return false;
}

void sgeTexture::destroy(void)
{
	IDirect3DTexture9 * d3d9 = (IDirect3DTexture9 *)mD3DTex9;
	if (d3d9)
	{
		if (gVideoDevice.isAlready())
		{
			d3d9->Release();
		}
	}

	mD3DTex9 = 0;
	mImageSize = sgeSize<float>();
	mSurfaceSize = sgeSize<float>();
	mImageFileName.clear();
}

bool sgeTexture::isAlready(void) const
{
	return mD3DTex9 ? true : false;
}

const sgeSize<float> & sgeTexture::getImageSize(void) const
{
	return mImageSize;
}

const sgeSize<float> & sgeTexture::getSurfaceSize(void) const
{
	return mSurfaceSize;
}

void * sgeTexture::getIDirect3DTexture9(void) const
{
	return mD3DTex9;
}

const wchar_t * sgeTexture::getImageFileNameW(void) const
{
	return mImageFileName.getString();
}
