#include "SecretBlock.h"

CSecretBlock::CSecretBlock(int id, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2, CSprite* sprite3, CSprite* sprite4, CSprite* sprite5) : CDynamicObject(id, position, sprite1)
{
	this->width = 50;
	this->height = 50;
	this->type = type;
	

	if (type == COIN_SECRET_BLOCK)
	{
		//D3DXVECTOR2 pos(position.x, 125);
		//flower = new CCarnivorousFlower(-1, pos, sprite2);
		coin = new CCoin(-1, position, sprite2);
	}
	else if (type == NORMAL_MUSHROOM_SECRET_BLOCK)
	{
		mushroom = new CMushroom(-1, position, sprite3);
	}
	else if(type== LIFE_MUSHROOM_SECRET_BLOCK)
	{
		mushroom = new CMushroom(-1, position, sprite4);
	}
	else if(type== FLOWER_SECRET_BLOCK)
	{
		flower = new CFlower(-1, position, sprite5);
	}
}

CSecretBlock::~CSecretBlock()
{
}

void CSecretBlock::Update(float delta_time)
{
	//UpdateAnimation(delta_time, 0, 1, direction);
	if (type == COIN_SECRET_BLOCK) coin->Update(delta_time);
	if (type == NORMAL_MUSHROOM_SECRET_BLOCK || type == LIFE_MUSHROOM_SECRET_BLOCK) mushroom->Update(delta_time);
	if (type == FLOWER_SECRET_BLOCK) flower->Update(delta_time);
}

void CSecretBlock::Render()
{
	if (type == COIN_SECRET_BLOCK) coin->Render();
	if (type == NORMAL_MUSHROOM_SECRET_BLOCK || type == LIFE_MUSHROOM_SECRET_BLOCK) mushroom->Render();
	if (type == FLOWER_SECRET_BLOCK) flower->Render();
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}