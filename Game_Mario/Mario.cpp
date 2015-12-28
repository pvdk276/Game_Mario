#include "Mario.h"
#include "Camera.h"
#include "GameKeyboard.h"
#include "BinaryTree.h"
#include "GameGraphic.h"


void CMario::droping()
{
	m_action = drop;
	velocity.y = -(abs(velocity.y) + abs(accel.y) * timer.y);
	timer.y = 0.0f;
	accel.y = - flagAccel.y;
	flagPosition.y = position.y;
}

void CMario::Jumping()
{
	m_collisionY = false;
	velocity.y = preVelocity.y;
	accel.y = - flagAccel.y;
	timer.y = 0.0f;
	flagPosition.y = position.y;
	m_action = jump;
}

void CMario::Standing()
{
	velocity.x = 0.0f;
	preVelocity.x = velocity.x;
	flagPosition.x = position.x;
	accel.x = 0.0f;
	timer.x = 0.0f;
	deltaPosition = 0;
	isSlowing = false;
}

// TODO Mario va chạm với enemy.
// TODO Sửa va chạm với pipe.
void CMario::CheckCollision(CBox mario, float delta_time)
{
	//Va chạm trong current object
	m_collisionX = false;
	m_collisionY = false;
	for (int i = 0; i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		m_pObject = CBinaryTree::getInstance()->listCurrentObject->at(i);
		float normalx = 0.0f, normaly = 0.0f;
		value = 1;
		value = CCollision::getInstance()->CheckCollision(
			mario, m_pObject->GetBox(), normalx, normaly, delta_time);
		//if (value < 1)
		//	value = CCollision::getInstance()->CheckCollision(
		//		mario, m_pObject->GetBox(), normalx, normaly, timer, delta_time);
		/*if(m_pObject->type == CENTER_LAND && ((m_pObject->GetBox().x < mario.x + 50) && (m_pObject->GetBox().x > mario.x - 50)) && value >= 1)*/
		/*if (m_pObject->type == PIPE && mario.x > 824.816 && value == 1)
			CCollision::getInstance()->CheckCollision(
				mario, m_pObject->GetBox(), normalx, normaly, timer, delta_time);*/
		//float v = value;

		if (value < 1 && !m_pObject->isDead) //a collision occur
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
					if (!doingChanging)
						currentSprite = this->sprite;
					changeMario(smallMario, 2);
					//position.x = position.x - 1;
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
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
					m_pObject->isCollision = true;
				}
			}
			break;
			case RED_MUSHROOM:
			{
				if (this->sprite == smallMario)
				{
					/*if (!doingChanging)
					currentSprite = this->sprite;*/
					changeMario(bigMario, 0);
					//m_pObject->bonus->isDead = true;
				}
			}
			break;
			//Va chạm với gạch
			case BRICK:
			{
				if (normalx == 0.0f && normaly == -1.0f)
				{
					if (this->sprite != smallMario)
					{
						m_pObject->isDead = true;
						CBinaryTree::getInstance()->listCurrentObject->erase(std::remove(
							CBinaryTree::getInstance()->listCurrentObject->begin(),
							CBinaryTree::getInstance()->listCurrentObject->end(),
							m_pObject),
							CBinaryTree::getInstance()->listCurrentObject->end());
					}
					else // Khi mario nho va cham
					{
						m_pObject->isCollision = true;
						this->droping();
					}
				}
				if (normalx == 0.0f && normaly == 1.0f)
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
			case COIN_BRICK:
			{
				if (normalx == 0.0f && normaly == -1.0f)
				{
					m_pObject->isCollision = true;
					this->droping();
				}
				if (normalx == 0.0f && normaly == 1.0f)
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
						m_pObject->unLocked = true;
						
					}
					this->droping();
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
}

CMario::CMario() : CLivingObject(0, D3DXVECTOR2(75.0f, 600.0f), NULL)
{
	this->Init();
}

CMario::~CMario()
{
}

