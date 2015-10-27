#pragma once
#include <d3dx9.h>

class CSprite
{
public:
	LPDIRECT3DTEXTURE9 image;
	LPD3DXSPRITE spriteHandler;

	int curIndex;
	int beginIndex;
	int endIndex;

	int width;
	int height;
	int count;
	int spritePerRow;
	float timeAmination;
	float timeCurrent;

	CSprite(LPD3DXSPRITE spriteHandler, LPCSTR filePath, int width, int height, int count, int spritePerRow, int transparentColor);
	~CSprite();

	//next picture in a picture chain
	void Next();

	//return to the first picture
	void Reset();

	//render character
	void Render(float posX, float posY, float vpx, float vpy, float direction);

	//render map
	void RenderMap(float posX, float posY, float vpx, float vpy, int value);
	void UpdateSprite();
	void UpdateSprite(float, int, int, int);
	void PositionSprite();
	//set
	void SetCurrentSprite(int _cursprite) { index = _cursprite; }
	void SetTimeAmination(float _time) { m_timeAmination = _time; }
};