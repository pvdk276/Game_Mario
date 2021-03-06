#include "DynamicObject.h"

CDynamicObject::CDynamicObject(int id, D3DXVECTOR2 position, CSprite* sprite) : CBaseObject(id, position, sprite)
{
	curIndex = 0;
	curTime = 0;
	direction = 1;
	velocity = D3DXVECTOR2(0.0f, 0.0f);
	accel = D3DXVECTOR2(0.0f, 0.0f);
	timer = D3DXVECTOR2(0.0f, 0.0f);
	this->isStatic = true;
}

CDynamicObject::~CDynamicObject()
{

}

CBox CDynamicObject::GetBox()
{
	CBox box(position.x, 
		position.y, 
		width, 
		height, 
		velocity.x, 
		velocity.y, 
		accel.x, 
		accel.y, 
		timer.x, 
		timer.y);
	return box;
}

std::string CDynamicObject::GetType()
{
	return "DynamicObject";
}
