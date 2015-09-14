//#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include "Global.h"

class GameGraphic
{
public:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backBuffer;

	GameGraphic();
	~GameGraphic();

	//Kh?i t?o d3ddevice
	int Init(HWND hWnd);

	//h?y b? c?p ph�t cho c�c bi?n
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