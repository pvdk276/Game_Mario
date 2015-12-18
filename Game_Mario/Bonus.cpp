#include "Bonus.h"
#include "BinaryTree.h"

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
	//Check collision
	m_collisionX = false;
	m_collisionY = false;
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		if (//CBinaryTree::getInstance()->listCurrentObject->at(i)->type == BRICK ||
			//CBinaryTree::getInstance()->listCurrentObject->at(i)->type == COIN_BRICK ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == LEFT_LAND ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == CENTER_LAND ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == RIGHT_LAND
			)
		{
			float normalx, normaly;
			float value = CCollision::getInstance()->CheckCollision(
				this->GetBox(),
				CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox(),
				normalx, normaly, delta_time);
			if (value < 1) //a collision occur
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					m_collisionX = true;
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					m_collisionY = true;
					if (position.y > CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox().y + 
						CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox().h / 2 + height / 2)
						position.y = CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox().y + 
						CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox().h / 2 + height / 2;
				}
			}
		}
	}

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

	if (isOutOfBlock)
	{
		if (velocity.y > 0) velocity.y = -velocity.y;
		if (!m_collisionX)
			position.x += velocity.x * delta_time;
		if (!m_collisionY)
			position.y += velocity.y * delta_time;
	}
}

void CBonus::Render()
{
	if(type == RED_MUSHROOM) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
	else if(type == GREEN_MUSHROOM) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
	else sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
