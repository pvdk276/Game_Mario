#include "Enemy.h"
#include "BinaryTree.h"

CEnemy::CEnemy(int id, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = ENEMY;
	this->width = 50;
	this->height = 50;
	this->isDead = false;
	this->isCollision = false;
	this->beingShoot = false;
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
				flagPosition.x = this->position.x;
			}
			break;
			default:
				break;
			}	
		}
	}
	
	//Bị bắn
	if (isShoot && !beingShoot)
	{
		//Chiều ngang
		if ( this->position.x > CMario::getInstance()->position.x)
		{
			timer.x = 0.0f;
			flagPosition.x = position.x;
			velocity.x = abs(velocity.x)/1.5;
		}
		else
		{
			timer.x = 0.0f;
			flagPosition.x = position.x;
			velocity.x = - abs(velocity.x)/1.5;
		}

		//Chiều dọc
		timer.y = 0.0f;
		flagPosition.y = position.y;
		velocity.y = 500;
		accel.y = -1500;

		this->beingShoot = true;
	}

	if(isShoot)
	{
		if (position.y < 125)
		{
			this->isDead = true;
		}
		timer.y += delta_time;
		this->position.y = flagPosition.y + this->velocity.y*timer.y + 0.5f*this->accel.y * timer.y * timer.y;
	}
	

	//Nếu có va chạm với mario
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
