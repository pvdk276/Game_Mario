#include "Enemy.h"
#include "BinaryTree.h"

CEnemy::CEnemy(int id, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = ENEMY;
	this->width = 50;
	this->height = 50;

	this->velocity = D3DXVECTOR2(-5.0f, 0.0f);
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update(float delta_time)
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
				break;
			}
		}
	}
	
	//update animation
	UpdateAnimation(delta_time, 0, 1, direction);

	//update position
	this->position.x += this->velocity.x*delta_time;
}

void CEnemy::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
