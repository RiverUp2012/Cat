
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

typedef HRESULT (WINAPI * sgeD3DXCreateFontW)(
	LPDIRECT3DDEVICE9       pDevice,
	INT                     Height,
	UINT                    Width,
	UINT                    Weight,
	UINT                    MipLevels,
	BOOL                    Italic,
	DWORD                   CharSet,
	DWORD                   OutputPrecision,
	DWORD                   Quality,
	DWORD                   PitchAndFamily,
	LPCWSTR                 pFaceName,
	LPD3DXFONT*             ppFont);

sgeFont::sgeFont()
{
	mD3DXFont = 0;
}

sgeFont::~sgeFont()
{
	destroy();
}

bool sgeFont::createW(
	const wchar_t * fontName,
	const int fontWidth,
	const int fontHeight)
{
	ID3DXFont * d3dxFont = 0;

	destroy();

	IDirect3DDevice9 * d3dDev9 = gVideoDevice.getIDirect3DDevice9();
	sgeD3DXCreateFontW d3dXCreateFontW = (sgeD3DXCreateFontW)
		gModuleD3DX9.getProcAddressA("D3DXCreateFontW");
	if (d3dDev9 && d3dXCreateFontW && fontName)
	{
		if (SUCCEEDED(d3dXCreateFontW(
			d3dDev9,
			fontHeight,
			fontWidth,
			400,
			1,
			FALSE,
			GB2312_CHARSET,
			0,
			0,
			0,
			fontName,
			&d3dxFont)))
		{
			mD3DXFont = (void *)d3dxFont;
			return true;
		}
	}

	return false;
}

void sgeFont::destroy(void)
{
	ID3DXFont * d3dxFont = (ID3DXFont *)mD3DXFont;
	if (d3dxFont)
	{
		if (gVideoDevice.isAlready())
		{
			d3dxFont->Release();
		}
	}

	mD3DXFont = 0;
}

bool sgeFont::paintTextW(
	const wchar_t * text,
	const int charsToPaint,
	const sgeRect<int> & paintRect,
	const unsigned int paintFormat,
	const unsigned int color)
{
	RECT textRect = { 0 };
	ID3DXFont * d3dxFont = (ID3DXFont *)mD3DXFont;
	sgeEngine * engine = sgeEngine::get();

	if (engine)
	{
		gBatchSprite.flush();
		gBatchPrimitive.flush();
	}

	if (d3dxFont && text)
	{
		textRect.left = paintRect.mX;
		textRect.top = paintRect.mY;
		textRect.right = paintRect.getRight();
		textRect.bottom = paintRect.getBottom();

		if (SUCCEEDED(d3dxFont->DrawTextW(
			0,
			text,
			charsToPaint,
			&textRect,
			paintFormat,
			color)))
		{
			return true;
		}
	}

	return false;
}

bool sgeFont::calcTextSizeW(
	const wchar_t * text,
	const int charsToCalc,
	const sgeSize<int> & layoutSize,
	const unsigned int calcFormat,
	sgeSize<int> & textSize)
{
	RECT textRect = { 0 };
	ID3DXFont * d3dxFont = (ID3DXFont *)mD3DXFont;

	if (d3dxFont && text)
	{
		textRect.right = layoutSize.mWidth;
		textRect.bottom = layoutSize.mHeight;

		if (SUCCEEDED(d3dxFont->DrawTextW(
			0,
			text,
			charsToCalc,
			&textRect,
			calcFormat | DT_CALCRECT,
			0)))
		{
			textSize.mWidth = textRect.right - textRect.left;
			textSize.mHeight = textRect.bottom - textRect.top;

			return true;
		}
	}

	return false;
}
