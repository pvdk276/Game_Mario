#include "Bar.h"
#include "BinaryTree.h"

CBar::CBar(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = type;
	this->width = 200;
	this->height = 32;
	direction = 1;

	if (type == BAR_DOWN) velocity = D3DXVECTOR2(0.0f, -100.0f);
	else if (type == BAR_UP) velocity = D3DXVECTOR2(0.0f, 100.0f);
	else if (type == BAR_RIGHT) velocity = D3DXVECTOR2(100.0f,0.0f);
	else velocity = D3DXVECTOR2(0.0f, 0.0f);

	flagPosition = position;

	if(type == BAR_RIGHT) prePosition = position;
}


CBar::~CBar()
{
}

void CBar::Update(float delta_time)
{
	//Chiều dọc
	timer.y += delta_time;
	position.y = flagPosition.y + velocity.y * timer.y;

	//Chiều ngang
	timer.x += delta_time;
	position.x = flagPosition.x + velocity.x * timer.x;

	

	//update position
	switch (type)
	{
	case BAR_DOWN:
	{
		if (position.y < -16.0f)
		{
			position.y = 766.0f;
			flagPosition.y = position.y;
			timer.y = 0.0f;
		}
	}
	break;
	case BAR_UP:
	{
		if (position.y > 766)
		{
			position.y = -16.0f;
			flagPosition.y = position.y;
			timer.y = 0.0f;
		}
	}
	break;
	case BAR_RIGHT:
	{
		if (position.x <= prePosition.x || position.x >= prePosition.x + 100)
		{
			position.x = prePosition.x;
			timer.x = 0.0f;
			velocity.x *= -1.0f;
		}
	}
	break;
	default:
		break;
	}
}

void CBar::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}
