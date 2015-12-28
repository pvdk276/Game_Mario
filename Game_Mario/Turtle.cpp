﻿#include "Turtle.h"
#include "BinaryTree.h"

CTurtle::CTurtle(int id, ObjectName type, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
	this->velocity = D3DXVECTOR2(-100.0f, 0.0f);
	m_countCollision = 0;
}

CTurtle::~CTurtle()
{
}

void CTurtle::Update(float delta_time)
{
	if (isCollision)
	{
		m_countCollision += 1;
		m_counttimer = 0;
	}
		

	//Check collision
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == PIPE ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == STONE ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == CARNIVOROUS_FLOWER_PIPE ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == PIPE_UP ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == PIPE_DOWN)
		{
			float normalx, normaly;
			float distanceX, distanceY;
			float value = CCollision::getInstance()->CheckCollision(
				this->GetBox(),
				CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox(),
				normalx, normaly, distanceX, distanceY, delta_time);
			if (value < 1) //a collision occur
			{
				timer.x = 0.0f;
				this->velocity.x *= -1;
				direction *= -1;
				flagPosition.x = this->position.x;
				break;
			}
		}
	}

	if (m_countCollision == 2)
	{
		velocity.x = direction * 300;
		timer.x = 0;
		flagPosition.x = position.x;
	}

	m_counttimer += delta_time;
	if (m_counttimer >= delta_time * 60 * 5 && m_countCollision == 1)
	{
		m_countCollision = 0;
		timer.x = 0;
		flagPosition.x = position.x;
	}
	else if (m_counttimer >= delta_time * 60* 5 && m_countCollision == 2)
	{
		m_countCollision = 1;
		timer.x = 0;
		flagPosition.x = position.x;
	}

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
		if (m_countCollision == 0)
		{
			if (direction == 1)
			{
				UpdateAnimation(delta_time, 8, 9, direction, 0.2);
			}
			else UpdateAnimation(delta_time, 2, 3, direction, 0.2);
		}
		else if(m_countCollision == 1)
		{
			if (direction == 1)
			{
				UpdateAnimation(delta_time, 4, 4, direction, 0.2);
			}
			else UpdateAnimation(delta_time, 10, 10, direction, 0.2);
		}
	}

	if(m_countCollision >= 2)
	{
		UpdateAnimation(delta_time, 4, 5, direction, 0.2);
	}

	if (m_countCollision != 1)
	{
		//update position
		timer.x += delta_time;
		this->position.x = flagPosition.x + this->velocity.x*timer.x;
	}

	isCollision = false;
}

void CTurtle::Render()
{
	if(!isDead)
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}