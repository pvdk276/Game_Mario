#include "Tower.h"

CTower::CTower(int id, D3DXVECTOR2 position, CSprite * sprite) : CStaticObject(id, position, sprite)
{
	this->type = TOWER;
	this->width = 300;
	this->height = 400;
}

CTower::~CTower()
{
}

void CTower::Update(float delta_time)
{
}

void CTower::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}
