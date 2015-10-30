#include "Mario.h"
#include "Camera.h"
#include "GameKeyboard.h"



CMario::CMario()
{
	position = D3DXVECTOR2(20.0f, 125.0f);
	velocity = D3DXVECTOR2(0.0f, 0.0f);
	accel = D3DXVECTOR2(0.0f, 0.0f);
	maxVelocity = D3DXVECTOR2(40.0f, 80.0f);
	maxAccel = D3DXVECTOR2(5.0f, 30.0f);

	direct = 1;

	currentSprite = smallMario;

	m_action = stand;
}

CMario::~CMario()
{

}

void CMario::Render()
{
	currentSprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
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
			direct = 1;
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
			direct = -1;
			if (velocity.x > direct * maxVelocity.x)
			{
				accel.x = direct * maxAccel.x;
			}
			else //(speedX <= direct*maxSpeedX)
			{
				velocity.x = maxVelocity.x * direct;
				accel.x = 0;
			}

			if (m_action != jump) m_action = run;
		}
		else
		{
			if (m_action != jump) m_action = stand;
			if (velocity.x != 0)
			{
				accel.x = -1.0f * direct * maxAccel.x;
			}

			if (direct * velocity.x <= 0)
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
			direct = 1;
		}
		else if (CGameKeyboard::getInstance()->IsKeyDown(DIK_LEFT))
		{
			direct = -1;
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

	UpdatePosition(delta_time);

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
		if (direct == 1)
		{
			currentSprite->SetCurrentIndex(0);
			currentSprite->UpdateSprite();
		}
		else
		{
			currentSprite->SetCurrentIndex(5);
			currentSprite->UpdateSprite();
		}
	}
	else if (m_action == run)
	{
		if (direct == 1)
		{
			currentSprite->SetTimeAnimation(TIME_ANIMATION);
			currentSprite->UpdateSprite(delta_time, 0, 1, 1);
		}
		else
		{
			currentSprite->SetTimeAnimation(TIME_ANIMATION);
			currentSprite->UpdateSprite(delta_time, 5, 6, -1);
		}
	}
	else if (m_action == jump)
	{
		if (direct == 1)
		{
			currentSprite->SetCurrentIndex(2);
			currentSprite->UpdateSprite();
		}
		else
		{
			currentSprite->SetCurrentIndex(7);
			currentSprite->UpdateSprite();
		}
	}
	else //if(m_action == down)
	{
		if (direct == 1)
		{
			currentSprite->SetCurrentIndex(3);
			currentSprite->UpdateSprite();
		}
		else
		{
			currentSprite->SetCurrentIndex(8);
			currentSprite->UpdateSprite();
		}
	}
}