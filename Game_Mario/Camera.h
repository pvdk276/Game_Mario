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

	CCamera();
	~CCamera();
	void Render();
	void Update(float x, float y);
};