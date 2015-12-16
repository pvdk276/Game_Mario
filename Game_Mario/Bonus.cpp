#include "Bonus.h"

CBonus::CBonus(int id, ObjectName type, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	type = type;
	width = 50;
	height = 50;
	isOutOfBlock = false;
	posOfBlock = position;
	velocity = D3DXVECTOR2(0.0f, 0.0f);
}

CBonus::~CBonus()
{
}

void CBonus::Update(float delta_time)
{
	

	if (!isOutOfBlock)
	{		
		if (position.y < posOfBlock.y + width)
		{
			position.y += velocity.y * delta_time;
		}
		else
		{
			position.y = posOfBlock.y + width;
			velocity.y = 0.0f;
			isOutOfBlock = true;
		}
	}
	
	if (type == COIN)
	{
		UpdateAnimation(delta_time, 0, 1, direction);
		if (isOutOfBlock) isDead = true;
	}
	else if (type == FLOWER)
	{
		UpdateAnimation(delta_time, 0, 3, direction);
	}
	else if (type == STAR)
	{
		UpdateAnimation(delta_time, 0, 3, direction);
	}
	else if (type == RED_MUSHROOM || type == GREEN_MUSHROOM)
	{
		if (isOutOfBlock) velocity.x = -10.0f;
	}
}

void CBonus::Render()
{
	if(type == RED_MUSHROOM) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
	else if(type == GREEN_MUSHROOM) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
	else sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
