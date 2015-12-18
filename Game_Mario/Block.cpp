#include "Block.h"

CBlock::CBlock(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2) : CDynamicObject(id, position, sprite1)
{
	this->type = type;
	this->width = 50;
	this->height = 50;
	this->isDead = false;

	if (type == COIN_BLOCK) bonus = new CBonus(id, COIN, position, sprite2);
	else if (type == FLOWER_BLOCK) bonus = new CBonus(id, FLOWER, position, sprite2);
	else if (type == RED_MUSHROOM_BLOCK) bonus = new CBonus(id, RED_MUSHROOM, position, sprite2);
	else if (type == GREEN_MUSHROOM_BLOCK) bonus = new CBonus(id, GREEN_MUSHROOM, position, sprite2);
	else bonus = new CBonus(id, STAR, position, sprite2);
}

CBlock::~CBlock()
{
}

void CBlock::Update(float delta_time)
{
	UpdateAnimation(delta_time, 0, 1, direction);

	if (this->isDead)
	{
		bonus->Update(delta_time);
	}
}

void CBlock::Render()
{
	if (!bonus->isDead) bonus->Render();
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}

void CBlock::ActiveBonus()
{
	bonus->velocity = D3DXVECTOR2(5.0f, 10.0f);
}