void CMario::Init()
{
	m_action = drop;
	this->isDead = false;
	magicCounter = 0;
	doingChanging = false;

	this->m_pSprBullet = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Bullet/Bullet.png", 30, 30, 4, 4, NULL);
	this->smallMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/SmallMario.png", 50, 50, 10, 5, NULL);
	this->bigMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/BigMario.png", 50, 100, 10, 5, NULL);
	this->superMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/SuperMario.png", 50, 100, 10, 5, NULL);
	changeMario(smallMario, 0);
	velocity = D3DXVECTOR2(0.0f, - 200);
	accel = D3DXVECTOR2(0, - 100);
	prePosition = D3DXVECTOR2(0.0f, 0.0f);
	posMasat = D3DXVECTOR2(5.0f, 0.0f);
	deltaPosition = 0.0f;
	masat = posMasat.x;
	isShooting = false;
	shoot = false;
	timerShoot = 0.0f;
}

void CMario::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	if(isShooting)
		m_pBullet->Render();
}

/// <summary>
/// Updates the specified delta_time.
/// </summary>
/// <param name="delta_time">The delta_time.</param>
void CMario::Update(float delta_time)
{
	this->CheckCollision(this->GetBox(), delta_time);

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
	if (m_action != down) //Đang di chuyển
	{
		if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		{
			if (m_collisionX == true && direction == - 1)
			{
				velocity.x = 0.0f;
				m_collisionX = false;
				isSlowing = false;
				timer.x = 0.0f;
				accel.x = flagAccel.x;
				flagPosition.x = position.x;
			}
			else
			{
				direction = 1;

				if (deltaPosition < 0)		//Nếu đang chuyển động sang trái
				{
					if (isSlowing == false)
					{
						velocity.x = accel.x*timer.x + preVelocity.x;
						preVelocity.x = velocity.x;
						flagPosition.x = position.x;
						accel.x = direction * (flagAccel.x);
						timer.x = 0.0f;
						isSlowing = true;
					}
					else
					{
						accel.x = direction * (flagAccel.x + masat * 2);
					}
				}
				else if (deltaPosition == 0.0f)
				{
					isSlowing = false;
					velocity.x = 0.0f;
					accel.x = flagAccel.x;
				}
			}		
			if (m_action != jump) m_action = run;
		}
		else if (CGameKeyboard::getInstance()->IsKeyDown(DIK_LEFT))
		{
			if (m_collisionX == true && direction == 1)
			{
				velocity.x = 0.0f;
				m_collisionX = false;
				isSlowing = false;
				timer.x = 0.0f;
				accel.x = - flagAccel.x;
				flagPosition.x = position.x - 2;
			}
			else
			{
				direction = -1;

				if (deltaPosition > 0)		//Nếu đang chuyển động sang phải
				{
					if (m_collisionX == true)
					{
						m_collisionX = false;
					}
					if (isSlowing == false)
					{
						velocity.x = accel.x*timer.x + preVelocity.x;
						preVelocity.x = velocity.x;
						flagPosition.x = position.x;
						accel.x = direction * (flagAccel.x);
						timer.x = 0.0f;
						isSlowing = true;
					}
					else
					{
						accel.x = direction * (flagAccel.x + masat * 2);
					}
				}
				else if (deltaPosition == 0.0f)
				{
					isSlowing = false;
					velocity.x = 0.0f;
					accel.x = -flagAccel.x;
				}
				else if (deltaPosition < 0)
				{
					//if(m_collisionX == true)

				}
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
#pragma endregion

#pragma region Mario Nhảy
	//Sự kiện nhấn phím khi nhảy
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_SPACE))
	{
		if (m_action != down && m_action != jump && m_action != drop)
		{
			if (m_collisionY)
			{
				this->Jumping();
			}
		}
	}
	//Khi mario nhảy
	if (m_action == jump)
	{
		if ((velocity.y + accel.y * timer.y) < 400)
		{
			this->droping();
		}
			
	}
#pragma endregion

#pragma region bắn
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_A))
	{
		if (this->sprite == superMario)
		{
			D3DXVECTOR2 bulletPosition;
			if (direction == 1)
				bulletPosition = D3DXVECTOR2(position.x + width / 2, position.y);
			else
				bulletPosition = D3DXVECTOR2(position.x - width / 2, position.y);
			if (isShooting && m_pBullet->isDead == true)
				m_pBullet = new CBullet(direction, bulletPosition, m_pSprBullet);
			else if (isShooting == false)
				m_pBullet = new CBullet(direction, bulletPosition, m_pSprBullet);
			isShooting = true;
			shoot = true;
		}
	}
	
	if (isShooting)
	{
		timerShoot += delta_time;
		if (timerShoot >= delta_time * 10)
		{
			shoot = false;
			timerShoot = 0.0f;
		}
		m_pBullet->Update(delta_time);
	}

