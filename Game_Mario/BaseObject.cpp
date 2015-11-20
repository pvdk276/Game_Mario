#include "BaseObject.h"

CBaseObject::CBaseObject(int id, D3DXVECTOR2 position, CSprite* sprite)
{
	this->id = id;
	this->position = position;
	this->sprite = sprite;
}

CBaseObject::~CBaseObject()
{
	if (sprite != nullptr)
	{
		delete sprite;
	}
}
