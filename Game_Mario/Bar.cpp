#include "Bar.h"

CBar::CBar(int id, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = BAR;
	this->width = 200;
	this->height = 32;
}


CBar::~CBar()
{
}

void CBar::Update(float delta_time)
{
	//update position

	//update animation
}

void CBar::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}
