#include "Flower.h"

CFlower::CFlower(int id, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = FLOWER;
	this->width = 50;
	this->height = 50;
}

CFlower::~CFlower()
{
}

void CFlower::Update(float delta_time)
{
	UpdateAnimation(delta_time, 0, 1, direction);
}

void CFlower::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);

}
