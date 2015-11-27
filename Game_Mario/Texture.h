#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "GameGraphic.h"

class CTexture
{
private:
	//???ng d?n ??n file hình
	char* m_szFileName;
	//Kích th??c c?a hình
	RECT m_rectSize;
	//Con tr? DirectX Texture ch?a texture hi?n t?i
	LPDIRECT3DTEXTURE9 m_lpTexture;

	void load();
public:

	CTexture(char* fileName);
	~CTexture();
	void Draw(D3DXVECTOR2 pos);

};