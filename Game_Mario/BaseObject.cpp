﻿#include "BaseObject.h"

CBaseObject::CBaseObject(int id, D3DXVECTOR2 flagPosition, CSprite* sprite)
{
	this->id = id;
	this->flagPosition = flagPosition;
	this->position = flagPosition;
	this->rootPosition = flagPosition;
	this->sprite = sprite;
	this->isCollision = false;
	this->isDead = false;
	this->unLocked = false;
	this->isShoot = false;
	
} 

CBaseObject::~CBaseObject()
{
	if (sprite != nullptr)
	{
		delete sprite;
	}
}
