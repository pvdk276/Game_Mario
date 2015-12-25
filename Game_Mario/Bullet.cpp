#include "Bullet.h"

CBullet::CBullet(int direction, D3DXVECTOR2 position, CSprite * sprite): CLivingObject(id, position, sprite)
{
	this->position = position;
	width = 30.0f;
	height = 30.0f;
	this->sprite = sprite;
	flagPosition = this->position;
	velocity.x = 500;
	this->direction = direction;
}

CBullet::~CBullet()
{
}

void CBullet::Update(float delta_time)
{
	if (abs(position.x - flagPosition.x) > 400)
		this->isDead = true;

	timer.x += delta_time;
	position.x = flagPosition.x + direction * velocity.x * timer.x + 1.0f / 2 * direction * accel.x * timer.x * timer.x;

	UpdateAnimation(delta_time, 0, 3, direction, 0.05f);
}

void CBullet::Render()
{
	if (!this->isDead)
	{
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	}
}
