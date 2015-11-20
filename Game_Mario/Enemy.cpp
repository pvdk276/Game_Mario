#include "Enemy.h"

CEnemy::CEnemy(int id, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = ENEMY;
	this->width = 50;
	this->height = 50;
	this->direction = 1;
	isDead = false;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update(float delta_time)
{
	//update position

	//update animation
	UpdateAnimation(delta_time, 0, 1, direction);
}

void CEnemy::Render()
{
	if (curTime == 0)
	{
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	}
}
