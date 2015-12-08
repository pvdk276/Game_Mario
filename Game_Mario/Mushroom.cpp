#include "Mushroom.h"

CMushroom::CMushroom(int id, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = MUSHROOM;
	this->width = 50;
	this->height = 50;
}

CMushroom::~CMushroom()
{
}

void CMushroom::Update(float delta_time)
{
	UpdateAnimation(delta_time, 0, 1, direction);
}

void CMushroom::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
