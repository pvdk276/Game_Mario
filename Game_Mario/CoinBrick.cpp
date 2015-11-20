#include "CoinBrick.h"

CCoinBrick::CCoinBrick(int id, D3DXVECTOR2 position, CSprite* sprite) : CStaticObject(id, position, sprite)
{
	this->type = COIN_BRICK;
	this->width = 50;
	this->height = 50;
}

CCoinBrick::~CCoinBrick()
{
}

void CCoinBrick::Update()
{

}

void CCoinBrick::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}