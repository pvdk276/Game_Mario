#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(int id, int typeId, float positionX, float positionY, float width, float height)
{
	this->id = id;
	this->typeId = typeId;
	this->positionX = positionX;
	this->positionY = positionY;
	this->width = width;
	this->height = height;
}