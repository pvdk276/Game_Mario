#include "CoinBlock.h"

CCoinBlock::CCoinBlock(int id, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = COIN_BLOCK;
	this->width = 50;
	this->height = 50;
}

CCoinBlock::~CCoinBlock()
{
}

void CCoinBlock::Update(float delta_time)
{
	UpdateAnimation(delta_time, 0, 1, direction);
}

void CCoinBlock::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}