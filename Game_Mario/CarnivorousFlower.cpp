#include "CarnivorousFlower.h"

CCarnivorousFlower::CCarnivorousFlower(int id, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = CARNIVOROUS_FLOWER;
	this->width = 50;
	this->height = 50;
	this->_isDelayMove = false;
	velocity = D3DXVECTOR2(0.0f, 10.0f);
	accel = D3DXVECTOR2(0.0f, 0.0f);
	maxVelocity = D3DXVECTOR2(40.0f, 80.0f);
	maxAccel = D3DXVECTOR2(5.0f, 30.0f);
}

CCarnivorousFlower::~CCarnivorousFlower()
{
}

void CCarnivorousFlower::Update(float delta_time)
{
	
	position.y += velocity.y * delta_time;
	if (position.y >= 275) velocity.y = -5.0f;
	else if (position.y <= 175) velocity.y = 5.0f;

	//update animation
	UpdateAnimation(delta_time, 0, 2, direction);
}

 

void CCarnivorousFlower::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
