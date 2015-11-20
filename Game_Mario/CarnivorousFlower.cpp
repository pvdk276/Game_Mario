#include "CarnivorousFlower.h"

CCarnivorousFlower::CCarnivorousFlower(int id, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = CARNIVOROUS_FLOWER;
	this->width = 50;
	this->height = 50;
}

CCarnivorousFlower::~CCarnivorousFlower()
{
}

void CCarnivorousFlower::Update(float delta_time)
{
	//update position	

	//update animation
	UpdateAnimation(delta_time, 0, 2, direction);
}

void CCarnivorousFlower::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
