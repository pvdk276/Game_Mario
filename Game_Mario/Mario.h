#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "Sprite.h"

class CMario : public CSingleton<CMario>, public CGameObject
{
public:
	//float speedX;
	//float speedY;
	//float lastSpeedX;

	CSprite* smallMario;
	CSprite* bigMario;
	CSprite* currentSprite;

	CMario();
	~CMario();

	void Render();
	void Update(float delta_time);
};