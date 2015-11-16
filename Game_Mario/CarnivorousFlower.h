#pragma once

#include "LivingObject.h"

class CCarnivorousFlower : public CLivingObject
{

	CCarnivorousFlower(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite* sprite, float timeAnimation, D3DXVECTOR2 maxVelocity, D3DXVECTOR2 maxAccel);
	~CCarnivorousFlower();
	void UpdateAnimation(float delta_time);
};
