#include "Spring.h"

CSpring::CSpring(int id, D3DXVECTOR2 position, CSprite * sprite) : CDynamicObject(id, position, sprite)
{
	this->type = SPRING;
	this->width = 50;
	this->height = 100;
	direction = 1;
}

CSpring::~CSpring()
{
}

void CSpring::Update(float delta_time)
{
}

void CSpring::Render()
{
	//at normal
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}
