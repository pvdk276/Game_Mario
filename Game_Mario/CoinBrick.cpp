#include "CoinBrick.h"

CCoinBrick::CCoinBrick(CSprite * _coinBrick, D3DXVECTOR2 _position)
{
	this->sprite = _coinBrick;
	this->position = _position;
	this->width = 50;
	this->height = 50;
}

CCoinBrick::~CCoinBrick()
{
}

void CCoinBrick::Render()
{
	this->sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

void CCoinBrick::UpdateAnimation(float delta_time)
{
}
