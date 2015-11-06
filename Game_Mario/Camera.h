#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "Sprite.h"

class CCamera : public CSingleton<CCamera>
{
public:
	int** matrix;
	int m;
	int n;
	D3DXVECTOR2 position;
	float width;
	float height;

	CSprite* sprite;

	//init camera
	CCamera();

	//destroy camera
	~CCamera();

	//render camera
	void Render();

	//update position of camera by position of mario
	void Update(float x, float y);
};