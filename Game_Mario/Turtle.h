#pragma once

#include "DynamicObject.h"
#include "LivingObject.h"
#include "Global.h"

class CTurtle : public CLivingObject
{
public: 
	CTurtle(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite* sprite, float timeAnimation, D3DXVECTOR2 maxVelocity, D3DXVECTOR2 maxAccel);
	~CTurtle();
	void UpdateAnimation(float delta_time);
};
