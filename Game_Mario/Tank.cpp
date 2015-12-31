#include "Tank.h"

CTank::CTank(int id, D3DXVECTOR2 position, CSprite * sprite1, CSprite* sprite2) : CStaticObject(id, position, sprite1)
{
	this->type = TANK;
	this->width = 100;
	this->height = 100;

	bullet = sprite2;
}

CTank::~CTank()
{
}

void CTank::Update(float delta_time)
{
}

void CTank::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}
