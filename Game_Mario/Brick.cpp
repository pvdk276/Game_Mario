#include "Brick.h"

CBrick::CBrick(int id, D3DXVECTOR2 position, CSprite* sprite) : CStaticObject(id, position, sprite)
{
	this->type = BRICK;
	this->width = 50;
	this->height = 50;
}

CBrick::~CBrick()
{
}

void CBrick::Update()
{
}

void CBrick::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}