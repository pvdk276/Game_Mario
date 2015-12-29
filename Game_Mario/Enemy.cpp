#include "Enemy.h"
#include "BinaryTree.h"

CEnemy::CEnemy(int id, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = ENEMY;
	this->width = 50;
	this->height = 50;
	this->isDead = false;
	this->isCollision = false;
	this->velocity = D3DXVECTOR2(-100.0f, 0.0f);
	deadTimer = 0.0f;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update(float delta_time)
{
	//Check collision
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == PIPE || 
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == STONE ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == CARNIVOROUS_FLOWER_PIPE)
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
				flagPosition.x = this->position.x;
				break;
			}
		}
	}
	
	if (!this->isCollision)
	{
		//update animation
		UpdateAnimation(delta_time, 0, 1, direction, 0.2f);
		//update position
		timer.x += delta_time;
		this->position.x = flagPosition.x + this->velocity.x*timer.x;
	}
	else
	{
		UpdateAnimation(delta_time, 3, 3, direction);
		deadTimer += delta_time;
		if (deadTimer >= delta_time * GAME_FPS)	//sau 1s thì chết
		{
			this->isDead = true;
		}	
	}
		
}

void CEnemy::Render()
{
	if(!isDead)
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
