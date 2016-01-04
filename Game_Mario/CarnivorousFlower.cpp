#include "CarnivorousFlower.h"

CCarnivorousFlower::CCarnivorousFlower(int id, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	this->type = CARNIVOROUS_FLOWER;
	this->width = 50;
	this->height = 50;
	velocity = D3DXVECTOR2(0.0f, 50.0f);
	accel = D3DXVECTOR2(0.0f, 0.0f);
	m_counter = 0.0f;
}

CCarnivorousFlower::~CCarnivorousFlower()
{
}

void CCarnivorousFlower::Update(float delta_time)
{

	//Va chạm với mario
	float normalx, normaly;
	float distanceX, distanceY;
	if (CCollision::getInstance()->CheckCollision(
		CMario::getInstance()->GetBox(),
		this->GetBox(),
		normalx, normaly, distanceX, distanceY, delta_time) < 1 && !this->isDead)
	{
		if (CMario::getInstance()->sprite == CMario::getInstance()->smallMario)
			CMario::getInstance()->Deading();
		else
		{
			CMario::getInstance()->changeMario(CMario::getInstance()->smallMario, 0);
			SoundManagement::GetInstance()->Get(SMALLER_SOUND)->Play();
		}
			
	}

	//Di chuyển
	if (this->position.y >= rootPosition.y + 100)
	{
		velocity.y = - abs(velocity.y);
		timer.y = 0.0f;
		flagPosition.y = position.y;
		m_counter += delta_time;
	}
	else
		m_counter = 0.0f;

	if (this->position.y <= rootPosition.y)
	{
		velocity.y = abs(velocity.y);
		timer.y = 0.0f;
		flagPosition.y = position.y;
	}

	if (m_counter >= delta_time*GAME_FPS )
	{
		timer.y += delta_time;
		this->position.y = flagPosition.y + this->velocity.y*timer.y;
	}
	if (m_counter == 0.0f)
	{
		timer.y += delta_time;
		this->position.y = flagPosition.y + this->velocity.y*timer.y;
	}
	//update animation

	UpdateAnimation(delta_time, 0, 2, direction, 0.2f);
}

 

void CCarnivorousFlower::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
