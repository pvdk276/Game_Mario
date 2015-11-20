#include "Turtle.h"

CTurtle::CTurtle(int id, ObjectName type, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
	this->direction = 1;
}

CTurtle::~CTurtle()
{
}

void CTurtle::Update(float delta_time)
{
	if (type == WING_TURTLE)
	{
		if (direction == 1)
		{
			UpdateAnimation(delta_time, 0, 1, direction);
		}
		else UpdateAnimation(delta_time, 6, 7, direction);
	}
	else if (type == TURTLE)
	{
		if (direction == 1)
		{
			UpdateAnimation(delta_time, 2, 3, direction);
		}
		else UpdateAnimation(delta_time, 8, 9, direction);
	}
	else
	{
		UpdateAnimation(delta_time, 4, 5, direction);
	}
	
}

void CTurtle::Render()
{
	if (curTime == 0)
	{
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	}
}