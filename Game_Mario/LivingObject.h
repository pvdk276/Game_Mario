#pragma once

#include "DynamicObject.h"
#include "Camera.h"

class CLivingObject : public CDynamicObject
{
public:
	int direction;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 accel;
	D3DXVECTOR2 maxAccel;

	CLivingObject(
		ObjectName type, 
		D3DXVECTOR2 position, 
		float width, 
		float height, 
		CSprite* sprite, 
		float timeAnimation,
		D3DXVECTOR2 maxVelocity,
		D3DXVECTOR2 maxAccel
		);
	~CLivingObject();

	CBox GetBox();
	virtual void UpdateAnimation(float delta_time) = 0;
};