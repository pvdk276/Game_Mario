#include "CoinBlock.h"

CCoinBlock::CCoinBlock(CSprite * _coinBlock, D3DXVECTOR2 _position)
{
	this->sprite = _coinBlock;
	this->position = _position;
	this->width = 50;
	this->height = 50;
}

CCoinBlock::~CCoinBlock()
{
}

void CCoinBlock::Render()
{
	this->sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

void CCoinBlock::UpdateAnimation(float delta_time)
{
}
