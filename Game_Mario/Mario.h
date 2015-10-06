#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Global.h"

class CMario : public CSingleton<CMario>, public CGameObject
{
public:

	float gravity;
	int state;

	CSprite* smallMario;
	CSprite* bigMario;
	CSprite* currentSprite;

	CMario();
	~CMario();

	void Render();
	void Update(float delta_time);
};