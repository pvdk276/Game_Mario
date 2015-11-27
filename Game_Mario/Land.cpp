#include "Land.h"

CLand::CLand(int id, ObjectName type, D3DXVECTOR2 position, CSprite * sprite) : CStaticObject(id, position, sprite)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
}

CLand::~CLand()
{
}

void CLand::Update(float delta_time)
{
}

void CLand::Render()
{
	if(type == LEFT_LAND) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
	else if(type == CENTER_LAND) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
	else sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 2);
}
