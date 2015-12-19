#include "CoinBrick.h"

CCoinBrick::CCoinBrick(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2) : CDynamicObject(id, position, sprite1)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
	this->isDead = false;
	this->isCollision = false;
	this->direct = 1;
	this->pos = position.y;
	this->count = 0;
	this->numberCoin = rand() % 10 + 1;
	this->sprite2 = sprite2;
	bonus = new CBonus(id, COIN, position, sprite2);
}

CCoinBrick::~CCoinBrick()
{
}

void CCoinBrick::Update(float delta_time)
 {
	 if (this->isCollision)
	 {
		 position.y += direct;
		 if (position.y > pos + 5)
			 direct = -1;
		 if (position.y == pos)
		 {
			 direct = 0;
		 }
		 //coin	
		 if (count <= numberCoin)
		 {
			 bonus->Update(delta_time);
			 if (bonus->isDead)
			 {
				 bonus = new CBonus(id, COIN, position, sprite2);
				 count++;
				 direct = 1;
				 this->isCollision = false;
			 }
		 }
		 else //Khi đủ số coin thì object chết
		 {
			 this->isDead = true;
			 direct = 1;
			 this->isCollision = false;
		 }		
	}

	if (this->isDead)
		UpdateAnimation(delta_time, 1, 1, direction);
	else
		UpdateAnimation(delta_time, 0, 0, direction);
}

void CCoinBrick::Render()
{
	if (!bonus->isDead) bonus->Render();
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
