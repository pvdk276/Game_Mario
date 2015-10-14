#include "GameObject.h"

CGameObject::CGameObject()
{

}

CGameObject::CGameObject(int id, int typeId, float positionX, float positionY, float width, float height)
{
	this->id = id;
	this->typeId = typeId;
	this->positionX = positionX;
	this->positionY = positionY;
	this->width = width;
	this->height = height;
}

CBox CGameObject::GetBox()
{
	CBox box(positionX, positionY, width, height, speedX, speedY);
	return box;
}