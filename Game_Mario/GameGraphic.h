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
	LPD3DXSPRITE spriteHandler;

	CGameGraphic();
	~CGameGraphic();

	//init game graphic
	int Init(HWND hWnd);

	//init surface
	int InitSurface(std::string filePath);

	//render from surface to back buffer
	void RenderBackbuffer(RECT *fromSurface, RECT *toBackbuffer);

	//destroy game graphic
	void destroy();

	//clear backbuffer tr??c khi render
	void beginRender();

	//??a h�nh ?nh t? backfuffer l�n frontbuffer
	//g?i ??n h�m Present
	void endRender();

	//l?y con tr? ??n backbuffer hi?n th?i
	LPDIRECT3DSURFACE9 getBackbuffer();

	//v? h�nh ?nh l�n backbuffer hi?n th?i
	//srcSurface surface c?n v?
	//srcRect v? tr� surface c?n v?
	//destRect v? tr� backbuffer s? v? t?i
	void strectRect(LPDIRECT3DSURFACE9 srcSurface, const RECT *srcRect, const RECT *destRect);
};