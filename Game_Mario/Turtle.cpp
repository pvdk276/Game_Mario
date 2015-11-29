#include "Turtle.h"
#include "BinaryTree.h"

CTurtle::CTurtle(int id, ObjectName type, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
	this->velocity = D3DXVECTOR2(-5.0f, 0.0f);
}

CTurtle::~CTurtle()
{
}

void CTurtle::Update(float delta_time)
{
	

	//Check collision
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == PIPE || CBinaryTree::getInstance()->listCurrentObject->at(i)->type == STONE)
		{
			float normalx, normaly;
			float value = CCollision::getInstance()->AABBCheck(
				this->GetBox(),
				CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox());
			if (value == true) //a collision occur
			{
				this->velocity.x *= -1;
				direction *= -1;
				break;
			}
		}
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
		if (direction == 1)
		{
			UpdateAnimation(delta_time, 8, 9, direction);
		}
		else UpdateAnimation(delta_time, 2, 3, direction);
	}
	else
	{
		UpdateAnimation(delta_time, 4, 5, direction);
	}

	//update position
	this->position.x += this->velocity.x*delta_time;
}

void CTurtle::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}