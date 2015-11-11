#include "Brick.h"

CBrick::CBrick(CSprite *brick, D3DXVECTOR2 _position)
{
	this->sprite = brick;
	this->position = _position;
	this->width = 50;
	this->height = 50;
}

CBrick::~CBrick()
{
}

void CBrick::Render()
{
	this->sprite->Render(position.x, position.y,CCamera::getInstance()->position.x, CCamera::getInstance()->position.y,1);
}

void CBrick::UpdateAnimation(float delta_time)
{
}
