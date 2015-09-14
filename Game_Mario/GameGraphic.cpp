#include "GameGraphic.h"

//using namespace std;

GameGraphic::GameGraphic()
{
	d3d = NULL;
	d3ddv = NULL;
}

GameGraphic::~GameGraphic()
{
}

int GameGraphic::Init(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) return 0;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
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

	return 1;
}

void GameGraphic::destroy()
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

void GameGraphic::beginRender()
{
	if (NULL == d3ddv)
	{
		OutputDebugString("[GameGraphic.cpp] Cannot begin render.");
		return;
	}

	// Clear the backbuffer to a black color
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

void GameGraphic::endRender()
{
	// Present the backbuffer contents to the display
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DSURFACE9 GameGraphic::getBackbuffer()
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

void GameGraphic::strectRect(LPDIRECT3DSURFACE9 srcSurface, const RECT * srcRect, const RECT * destRect)
{
	d3ddv->StretchRect(srcSurface, srcRect, getBackbuffer(), destRect, D3DTEXF_NONE);
}
