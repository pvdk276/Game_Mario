#include "DynamicObject.h"

CDynamicObject::CDynamicObject(int id, D3DXVECTOR2 position, CSprite* sprite) : CBaseObject(id, position, sprite)
{
	animationTime = TIME_ANIMATION;
	curIndex = 0;
	curTime = 0;
	direction = 1;
	velocity = D3DXVECTOR2(0.0f, 0.0f);
}

CDynamicObject::~CDynamicObject()
{

}

CBox CDynamicObject::GetBox()
{
	CBox box(position.x, position.y, width, height, velocity.x, velocity.y);
	return box;
}

std::string CDynamicObject::GetType()
{
	return "DynamicObject";
}
