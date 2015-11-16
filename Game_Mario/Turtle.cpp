#include "Turtle.h"

CTurtle::CTurtle(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite * sprite, float timeAmination, D3DXVECTOR2 maxVelocity, D3DXVECTOR2 maxAccel) : CLivingObject(type, position, width, height, sprite, timeAnimation, maxVelocity, maxAccel)
{

}

CTurtle::~CTurtle()
{
}

void CTurtle::UpdateAnimation(float delta_time)
{
	sprite->SetTimeAnimation(timeAnimation);
	if (type == TURTLE)
	{
		if (direction == 1)
		{
			sprite->UpdateSprite(delta_time, 2, 3, direction);
		}
		else sprite->UpdateSprite(delta_time, 8, 9, direction);
	}

	else if (type == TURTLE){
		if (direction == 1)
		{
			sprite->UpdateSprite(delta_time, 0, 1, direction);
		}
		else sprite->UpdateSprite(delta_time, 6, 7, direction);
	}
	else
	{
		if (direction == 1)
		{
			sprite->UpdateSprite(delta_time, 4, 5, direction);
		}
		else sprite->UpdateSprite(delta_time, 10, 11, direction);
	}
}
