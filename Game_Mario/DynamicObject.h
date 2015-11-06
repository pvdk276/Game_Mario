#pragma once

#include "GameObject.h"

class CDynamicObject : public CGameObject
{
public:
	int direct;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 accel;
	D3DXVECTOR2 maxAccel;
	CSprite sprite;

	CDynamicObject();
	~CDynamicObject();
	CBox GetBox();

	virtual void Update(float delta_time) = 0;	//general update function
	virtual void UpdatePosition(float delta_time) = 0;
	virtual void UpdateAnimation(float delta_time) = 0;
	virtual void Render() = 0;
};