#include "Stone.h"

CStone::CStone(CSprite * _stone, D3DXVECTOR2 _position)
{
	this->sprite = _stone;
	this->position = _position;
	this->width = 50;
	this->height = 50;
}

CStone::~CStone()
{
}

void CStone::Render()
{
	this->sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

void CStone::UpdateAnimation(float delta_time)
{
}
