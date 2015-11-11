#include "Coin.h"

CCoin::CCoin(CSprite * _coin, D3DXVECTOR2 _position)
{
	this->sprite = _coin;
	this->position = _position;
	this->width = 50;
	this->height = 50;
}

CCoin::~CCoin()
{
}

void CCoin::Render()
{
	this->sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

void CCoin::UpdateAnimation(float delta_time)
{
}
