#pragma once

#include "Box.h"
#include "Sprite.h"
#include "Global.h"

class CBaseObject
{
public:
	ObjectName type;
	D3DXVECTOR2 position;
	float width;
	float height;
	CSprite* sprite;

	CBaseObject(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite* sprite);
	~CBaseObject();
};