#include "Bullet.h"
#include "BinaryTree.h"
#include "SoundManagement.h"

CBullet::CBullet(int direction, D3DXVECTOR2 position, CSprite * sprite): CLivingObject(id, position, sprite)
{
	this->position = position;
	width = 30.0f;
	height = 30.0f;
	this->sprite = sprite;
	flagPosition = this->position;
	this->direction = direction;
	velocity = D3DXVECTOR2(direction*600,-600);
	

	positionObject = position.y * 2;
	heighObject = height;
}

CBullet::~CBullet()
{
}

void CBullet::Update(float delta_time)
{
	//Xét va chạm
	m_collisionX = false;
	m_collisionY = false;

	for (int i = 0; i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		CBaseObject* m_pObject = CBinaryTree::getInstance()->listCurrentObject->at(i);
		float normalx = 0.0f, normaly = 0.0f;
		float distanceX, distanceY;
		float value = CCollision::getInstance()->CheckCollision(
			this->GetBox(), m_pObject->GetBox(), normalx, normaly,distanceX,distanceY, delta_time);
		if (m_pObject->type == PIPE && value == 1)
		{
			value = CCollision::getInstance()->CheckCollision(
				this->GetBox(), m_pObject->GetBox(), normalx, normaly, distanceX, distanceY, delta_time);
		}
		if (value < 1 && !this->isDead) //a collision occur
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
					this->isDead = true;
				}
				if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					m_collisionY = true;
					positionObject = m_pObject->GetBox().y;
					heighObject = m_pObject->GetBox().h;
					if (position.y > m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2)
						position.y = m_pObject->GetBox().y + m_pObject->GetBox().h / 2 + height / 2;
				}
			}
			break;

			//Va chạm với Enemy
			case ENEMY:
			{
				SoundManagement::GetInstance()->Get(BULLETBREAK_SOUND)->Play();
				m_pObject->isShoot = true;
			}
			break;
			case TURTLE:
			{
				SoundManagement::GetInstance()->Get(BULLETBREAK_SOUND)->Play();
				m_pObject->isShoot = true;
			}
			//va chạm với brick
			case COIN_BRICK:
			case BRICK:
			//Va chạm với block
			case COIN_BLOCK:
			case RED_MUSHROOM_BLOCK:
			case FLOWER_BLOCK:
			case GREEN_MUSHROOM_BLOCK:
			case STAR_BLOCK:
			{
				if (normalx == -1.0f && normaly == 0.0f || normalx == 1.0f && normaly == 0.0f)
				{
					this->isDead = true;
				}
				else if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
				{
					m_collisionY = true;
					positionObject = m_pObject->GetBox().y;
					heighObject = m_pObject->GetBox().h;
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
					positionObject = m_pObject->GetBox().y;
					heighObject = m_pObject->GetBox().h;
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
	//Chiều ngang
	if (abs(position.x - flagPosition.x) > 500)
		this->isDead = true;
	if (direction == 1)
		velocity.x = 600;
	else
		velocity.x = -600;
	timer.x += delta_time;
	position.x = flagPosition.x + velocity.x * timer.x + 1.0f / 2 * direction * accel.x * timer.x * timer.x;

	//Chiều dọc
	if (m_collisionY == true || position.y >= (positionObject + heighObject/2 + 100))
	{
		flagPosition.y = position.y;
		velocity.y = - velocity.y;
		timer.y = 0.0f;
	}

	timer.y += delta_time;
	position.y = flagPosition.y + velocity.y * timer.y + 1.0f / 2 * accel.y * timer.y * timer.y;

	UpdateAnimation(delta_time, 0, 3, direction, 0.05f);
}

void CBullet::Render()
{
	if (!this->isDead)
	{
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	}
}
