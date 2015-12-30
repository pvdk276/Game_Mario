#include "CoinBrick.h"
#include "SoundManagement.h"
#include "ScoreManagement.h"

CCoinBrick::CCoinBrick(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2) : CDynamicObject(id, position, sprite1)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
	this->isDead = false;
	this->isCollision = false;
	this->direct = 1;
	this->pos = position.y;
	//Random coin number
	srand((int)time(0));
	this->numberCoin = rand() % 10 + 1;
	this->count = 0;
	this->sprite2 = sprite2;
	bonus = new CBonus(id, COIN, position, sprite2);
	isBonus = false;
	isBrick = false;
}

CCoinBrick::~CCoinBrick()
{
}

void CCoinBrick::Update(float delta_time)
 {
	 if (isCollision && !isBonus && !isBrick)
	 {
		 isBonus = true;
		 isBrick = true;
	 }
	
	 if (this->isCollision && isBonus == true)
	 {
		 if (count <= numberCoin)
		 {
			 SoundManagement::GetInstance()->Get(GETCOIN_SOUND)->Play();
			 bonus->Update(delta_time);
			
			 if (bonus->isDead)
			 {
				 CScoreManagement::getInstance()->AddScore();
				 bonus = new CBonus(id, COIN, position, sprite2);
				 count++;
				 isBonus = false;
			 }
		 }
		 else //Khi đủ số coin thì object unlock
		 {
			 this->unLocked = true;
			 isBonus = false;
		 }
		 
	 }
	 
	 if (this->isCollision && isBrick == true)
	 {
		 position.y += direct;
		 if (position.y > pos + 5)
			 direct = -1;
		 if (position.y == pos)
		 {
			 direct = 1;
			 isBrick = false;
		 }
	 }

	 if (!isBonus && !isBrick)
		 isCollision = false;

	if (this->unLocked)
		UpdateAnimation(delta_time, 1, 1, direction, 0.2f);
	else
		UpdateAnimation(delta_time, 0, 0, direction);
}

void CCoinBrick::Render()
{
	if (!bonus->isDead) bonus->Render();
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
