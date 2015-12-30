#include "Mario.h"
#include "Camera.h"
#include "GameKeyboard.h"
#include "BinaryTree.h"
#include "SoundManagement.h"
#include "GameGraphic.h"
#include <sstream>


CMario::CMario() : CLivingObject(0, D3DXVECTOR2(120.0f, 600.0f), NULL)
{
	this->Init();
}

CMario::~CMario()
{
}

void CMario::Init()
{
	velocity = D3DXVECTOR2(0.0f, -20.0f);
	accel = D3DXVECTOR2(0.0f, 0.0f);
	maxVelocity = D3DXVECTOR2(40.0f, 80.0f);
	maxAccel = D3DXVECTOR2(5.0f, 30.0f);
	m_action = stand;
	this->isDead = false;

	this->smallMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/SmallMario.png", 50, 50, 10, 5, NULL);
	this->bigMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/BigMario.png", 50, 100, 10, 5, NULL);
	changeMario(bigMario);
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
#pragma region Xử lý va chạm của Mario
	m_collisionX = false;
	m_collisionY = false;
	for (int i = 0; i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		mario = CMario::getInstance()->GetBox();
		m_pObject = CBinaryTree::getInstance()->listCurrentObject->at(i);
		float normalx, normaly;
		float value = CCollision::getInstance()->CheckCollision(
			mario, m_pObject->GetBox(), normalx, normaly, delta_time);
		if (value < 1) //a collision occur
		{
			//objectName = CBinaryTree::getInstance()->listCurrentObject->at(i)->type;
			switch (m_pObject->type)
			{
			//Va chạm với ống
			case PIPE:
			case STONE:
			case CARNIVOROUS_FLOWER_PIPE:
			case PIPE_UP:
			case PIPE_DOWN:
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					m_collisionX = true;
					SoundManagement::GetInstance()->Get(ENEMYDIE_SOUND)->Play();
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					m_collisionY = true;
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
						accel.y = - 2;
					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
			}
			break;

			//Va chạm với Enemy
			case ENEMY:
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					//Mario chết
					if (this->sprite == smallMario)
						this->isDead = true;
					else //Nếu là mario lớn
					{
						changeMario(smallMario);
					}
						
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					//if (this->sprite == bigMario)
					//	this->sprite = smallMario;
					//else
					//	this->sprite = bigMario;
					//Enemy chết
					CBinaryTree::getInstance()->listCurrentObject->at(i)->isDead = true;
				}
			}
			break;
			
			//Va chạm với gạch
			case BRICK:
			{
				/*if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)*/
				if(normalx == 0.0f && normaly == -1.0f)
				{
					SoundManagement::GetInstance()->Get(EXTRALIFE_SOUND)->Play();
					if (this->sprite == bigMario)
						CBinaryTree::getInstance()->listCurrentObject->at(i)->isDead = true;
					else if (this->sprite == smallMario) // Khi mario nho va cham
						CBinaryTree::getInstance()->listCurrentObject->at(i)->isCollision = true;
				}
				if (normalx == 0.0f && normaly == 1.0f)
				{
					m_collisionY = true;	
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
						accel.y = -2;

					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
				
			}
			break;
			case COIN_BRICK:
			{
				if (normalx == 0.0f && normaly == -1.0f)
				{
					m_pObject->isCollision = true;
				}
				if (normalx == 0.0f && normaly == 1.0f)
				{
					m_collisionY = true;
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
						accel.y = -2;

					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
			}
			break;
			//Va chạm với block
			case COIN_BLOCK:
			case RED_MUSHROOM_BLOCK:
			case FLOWER_BLOCK:
			case GREEN_MUSHROOM_BLOCK:
			case STAR_BLOCK:
			{
				if (normalx == 0.0f && normaly == -1.0f)
				{
					if (m_pObject->type == COIN_BLOCK)
						m_pObject->isCollision = true;
					else
						m_pObject->isDead = true;
				}
				if (normalx == 0.0f && normaly == 1.0f)
				{
					m_collisionY = true;
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
						accel.y = -2;

					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
			}
			break;
			//Va chạm với đất
			case LEFT_LAND:
			case RIGHT_LAND:
			case CENTER_LAND:
			{
				/*if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					m_collisionX = true;
				}*/
				if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					m_collisionY = true;
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
						accel.y = -2;

					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
			}
			break;

			default:
				break;
			}
		}
	}

	//Va chạm với tường
	if (position.x < 50.0f)
	{
		m_collisionX = true;
	}
#pragma endregion
	

#pragma region Di chuyển của Mario
	//update state
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		if (m_action != jump && m_action != drop)
		{
			m_action = down;
			velocity.x = 0;
			accel.x = 0;
		}
	}
	if (m_action != down && m_action != drop) //Đang di chuyển
	{
		if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		{
			if (m_collisionX == true && direction == -1)
			{
				if (position.x < 50)
					position.x = 50;
				velocity.x = 0;
			}
				
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
			{
				if (position.x < 50)
					position.x = 50;
				velocity.x = 0;
			}
				
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
			if (m_action != jump && m_action != drop) m_action = stand;
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

	//Sự kiện nhấn phím khi nhảy
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_SPACE))
	{
		if (m_action != down && m_action != jump && m_action != drop)
		{
			if (m_collisionY)
			{
				m_collisionY = false;
				velocity.y = 0;
				accel.y = maxAccel.y;
				m_action = jump;
			}
			
		}
	}
	//Khi mario nhảy
	if (m_action == jump)
	{
		if (velocity.y >= maxVelocity.y)
		{
			accel.y = -1.0f * maxAccel.y;
		}
	}
	//Nếu mario đang rơi xuống
	if (m_collisionY == false && m_action != jump)
	{
		m_action = drop;
		accel.y = -2;
		if (direction == 1)
			velocity.x = 2;
		else
			velocity.x = -2;
	}
	//Mario dead
	if (position.y <= 0.0f)
	{
		isDead = true;
	}
#pragma endregion

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
	else if (m_action == drop)
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
			if(this->sprite == smallMario)
				CAnimation::UpdateAnimation(delta_time, 3, 3, direction);
			else
				CAnimation::UpdateAnimation(delta_time, 4, 4, direction);
		}
		else
		{
			if(this->sprite == smallMario)
				CAnimation::UpdateAnimation(delta_time, 8, 8, direction);
			else
				CAnimation::UpdateAnimation(delta_time, 9, 9, direction);
		}
	}
}
void CMario::Reset()
{
	position = D3DXVECTOR2(120.0f, 600.0f);
	this->Init();
}
void CMario::changeMario(CSprite* mario)
{
	this->sprite = mario;
	width = mario->width;
	height = mario->height;
	if (mario == smallMario)
	{
		maxVelocity = D3DXVECTOR2(35.0f, 60.0f);
		maxAccel = D3DXVECTOR2(4.0f, 25.0f);
	}
	else
	{
		maxVelocity = D3DXVECTOR2(40.0f, 80.0f);
		maxAccel = D3DXVECTOR2(5.0f, 30.0f);
	}
		
}