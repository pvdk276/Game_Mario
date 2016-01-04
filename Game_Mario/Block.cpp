#include "Block.h"

CBlock::CBlock(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2) : CDynamicObject(id, position, sprite1)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
	this->isDead = false;
	this->isCollision = false;
	this->pos = position.y;
	this->direct = 1;
	if (type == COIN_BLOCK) 
	{
		bonus = new CBonus(id, COIN, position, sprite2);
		this->sprite2 = sprite2;
		//Random coin number
		srand((int)time(0));
		this->numberCoin = rand() % 10 + 1;
		this->count = 0;
		bonus->isStatic = false;
	}
	else if (type == FLOWER_BLOCK)
	{
		bonus = new CBonus(id, FLOWER, position, sprite2);
	}
	else if (type == RED_MUSHROOM_BLOCK) bonus = new CBonus(id, RED_MUSHROOM, position, sprite2);
	else if (type == GREEN_MUSHROOM_BLOCK) bonus = new CBonus(id, GREEN_MUSHROOM, position, sprite2);
	else bonus = new CBonus(id, STAR, position, sprite2);
	isBonus = false;
	isBlock = false;
}

CBlock::~CBlock()
{
}

void CBlock::Update(float delta_time)
{
	if (isCollision && !isBonus && !isBlock)
	{
		isBonus = true;
		isBlock = true;
		if (this->type != COIN_BLOCK)
			SoundManagement::GetInstance()->Get(BONUSAPPEAR_SOUND)->Play();
	}
	
	if (type == COIN_BLOCK)
	{
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
					bonus->isStatic = false;
					count++;
					isBonus = false;
				}
			}
			else //Khi đủ số coin thì object unlock
			{
				bonus->isDead = true;
				this->unLocked = true;
				isBonus = false;
			}

		}
	}
	if (this->isCollision && isBlock == true)
	{
		position.y += direct;
		if (position.y > pos + 5)
			direct = -1;
		if (position.y == pos)
		{
			direct = 1;
			isBlock = false;
		}
	}

	if (!isBonus && !isBlock)
		isCollision = false;

	if (this->unLocked)
	{
		bonus->Update(delta_time);
		UpdateAnimation(delta_time, 2, 2, direction, 0.2f);
	}
	else
	{
		UpdateAnimation(delta_time, 0, 1, direction);
	}
}

void CBlock::Render()
{
	if (!bonus->isDead) bonus->Render();
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}