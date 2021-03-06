#pragma once

#include "LivingObject.h"
#include "Mario.h"

class CEnemy : public CLivingObject
{
private:
	float deadTimer;
	bool beingShoot;
public:
	CEnemy(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CEnemy();

	void Update(float delta_time);
	void Render();
};
