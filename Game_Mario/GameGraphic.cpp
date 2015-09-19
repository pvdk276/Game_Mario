#include "GameGraphic.h"

CGameGraphic::CGameGraphic()
{
	d3d = NULL;
	d3ddv = NULL;
}

CGameGraphic::~CGameGraphic()
{
}

int CGameGraphic::Init(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) return 0;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = 750;
	d3dpp.BackBufferHeight = 750;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;

	HRESULT result = d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->d3ddv);
	if (FAILED(result))
	{
		OutputDebugString("[GameGraphic.cpp] Cannot init Game graphic.");
		return 0;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	result =
		d3ddv->CreateOffscreenPlainSurface(
			750,
			750,// width 				100,				// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
			&surface,
			NULL);

	result = D3DXLoadSurfaceFromFile(
		surface, 		// surface
		NULL,			// destination palette	
		NULL,			// destination rectangle 
		"Resources/background.png",
		NULL,			// source rectangle
		D3DX_DEFAULT, 		// filter image
		0,			// transparency (0 = none)
		NULL);			// reserved


	return 1;
}

void CGameGraphic::destroy()
{
	if (d3ddv != NULL)
	{
		d3ddv->Release();
		d3ddv = NULL;
	}

	if (d3d != NULL)
	{
		d3d->Release();
		d3d = NULL;
	}
}

void CGameGraphic::beginRender()
{
	if (NULL == d3ddv)
	{
		OutputDebugString("[GameGraphic.cpp] Cannot begin render.");
		return;
	}

	// Clear the backbuffer to a black color
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

void CGameGraphic::endRender()
{
	// Present the backbuffer contents to the display
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DSURFACE9 CGameGraphic::getBackbuffer()
{
	IDirect3DSurface9* backbuffer = NULL;

	if (!d3ddv)
		return NULL;

	HRESULT hResult = d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	if (FAILED(hResult))
		return NULL;
	else
		return backbuffer;
}

void CGameGraphic::strectRect(LPDIRECT3DSURFACE9 srcSurface, const RECT * srcRect, const RECT * destRect)
{
	d3ddv->StretchRect(srcSurface, srcRect, getBackbuffer(), destRect, D3DTEXF_NONE);
}
