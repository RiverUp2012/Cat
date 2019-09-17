
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

typedef HRESULT (WINAPI * glD3DXCreateTextureFromFileExW)(
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
typedef HRESULT (WINAPI * glD3DXCreateTextureFromFileInMemoryEx)(
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

glTexture::glTexture() {
	mD3DTex9 = 0;
}

glTexture::~glTexture() {
	destroy();
}

bool glTexture::createFromFileW(
	const wchar_t * fileName,
	const unsigned int colorKey) {
	D3DXIMAGE_INFO imgInfo = { 0 };
	D3DSURFACE_DESC surfDesc;
	IDirect3DTexture9 * d3dTex9 = 0;
	destroy();
	IDirect3DDevice9 * d3dDev9 = gVideoDevice.getIDirect3DDevice9();
	glD3DXCreateTextureFromFileExW d3dXCreateTextureFromFileExW = (glD3DXCreateTextureFromFileExW)
		gModuleD3DX9.getProcAddressA("D3DXCreateTextureFromFileExW");
	if (d3dDev9 && fileName && d3dXCreateTextureFromFileExW) {
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
			&d3dTex9))) {
			mImageSize = glSize<float>((float)imgInfo.Width, (float)imgInfo.Height);
			if (SUCCEEDED(d3dTex9->GetLevelDesc(0, &surfDesc))) {
				mSurfaceSize = glSize<float>((float)surfDesc.Width, (float)surfDesc.Height);
				mImageFileName = fileName;
				mD3DTex9 = (void *)d3dTex9;
				return true;
			}
		}
	}
	return false;
}

void glTexture::destroy(void) {
	IDirect3DTexture9 * d3d9 = (IDirect3DTexture9 *)mD3DTex9;
	if (d3d9) {
		if (gVideoDevice.isAlready()) {
			d3d9->Release();
		}
	}
	mD3DTex9 = 0;
	mImageSize = glSize<float>();
	mSurfaceSize = glSize<float>();
	mImageFileName.clear();
}

bool glTexture::isAlready(void) const {
	return mD3DTex9 ? true : false;
}

const glSize<float> & glTexture::getImageSize(void) const {
	return mImageSize;
}

const glSize<float> & glTexture::getSurfaceSize(void) const {
	return mSurfaceSize;
}

void * glTexture::getIDirect3DTexture9(void) const {
	return mD3DTex9;
}

const wchar_t * glTexture::getImageFileNameW(void) const {
	return mImageFileName.getString();
}
