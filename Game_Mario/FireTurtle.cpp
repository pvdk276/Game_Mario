#include "FireTurtle.h"

CFireTurtle::CFireTurtle(int id, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = FIRE_TURTLE;
	this->width = 50;
	this->height = 50;
}

CFireTurtle::~CFireTurtle()
{
}

void CFireTurtle::Update(float delta_time)
{
	//update position

	//upate animation
	if (direction == 1)
	{
		UpdateAnimation(delta_time, 2, 3, direction);
	}
	else UpdateAnimation(delta_time, 0, 1, direction);
}

void CFireTurtle::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}