#pragma endregion 
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
	//Di chuyển ngang
	if (!m_collisionX)
	{
		timer.x += delta_time;

		preDeltaPosition = deltaPosition;
		deltaPosition = (flagPosition.x + velocity.x * timer.x + 1.0f / 2 * accel.x * timer.x * timer.x) - position.x;

		//Giới hạn tốc độ cho Mario
		if (abs(preVelocity.x + accel.x*timer.x) >= 300 && isSlowing == false)	//Giới hạn vận tốc nhỏ hơn 300
		{
			//Chuyển thành chuyển động đều
			velocity.x = preVelocity.x + accel.x*(timer.x - delta_time);
			accel.x = 0.0f;
			preVelocity.x = velocity.x;
			timer.x = delta_time;
			flagPosition.x = position.x;
		}	

		//mario đang dừng
		if ((isSlowing == true && accel.x < 0 && deltaPosition < 0) ||
			(isSlowing == true && accel.x > 0 && deltaPosition > 0) ||
			deltaPosition == 0) 
		{
			this->Standing();
		}		
		else
		{
			position.x = flagPosition.x + velocity.x * timer.x + 1.0f / 2 * accel.x * timer.x * timer.x;
		}
	}
	else
	{
		timer.x = delta_time;
		flagPosition.x = position.x;
		//deltaPosition = 0;
	}

	//Di chuyển dọc
	if (!m_collisionY)
	{
		timer.y += delta_time;
		position.y = flagPosition.y + velocity.y * timer.y + 1.0f / 2 * accel.y * timer.y * timer.y;
	}
	else
	{
		//velocity.y = 0;
		//accel.y = 0;
		flagPosition.y = position.y;
		timer.y = 0.0f;
	}

}

void CMario::UpdateAnimation(float delta_time)
{
	if (!shoot)
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
	else
	{
		if (direction == 1)
		{
			CAnimation::UpdateAnimation(delta_time, 1, 1, direction, 0.05f);
		}
		else
		{
			CAnimation::UpdateAnimation(delta_time, 8, 8, direction, 0.05f);
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
	magicCounter += 1;
	doingChanging = true;
	if (magicCounter <= number*GAME_FPS)
	{
		if (magicCounter % 30 == 0)
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
	}
	else //Thực hiện xong hiệu ứng
	{
		if (mario == smallMario)
		{
			preVelocity = D3DXVECTOR2(0.0f, 600.0f);
			flagAccel = D3DXVECTOR2(400.0f, 550.0f);
			if (this->sprite == bigMario || this->sprite == superMario)
			{
				position.y = position.y - 25;
			}
		}
		else
		{
			preVelocity = D3DXVECTOR2(0.0f, 700.0f);
			flagAccel = D3DXVECTOR2(400.0f, 550.0f);
			if (this->sprite == smallMario)
			{
				position.y = position.y + 25;
			}
		}

		this->sprite = mario;
		width = mario->width;
		height = mario->height;

		magicCounter = 0;
		doingChanging = false;
	}
}