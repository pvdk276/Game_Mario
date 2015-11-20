#include "LivingObject.h"

CLivingObject::CLivingObject(int id, D3DXVECTOR2 position, CSprite* sprite)	: CDynamicObject(id, position, sprite)
{

}

CLivingObject::~CLivingObject()
{

}

std::string CLivingObject::GetType()
{
	return "LivingObject";
}