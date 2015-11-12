#include "BaseObject.h"

CBaseObject::CBaseObject(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite* sprite)
{
	this->type = type;
	this->position = position;
	this->width = width;
	this->height = height;
	this->sprite = sprite;
}

CBaseObject::~CBaseObject()
{
	if (sprite != nullptr)
	{
		delete sprite;
	}
}