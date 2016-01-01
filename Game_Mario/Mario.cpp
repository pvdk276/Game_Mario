#include "Mario.h"
#include "Camera.h"
#include "GameKeyboard.h"
#include "BinaryTree.h"
#include "SoundManagement.h"
#include "GameGraphic.h"

CMario::CMario() : CLivingObject(0, D3DXVECTOR2(75.0f, 600.0f), NULL)
{
	this->Init();
}

CMario::~CMario()
{
	delete smallMario;
	delete bigMario;
	delete superMario;
	delete m_pSprBullet;
	if (m_pBullet)
		delete m_pBullet;
	if (m_pObject)
		delete m_pObject;

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
	changeMario(superMario, 0);
	velocity = D3DXVECTOR2(0.0f, - 200);
	accel = D3DXVECTOR2(0, - 100);
	prePosition = D3DXVECTOR2(0.0f, 0.0f);
	
	posMasat = D3DXVECTOR2(5.0f, 0.0f);
	deltaPosition = 0.0f;
	masat = posMasat.x;
	isShooting = false;
	shoot = false;
	timerShoot = 0.0f;
	this->isWin = false;

	this->Backup();
}

void CMario::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	if(isShooting)
		m_pBullet->Render();
}

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
			flagPosition.x = position.x;
			timer.x = 0.0f;
		}
	}
	if (m_action != down && m_action != dead) //Đang di chuyển
	{
		if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		{
			if (m_collisionX == true && direction == - 1)
			{
				this->BeginMoving(position.x + 2, 0.0f, flagAccel.x);
			}
			else
			{
				direction = 1;

				if (deltaPosition < 0)		//Nếu đang chuyển động sang trái
				{
					if (m_collisionX)
					{
						this->BeginMoving(position.x, 0.0f, flagAccel.x);
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
					this->BeginMoving(position.x, 0.0f, flagAccel.x);
				}
			}		
			if (m_action != jump) m_action = run;
		}
		else if (CGameKeyboard::getInstance()->IsKeyDown(DIK_LEFT))
		{
			if (m_collisionX == true && direction == 1)
			{
				this->BeginMoving(position.x - 2, 0.0f,- flagAccel.x);
			}
			else
			{
				direction = -1;

				if (deltaPosition > 0)		//Nếu đang chuyển động sang phải
				{
					if (m_collisionX)
					{
						this->BeginMoving(position.x, 0.0f, -flagAccel.x);
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
					this->BeginMoving(position.x, 0.0f,- flagAccel.x);
				}
			}	
			if (m_action != jump) m_action = run;
		}
		else // KHông nhấn nút (trượt)
		{
			if (m_action == run || m_action == jump || m_action == drop)
			{
				if (isSlowing == false && timer.x != 0)
				{
					velocity.x = accel.x*timer.x + preVelocity.x;
					preVelocity.x = velocity.x;
					flagPosition.x = position.x;
					accel.x = -1.0f * direction * (flagAccel.x);
					timer.x = 0.0f;
					isSlowing = true;
				}
				if (m_collisionX)
				{
					flagPosition.x = position.x;
					accel.x = 0;
					timer.x = 0;
				}
			}

			if (m_action != jump && m_action != drop && m_action != dead) m_action = stand;
			
			
		}
	}
	else if(m_action == down)
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
				bulletPosition = D3DXVECTOR2(position.x + width / 2 - 15, position.y);
			else
				bulletPosition = D3DXVECTOR2(position.x - width / 2 + 15, position.y);
			if (isShooting && m_pBullet->isDead == true)
				m_pBullet = new CBullet(direction, bulletPosition, m_pSprBullet);
			else if (isShooting == false)
				m_pBullet = new CBullet(direction, bulletPosition, m_pSprBullet);
			isShooting = true;
			shoot = true;

			SoundManagement::GetInstance()->Get(HEADSHOOT_SOUND)->Play();
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
		this->Deading();
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
		if (abs(preVelocity.x + accel.x*timer.x) >= 500 && isSlowing == false)	//Giới hạn vận tốc nhỏ hơn 300
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
		timer.x = 0.0f;
		flagPosition.x = position.x;
		velocity.x = 0;
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
		else if (m_action == dead)
		{
			if(this->sprite != smallMario)
				this->sprite = smallMario;
			CAnimation::UpdateAnimation(delta_time, 4, 4, direction, 0.2f);
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

void CMario::Backup()
{
	this->backupPosition = position;
	this->backupSprite = this->sprite;
}

void CMario::Reset()
{
	direction = 1;
	timer = D3DXVECTOR2(0.0f, 0.0f);
	position = rootPosition;
	flagPosition = position;
	accel = flagAccel;
	this->Init();
}

void CMario::Resume()
{
	position = backupPosition;
	flagPosition = position;
	this->sprite = backupSprite;
	timer.x = 0;
	timer.y = 0;
	isDead = false;
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
		width = mario->width - 10;
		height = mario->height;

		magicCounter = 0;
		doingChanging = false;
	}
}

void CMario::BeginMoving(float positionx, float velocityx, float accelx)
{
	isSlowing = false;
	position.x = positionx;
	flagPosition.x = positionx;
	velocity.x = velocityx;
	preVelocity.x = 0.0f;
	accel.x = accelx;
	timer.x = 0.0f;
}

void CMario::droping()
{
	m_action = drop;
	velocity.y = -(abs(velocity.y) + abs(accel.y) * timer.y);
	timer.y = 0.0f;
	accel.y = -flagAccel.y;
	flagPosition.y = position.y;
}

void CMario::Jumping()
{
	m_collisionY = false;
	velocity.y = preVelocity.y;
	accel.y = -flagAccel.y;
	timer.y = 0.0f;
	flagPosition.y = position.y;
	m_action = jump;
	SoundManagement::GetInstance()->Get(JUMP_SOUND)->Play();
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

void CMario::Deading()
{
	if (m_action != dead)
	{
		velocity.y = preVelocity.y;
		accel.y = - flagAccel.y;
		timer.y = 0.0f;
		flagPosition.y = position.y;

		timer.x = 0.0f;
		velocity.x = 0.0f;
		accel.x = 0.0f;
		flagPosition.x = position.x;
	}
	m_action = dead;
	SoundManagement::GetInstance()->Get(DYING_SOUND)->Play();
	if (position.y <= 0.0f && (velocity.y + accel.y*timer.y) < 0)
	{
		this->isDead = true;
	}
}

void CMario::CheckCollision(CBox mario, float delta_time)
{
	//Va chạm trong current object
	m_collisionX = false;
	m_collisionY = false;
	for (int i = 0; i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		m_pObject = CBinaryTree::getInstance()->listCurrentObject->at(i);
		float normalx = 0.0f, normaly = 0.0f;
		float distanceX, distanceY;
		float value;
		value = CCollision::getInstance()->CheckCollision(
			mario, m_pObject->GetBox(), normalx, normaly, distanceX, distanceY, delta_time);
		if (value < 1 && !m_pObject->isDead && m_action != dead) //a collision occur
		{
			switch (m_pObject->type)
			{
				//Va chạm với ống
			case PIPE:
			case CARNIVOROUS_FLOWER_PIPE:
			case PIPE_UP:
			case PIPE_DOWN:
			case PIPE_DOWN_1:
			case PIPE_DOWN_2:
			case PIPE_UP_1:
			case PIPE_UP_2:
			case PIPE_LEFT:
			case PIPE_LEFT_1:
			case PIPE_LEFT_2:
			{
				this->Backup();
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
	 				m_collisionX = true;
					position.x += distanceX;
					flagPosition.x = position.x;
					timer.x = 0.0f;
					accel.x = 0.0f;
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
			case STONE:
			{
				if (normalx == 0.0f && normaly == -1.0f)
				{
					this->droping();
				}
				if (normalx == 0.0f && normaly == 1.0f)
				{
					//this->Backup();
					m_collisionY = true;
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
				if (position.y != (position.y + distanceY))
				{
					if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
					{
						m_collisionX = true;
						position.x += distanceX;
						flagPosition.x = position.x;
						timer.x = 0.0f;
						accel.x = 0.0f;
					}
				}
			}
			break;
			//Va chạm với Enemy
			case TURTLE:
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
					this->Jumping();
					m_pObject->isCollision = true;
				}
			}
			break;
			case ENEMY:
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					position.x = position.x + distanceX;
					//Mario chết
					if (!m_pObject->isCollision)
					{
						if (this->sprite == smallMario)
						{
							this->Deading();
						}
						else //Nếu là mario lớn
						{
							//currentSprite = this->sprite;
							changeMario(smallMario, 0);
						}
					}	
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					if (!m_pObject->isCollision)
					{
						this->Jumping();
						m_pObject->isCollision = true;
						SoundManagement::GetInstance()->Get(ENEMYDIE_SOUND)->Play();
					}
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
						SoundManagement::GetInstance()->Get(BRICKBROKEN_SOUND)->Play();
					}
					else // Khi mario nho va cham
					{
						m_pObject->isCollision = true;
						this->droping();
					}
				}
				if (normalx == 0.0f && normaly == 1.0f)
				{
					this->Backup();
					m_collisionY = true;
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
				if (position.y != (position.y + distanceY))
				{
					if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
					{
						m_collisionX = true;
					}
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
					this->Backup();
					m_collisionY = true;
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;
					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
				if (position.y != (position.y + distanceY))
				{
					if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
					{
						m_collisionX = true;
					}
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
					position.x = position.x + distanceX;
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
					this->Backup();
					m_collisionY = true;
					if (m_action == jump || m_action == drop)
					{
						if (velocity.x != 0) m_action = run;
						else m_action = stand;

					}
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
				if (position.y != (position.y + distanceY))
				{
					if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
					{
						m_collisionX = true;
					}
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
			case TOWER:
			{
				this->isWin = true;
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