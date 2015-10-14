#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "Sprite.h"

class CCamera : public CSingleton<CCamera>, public CGameObject
{
public:
	int** matrix;
	int m;
	int n;

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