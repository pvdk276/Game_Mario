#include "Mario.h"
#include "Camera.h"
#include "GameKeyboard.h"
#include "BinaryTree.h"
#include "GameGraphic.h"
#include <sstream>


CMario::CMario() : CLivingObject(0, D3DXVECTOR2(120.0f, 225.0f), NULL)
{
	velocity = D3DXVECTOR2(0.0f, -10.0f);
	accel = D3DXVECTOR2(0.0f, 0.0f);
	maxVelocity = D3DXVECTOR2(40.0f, 80.0f);
	maxAccel = D3DXVECTOR2(5.0f, 30.0f);

	m_action = stand;
	animationTime = TIME_ANIMATION;

	width = 50;
	height = 50;

	this->isDead = false;
}

CMario::~CMario()
{
}

void CMario::Init()
{
	this->smallMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/SmallMario.png", 50, 50, 10, 5, NULL);
	this->bigMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/BigMario.png", 50, 100, 10, 5, NULL);

	this->sprite = this->bigMario;
}

void CMario::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}

/// <summary>
/// Updates the specified delta_time.
/// </summary>
/// <param name="delta_time">The delta_time.</param>
void CMario::Update(float delta_time)
{
	m_collisionX = false;
	m_collisionY = false;
	m_inAir = false;
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		// va chạm với ống
		if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == PIPE)
		{
			float normalx, normaly;
			float value = CCollision::getInstance()->CheckCollision(
				CMario::getInstance()->GetBox(),
				CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox(),
				normalx, normaly, delta_time);
			if (value < 1) //a collision occur
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					m_collisionX = true;
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					m_collisionY = true;
					if (m_action == jump)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
						velocity.y = -10.0f;
						accel.y = 0.0f;
						/*if (position.y > 125)
						position.y = 125;*/
					}
				}
				break;
			}
		}
	}
	//va chạm vs enemy
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == ENEMY)
		{
			float normalx, normaly;
			float value = CCollision::getInstance()->CheckCollision(
				CMario::getInstance()->GetBox(),
				CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox(),
				normalx, normaly, delta_time);
			if (value < 1) //a collision occur
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					//Mario chết
					this->isDead = true;
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					//Enemy chết
					CBinaryTree::getInstance()->listCurrentObject->at(i)->isDead = true;
				}
				break;
			}
		}
	}
	//va cham gach
	for (int i = 0; i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == BRICK)
		{
			float normalx, normaly;
			float value = CCollision::getInstance()->CheckCollision(
				CMario::getInstance()->GetBox(),
				CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox(),
				normalx, normaly, delta_time);
			if (value < 1) //a collision occur
			{
				if(this->sprite == bigMario)
					CBinaryTree::getInstance()->listCurrentObject->at(i)->isDead = true;
				else if (this->sprite == smallMario) // Khi mario nho va cham
					CBinaryTree::getInstance()->listCurrentObject->at(i)->isCollision = true;
				break;
			}
		}
	}
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
	if (m_action != down) //Đang di chuyển
	{
		if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		{
			if (m_collisionX == true && direction == -1)
				velocity.x = 0;
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
			if (m_collisionX == true && direction == 1)
				velocity.x = 0;
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
		else // KHông nhấn nút (trượt)
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
	else //m_action = down
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
	
	//Va chạm với đất
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == LEFT_LAND ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == RIGHT_LAND ||
			CBinaryTree::getInstance()->listCurrentObject->at(i)->type == CENTER_LAND)
		{
			CBox mario = CMario::getInstance()->GetBox();
			CBox land = CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox();
			float normalx, normaly;
			float value = CCollision::getInstance()->CheckCollision(
				mario,
				land,
				normalx, normaly, delta_time);
			if (value < 1) //a collision occur
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					m_collisionX = true;
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					this->m_inAir = false;
					m_collisionY = true;
					if (m_action == jump)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
						velocity.y = -10.0f;
						accel.y = 0.0f;
						
					}
					if (position.y > 125)
						position.y = 125;
				}
				break;
			}
			else
				this->m_inAir = true;
		}
	}
	//Sự kiện nhấn phím khi nhảy
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_SPACE))
	{
		if (m_action != down && m_action != jump)
		{
			if (!this->m_inAir)
			{
				m_collisionY = false;
				velocity.y = 0;
				accel.y = maxAccel.y;
				m_action = jump;
			}
			
		}
		//velocityY = velocity.y;
	}
	//Khi mario nhảy
	if (m_action == jump)
	{
		if (velocity.y >= maxVelocity.y)
		{
			accel.y = -1.0f * maxAccel.y;
		}

		//nếu đang đứng trên pipe


		/*if (position.y < 125)
		{
		if (velocity.x != 0) m_action = run;
		else m_action = stand;
		velocity.y = 0.0f;
		accel.y = 0.0f;
		position.y = 125;
		}*/
	}
	//Mario dead
	if (position.y <= 0.0f)
	{
		isDead = true;
	}
		

	UpdatePosition(delta_time);
	UpdateAnimation(delta_time);
}
void CMario::UpdatePosition(float delta_time)
{	
	if (!m_collisionX)
	{
		position.x += velocity.x * delta_time + 1.0f / 2 * accel.x * delta_time * delta_time;
		velocity.x += accel.x * delta_time;
	}
		

	if (!m_collisionY)
	{
		position.y += velocity.y * delta_time + 1.0f / 2 * accel.y * delta_time * delta_time;
		velocity.y += accel.y * delta_time;
	}
		
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