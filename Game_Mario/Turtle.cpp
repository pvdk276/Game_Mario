#include "Turtle.h"
#include "BinaryTree.h"

CTurtle::CTurtle(int id, ObjectName type, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
	this->velocity = D3DXVECTOR2(-100.0f, 0.0f);
	m_countCollision = 0;
	beingShoot = false;
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
		float normalx, normaly;
		float distanceX, distanceY;
		float value = CCollision::getInstance()->CheckCollision(
			this->GetBox(),
			CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox(),
			normalx, normaly, distanceX, distanceY, delta_time);
		if (value < 1) //a collision occur
		{
			switch (CBinaryTree::getInstance()->listCurrentObject->at(i)->type)
			{
			case PIPE:
			case CARNIVOROUS_FLOWER_PIPE:
			case PIPE_UP:
			case PIPE_DOWN:
			case PIPE_DOWN_1:
			case PIPE_DOWN_2:
			case PIPE_UP_1:
			case PIPE_UP_2:
			case PIPE_LEFT:
			case PIPE_LEFT_1:
			case PIPE_LEFT_2:
			case STONE:
			{
				timer.x = 0.0f;
				this->velocity.x *= -1;
				direction *= -1;
				flagPosition.x = this->position.x;
			}
			break;
			default:
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

	//Bị bắn
	if (isShoot && !beingShoot)
	{
		//Chiều ngang
		if (this->position.x > CMario::getInstance()->position.x)
		{
			timer.x = 0.0f;
			flagPosition.x = position.x;
			velocity.x = abs(velocity.x) / 1.5;
		}
		else
		{
			timer.x = 0.0f;
			flagPosition.x = position.x;
			velocity.x = -abs(velocity.x) / 1.5;
		}

		//Chiều dọc
		timer.y = 0.0f;
		flagPosition.y = position.y;
		velocity.y = 500;
		accel.y = -1500;

		this->beingShoot = true;
	}

	if (isShoot)
	{
		if (position.y < 125)
		{
			this->isDead = true;
		}
		timer.y += delta_time;
		this->position.y = flagPosition.y + this->velocity.y*timer.y + 0.5f*this->accel.y * timer.y * timer.y;
	}

	//Animation
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