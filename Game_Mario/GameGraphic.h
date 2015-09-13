//#pragma once
#include <d3d9.h>

class GameGraphic
{
public:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backBuffer;

	int Init(HWND hWnd);
};