//#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include "Global.h"
#include "Singleton.h"

class CGameGraphic : public CSingleton<CGameGraphic>
{
public:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backBuffer;
	LPDIRECT3DSURFACE9 surface;

	CGameGraphic();
	~CGameGraphic();

	//Kh?i t?o d3ddevice
	int Init(HWND hWnd);

	//h?y b? c?p phát cho các bi?n
	void destroy();

	//clear backbuffer tr??c khi render
	void beginRender();

	//??a hình ?nh t? backfuffer lên frontbuffer
	//g?i ??n hàm Present
	void endRender();

	//l?y con tr? ??n backbuffer hi?n th?i
	LPDIRECT3DSURFACE9 getBackbuffer();

	//v? hình ?nh lên backbuffer hi?n th?i
	//srcSurface surface c?n v?
	//srcRect v? trí surface c?n v?
	//destRect v? trí backbuffer s? v? t?i
	void strectRect(LPDIRECT3DSURFACE9 srcSurface, const RECT *srcRect, const RECT *destRect);
};