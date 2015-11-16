#pragma once

#include "LivingObject.h"

class CEnemy : public CLivingObject
{
	CEnemy(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite* sprite, float timeAnimation, D3DXVECTOR2 maxVelocity, D3DXVECTOR2 maxAccel);
	~CEnemy();
	void UpdateAnimation(float delta_time);
};
