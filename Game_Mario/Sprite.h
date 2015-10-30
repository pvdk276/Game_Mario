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
	float timeAnimation;
	float timeCurrent;

	int width;
	int height;
	int count;
	int spritePerRow;
	

	RECT rect;

	CSprite(LPD3DXSPRITE spriteHandler, LPCSTR filePath, int width, int height, int count, int spritePerRow, int transparentColor);
	~CSprite();

	
	void Next();	//next picture in a picture chain
	void Reset();	//return to the first picture
	void Render(float posX, float posY, float vpx, float vpy, float direction);	//render character
	void RenderMap(float posX, float posY, float vpx, float vpy, int value);	//render map
	void UpdateSprite();
	void UpdateSprite(float, int, int, int);
	void PositionSprite();

	//set
	void SetCurrentIndex(int _cursprite) { curIndex = _cursprite; }
	void SetTimeAnimation(float _time) { timeAnimation = _time; }
};