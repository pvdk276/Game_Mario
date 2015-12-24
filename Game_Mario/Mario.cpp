#include "Mario.h"
#include "Camera.h"
#include "GameKeyboard.h"
#include "BinaryTree.h"
#include "GameGraphic.h"


CMario::CMario() : CLivingObject(0, D3DXVECTOR2(75.0f, 600.0f), NULL)
{
	this->Init();
}

CMario::~CMario()
{
}

void CMario::Init()
{
	m_action = stand;
	this->isDead = false;
	magicCounter = 0;
	doingChanging = false;

	this->smallMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/SmallMario.png", 50, 50, 10, 5, NULL);
	this->bigMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/BigMario.png", 50, 100, 10, 5, NULL);
	changeMario(bigMario, 0);
	velocity = D3DXVECTOR2(0.0f, preVelocity.y);
	accel = D3DXVECTOR2(0, flagAccel.y);
	prePosition = D3DXVECTOR2(0.0f, 0.0f);
	timer = D3DXVECTOR2(0.0f,0.0f);
	posMasat = D3DXVECTOR2(0.001f, 0.0f);
	deltaPosition = 0.0f;
	masat = posMasat.x;
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
	delta_time = 0.016667;

#pragma region Xử lý va chạm của Mario

	m_collisionX = false;
	m_collisionY = false;

	for (int i = 0; i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		mario = CMario::getInstance()->GetBox();
		m_pObject = CBinaryTree::getInstance()->listCurrentObject->at(i);
		float normalx = 0.0f, normaly = 0.0f;
		value = 1;
		value = CCollision::getInstance()->CheckCollision(
			mario, m_pObject->GetBox(), normalx, normaly, timer, delta_time);
		if(value < 1)
			value = CCollision::getInstance()->CheckCollision(
				mario, m_pObject->GetBox(), normalx, normaly, timer, delta_time);
		if(m_pObject->type == CENTER_LAND && ((m_pObject->GetBox().x < mario.x + 50) && (m_pObject->GetBox().x > mario.x - 50)) && value >= 1)
			CCollision::getInstance()->CheckCollision(
				mario, m_pObject->GetBox(), normalx, normaly, timer, delta_time);
		//float v = value; 
		if (value < 1) //a collision occur
		{
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
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
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

			//Va chạm với Enemy
			case ENEMY:
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					//Mario chết
					if (this->sprite == smallMario)
					{
						if (!doingChanging)
							this->isDead = true;
					}
					else //Nếu là mario lớn
					{
						if (!doingChanging)
							currentSprite = this->sprite;
						changeMario(smallMario, 2);
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
			case RED_MUSHROOM:
			{
				if (this->sprite == smallMario)
				{
					if (!doingChanging)
						currentSprite = this->sprite;
					changeMario(bigMario, 2);
					m_pObject->isDead = true;
				}
			}
			break;
			//Va chạm với gạch
			case BRICK:
			{
				if ((normalx == 0.0f) && (normaly == -1.0f))
				{
					if (this->sprite == bigMario)
						m_pObject->isDead = true;
					else if (this->sprite == smallMario) // Khi mario nho va cham
					{
						m_pObject->isCollision = true;
						velocity.y = -velocity.y;
					}
					break;
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
					velocity.y = -velocity.y;
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
					{
						m_pObject->isCollision = true;
						m_pObject->isDead = true;
					}
					velocity.y = -velocity.y;
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
	if (m_collisionY == false)
	{
		m_collisionY = false;
	}
#pragma region Di chuyển của Mario

	//update state
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		if (m_action != jump && m_action != drop)
		{
			m_action = down;
			velocity.x = 0;
			accel.x = 0;
			timer = D3DXVECTOR2(0.0f,0.0f);
		}
	}
	if (m_action != down && m_action != drop) //Đang di chuyển
	{
		if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		{
			direction = 1;

			if (m_collisionX == true && direction == -1)
			{
				if (position.x < 50)
					position.x = 50;
				velocity.x = 0;
			}
			
			if (deltaPosition < 0)
			{
				velocity.x = accel.x*timer.x + preVelocity.x;
				flagPosition.x = position.x;
				accel.x = -1.0f * direction * (flagAccel.x);
				isSlowing = true;
			}
				
			else
			{
				velocity.x = preVelocity.x;
				accel.x = flagAccel.x;
			}

			if (m_action != jump) m_action = run;
		}
		else if (CGameKeyboard::getInstance()->IsKeyDown(DIK_LEFT))
		{
			direction = -1;

			if (m_collisionX == true && direction == 1)
			{
				if (position.x < 50)
					position.x = 50;
				velocity.x = 0;
			}

			if (deltaPosition > 0)
			{
				velocity.x = accel.x*timer.x + preVelocity.x;
				flagPosition.x = position.x;
				accel.x = -1.0f * direction * (flagAccel.x);
				isSlowing = true;
			}	
			else
			{
				
				velocity.x = preVelocity.x;
				accel.x = - flagAccel.x;
			}

			if (m_action != jump) m_action = run;
		}
		else // KHông nhấn nút (trượt)
		{
			if (m_action == run)
			{
				if (isSlowing == false)
				{
					velocity.x = accel.x*timer.x + preVelocity.x;
					preVelocity.x = velocity.x;
					flagPosition.x = position.x;
					accel.x = -1.0f * direction * (flagAccel.x);
					timer.x = 0.0f;
					isSlowing = true;
				}	
			}

			if (m_action != jump && m_action != drop) m_action = stand;
			
			
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
				//velocity.y = 0;
				//velocity.y = maxVelocity
				accel.y = flagAccel.y;
				m_action = jump;
			}

		}
	}
	//Khi mario nhảy
	if (m_action == jump)
	{
		if (accel.y*timer.y + preVelocity.y >= preVelocity.y * 3)
			accel.y = -1.0f*accel.y;
	}

	//Nếu mario đang rơi xuống
	if (m_collisionY == false && m_action != jump)
	{
		m_action = drop;
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
	//Di chuyển ngang
	if (!m_collisionX)
	{
		timer.x += delta_time;

		preDeltaPosition = deltaPosition;
		deltaPosition = (flagPosition.x + velocity.x * timer.x + 1.0f / 2 * accel.x * timer.x * timer.x) - position.x;

		if (deltaPosition > preDeltaPosition)
		{
			deltaPosition += 0;
		}
		//Giới hạn tốc độ cho Mario
		/*if (abs(deltaPosition) > abs(flagAccel.x*delta_time * 100) && isSlowing == false)
		{
			deltaPosition += preDeltaPosition;
			timer.x -= delta_time;
		}	*/
		
		if ((isSlowing == true && deltaPosition < 0 && direction == 1) ||
			(isSlowing == true && deltaPosition > 0 && direction == -1) ||
			deltaPosition == 0) //mario đang dừng
		{
			velocity.x = 0.0f;
			preVelocity.x = velocity.x;
			flagPosition.x = position.x;
			accel.x = 0.0f;
			timer.x = 0.0f;
			deltaPosition = 0;
			isSlowing = false;
		}		
		else
		{
			position.x = flagPosition.x + velocity.x * timer.x + 1.0f / 2 * accel.x * timer.x * timer.x;
			//prePosition.x = position.x;
		}
	}
	else
	{
		isSlowing = false;
		velocity.x = 0.0f;
		accel.x = 0.0f;
		timer.x = 0.0f;
		flagPosition.x = position.x;
		deltaPosition = 0;
	}

	//Di chuyển dọc
	if (!m_collisionY)
	{
		timer.y += delta_time;
		position.y = flagPosition.y + velocity.y * timer.y + 1.0f / 2 * accel.y * timer.y * timer.y;
	}
	else
	{
		flagPosition.y = position.y;
		timer.y = 0.0f;
	}

}

void CMario::UpdateAnimation(float delta_time)
{
	if (m_action == stand)
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 0, 0, direction, 0.2f);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 5, 5, direction, 0.2f);
		}
	}
	else if (m_action == run)
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 0, 1, direction, 0.2f);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 5, 6, direction, 0.2f);
		}
	}
	else if (m_action == jump)
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 2, 2, direction, 0.2f);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 7, 7, direction, 0.2f);
		}
	}
	else if (m_action == drop)
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 2, 2, direction, 0.2f);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 7, 7, direction, 0.2f);
		}
	}
	else //if(m_action == down)
	{
		if (direction == 1)
		{
			if (this->sprite == smallMario)
				CAnimation::UpdateAnimation(delta_time, 3, 3, direction, 0.2f);
			else
				CAnimation::UpdateAnimation(delta_time, 4, 4, direction, 0.2f);
		}
		else
		{
			if (this->sprite == smallMario)
				CAnimation::UpdateAnimation(delta_time, 8, 8, direction, 0.2f);
			else
				CAnimation::UpdateAnimation(delta_time, 9, 9, direction, 0.2f);
		}
	}
}
void CMario::Reset()
{
	position = D3DXVECTOR2(120.0f, 600.0f);
	this->Init();
}
void CMario::changeMario(CSprite* mario, float number)
{
	magicCounter += 0.5;
	doingChanging = true;
	if (magicCounter <= number)
	{
		if (this->sprite != this->currentSprite)
		{
			this->sprite = this->currentSprite;
			width = currentSprite->width;
			height = currentSprite->height;
		}
		else
		{
			this->sprite = mario;
			width = mario->width;
			height = mario->height;
		}
	}
	else //Thực hiện xong hiệu ứng
	{
		this->sprite = mario;
		width = mario->width;
		height = mario->height;

		magicCounter = 0;
		doingChanging = false;
	}
	if (mario == smallMario)
	{
		preVelocity = D3DXVECTOR2(500.0f, 500.0f);
		flagAccel = D3DXVECTOR2(100.0f, 100.0f);
	}
	else
	{
		/*preVelocity = D3DXVECTOR2(0.0f, 0.0f);
		maxAccel = D3DXVECTOR2(10.0f, -5.0f);*/
		preVelocity = D3DXVECTOR2(0.0f, -60.0f);
		flagAccel = D3DXVECTOR2(60.0f, -50.0f);
	}
}
