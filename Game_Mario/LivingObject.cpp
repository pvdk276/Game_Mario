#include "LivingObject.h"

CLivingObject::CLivingObject(ObjectName type,
	D3DXVECTOR2 position,
	float width,
	float height,
	CSprite* sprite,
	float timeAnimation,
	D3DXVECTOR2 maxVelocity,
	D3DXVECTOR2 maxAccel) : CDynamicObject(type, position, width, height, sprite, timeAnimation)
{
	direction = 1;
	this->velocity = D3DXVECTOR2(0.0f, 0.0f);
	this->accel = D3DXVECTOR2(0.0f, 0.0f);
	this->maxVelocity = maxVelocity;
	this->maxAccel = maxAccel;
}

CLivingObject::~CLivingObject()
{

}

CBox CLivingObject::GetBox()
{
	CBox box(position.x, position.y, width, height, velocity.x, velocity.y);
	return box;
}