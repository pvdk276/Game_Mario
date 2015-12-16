#pragma once

#include "LivingObject.h"
enum Direction
{
	NONE = 0,
	LEFT = 0x01,
	JUMP = 0x02,
	RIGHT = 0x04,
	FALL = 0x08
};
class CCarnivorousFlower : public CLivingObject
{
public:
	bool _isDelayMove;
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 maxAccel;
	bool _isDead;
	Direction _direction;
	D3DXVECTOR2 accel;
	D3DXVECTOR2 _velocity;
	float _deltaTime;
	CCarnivorousFlower(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CCarnivorousFlower();
	
	void Update(float delta_time);
	void UpdatePosition(float delta_time);
	void Render();
};
