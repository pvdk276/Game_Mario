#include "Mario.h"
#include "Camera.h"
#include "GameKeyboard.h"

CMario::CMario() : CLivingObject(0, D3DXVECTOR2(120.0f, 125.0f), NULL)
{
	velocity = D3DXVECTOR2(0.0f, 0.0f);
	accel = D3DXVECTOR2(0.0f, 0.0f);
	maxVelocity = D3DXVECTOR2(40.0f, 80.0f);
	maxAccel = D3DXVECTOR2(5.0f, 30.0f);

	m_action = stand;
	animationTime = TIME_ANIMATION;
}

CMario::~CMario()
{
}

void CMario::Init(CSprite * smallMario, CSprite * bigMario, CSprite * superMario)
{
	this->smallMario = smallMario;
	this->bigMario = bigMario;
	this->superMario = superMario;

	this->sprite = this->smallMario;
}

void CMario::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}

void CMario::Update(float delta_time)
{
	//update state
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		if (m_action != jump)
		{
			m_action = down;
			velocity = D3DXVECTOR2(0.0f, 0.0f);
			accel = D3DXVECTOR2(0.0f, 0.0f);
		}
	}

	if (m_action != down)
	{
		if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		{
			direction = 1;
			if (velocity.x < maxVelocity.x)
			{
				accel.x = maxAccel.x;
			}
			else //if (m_veloc.x >= m_maxVelocity.x)
			{
				accel.x = 0;
				velocity.x = maxVelocity.x;
			}

			if (m_action != jump) m_action = run;
		}
		else if (CGameKeyboard::getInstance()->IsKeyDown(DIK_LEFT))
		{
			direction = -1;
			if (velocity.x > direction * maxVelocity.x)
			{
				accel.x = direction * maxAccel.x;
			}
			else //(speedX <= direction*maxSpeedX)
			{
				velocity.x = maxVelocity.x * direction;
				accel.x = 0;
			}

			if (m_action != jump) m_action = run;
		}
		else
		{
			if (m_action != jump) m_action = stand;
			if (velocity.x != 0)
			{
				accel.x = -1.0f * direction * maxAccel.x;
			}

			if (direction * velocity.x <= 0)
			{
				velocity.x = 0;
				accel.x = 0;
				
			}
		}
	}
	else
	{
		if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		{
			direction = 1;
		}
		else if (CGameKeyboard::getInstance()->IsKeyDown(DIK_LEFT))
		{
			direction = -1;
		}
		
		if (!CGameKeyboard::getInstance()->IsKeyDown(DIK_DOWN))
		{
			m_action = stand;
		}
	}

	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_SPACE))
	{
		if (m_action != down && m_action != jump)
		{			
			accel.y = maxAccel.y;
			m_action = jump;
		}
	}

	UpdatePosition(delta_time);

	if (m_action == jump)
	{
		if (velocity.y >= maxVelocity.y)
		{
			accel.y = -1.0f * maxAccel.y;
		}

		if (position.y < 125)
		{
			if (velocity.x != 0) m_action = run;
			else m_action = stand;
			velocity.y = 0.0f;
			accel.y = 0.0f;
			position.y = 125;
		}
	}

	UpdateAnimation(delta_time);
}

void CMario::UpdatePosition(float delta_time)
{	
	position.x += velocity.x * delta_time + 1.0f / 2 * accel.x * delta_time * delta_time;
	velocity.x += accel.x * delta_time;
		
	position.y += velocity.y * delta_time + 1.0f / 2 * accel.y * delta_time * delta_time;
	velocity.y += accel.y * delta_time;
}

void CMario::UpdateAnimation(float delta_time)
{
	if (m_action == stand)
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 0, 0, direction);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 5, 5, direction);
		}
	}
	else if (m_action == run)
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 0, 1, direction);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 5, 6, direction);
		}
	}
	else if (m_action == jump)
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 2, 2, direction);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 7, 7, direction);
		}
	}
	else //if(m_action == down)
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 3, 3, direction);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 8, 8, direction);
		}
	}
}