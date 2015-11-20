#include "DynamicObject.h"

CDynamicObject::CDynamicObject(int id, D3DXVECTOR2 position, CSprite* sprite) : CBaseObject(id, position, sprite)
{
	
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
