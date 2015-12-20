#include "Bonus.h"
#include "BinaryTree.h"

CBonus::CBonus(int id, ObjectName typeObj, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	type = typeObj;
	width = 50;
	height = 50;
	posOfBlock = position;
	velocity = D3DXVECTOR2(0.0f, 2.0f);
	maxAccel = D3DXVECTOR2(10.0f, 10.0f);
	MaxVelocity = D3DXVECTOR2(15.0f, 50.0f);
	this->isDead = false;
	this->isCollision = false;
}

CBonus::~CBonus()
{
}

void CBonus::Update(float delta_time)
{
#pragma region Mushroom
	//Check collision
	m_collisionX = false;
	m_collisionY = false;

	//Nếu là RED_MUSHROOM hoặc GREEN_MUSHROOM thì xét va chạm
	if (type == RED_MUSHROOM || type == GREEN_MUSHROOM)
	{
		for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
		{
			m_pObject = CBinaryTree::getInstance()->listCurrentObject->at(i);
			float normalx, normaly;
			float value = CCollision::getInstance()->CheckCollision(
				this->GetBox(),
				m_pObject->GetBox(),
				normalx, normaly, delta_time);
			if (value < 1) //a collision occur
			{
				switch (m_pObject->type)
				{
				case PIPE:
				case STONE:
				case CARNIVOROUS_FLOWER_PIPE:
				case PIPE_UP:
				case PIPE_DOWN:
				{
					if (normalx == 1.0f && normaly == 0.0f || normalx == -1.0f && normaly == 0.0f)
					{
						m_collisionX = true;
					}
				}
				break;
				case BRICK:
				case COIN_BRICK:
				case LEFT_LAND:
				case CENTER_LAND:
				case RIGHT_LAND:
				{
					if (normalx == 0.0f && normaly == 1.0f || normalx == 0.0f && normaly == -1.0f)
					{
						m_collisionY = true;
						if (velocity.x == 0.0f)
							velocity.x = MaxVelocity.x;
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
	}	
#pragma endregion

	//Bonus khi di chuyển lên lên
	if (position.y > posOfBlock.y + width + 50)
	{
		switch (type)
		{
		case RED_MUSHROOM:
		case GREEN_MUSHROOM:
		{
			if (velocity.y > 0) velocity.y *= -1;
		}
		break;
		case COIN:
		{
			this->isDead = true;
		}
		break;
		case FLOWER:
		{
			
		}
		break;
		case STAR:
		{
			
		}
		break;
		default:
			break;
		}
		
	}

	//Tính vận tốc cho bonus
	if (m_collisionX)
		velocity.x *= -1;
	if (velocity.y < MaxVelocity.y && velocity.y > 0 || velocity.y > - MaxVelocity.y && velocity.y < 0)
	{
		/*if (velocity.y > 0)
			accel.y = maxAccel.y;
		else*/
			accel.y = - maxAccel.y;
	}
	else
	{
		/*if(velocity.y > 0)
			velocity.y = MaxVelocity.y;
		else*/
			velocity.y = - MaxVelocity.y;
		accel.y = 0;
	}
	
	//update Postion and Animation
	updatePosAnima(delta_time);
}
void CBonus::updatePosAnima(float delta_time)
{
	//Cập nhật vị trí và sprite cho từng loại đối tượng
	switch (type)
	{
	case RED_MUSHROOM:
	case GREEN_MUSHROOM:
	{
		if (!m_collisionY)
		{
			position.y += velocity.y * delta_time + 1.0f / 2 * accel.y * delta_time * delta_time;
			velocity.y += accel.y * delta_time;
		}
		else
		{
			position.x += velocity.x * delta_time;
		}
	}
	break;
	case COIN:
	{
		position.y += velocity.y * delta_time + 1.0f / 2 * accel.y * delta_time * delta_time;
		velocity.y += accel.y * delta_time;

		UpdateAnimation(delta_time, 0, 1, direction);
	}
	break;
	case FLOWER:
	{
		UpdateAnimation(delta_time, 0, 3, direction);
	}
	break;
	case STAR:
	{
		UpdateAnimation(delta_time, 0, 3, direction);
	}
	break;
	default:
		break;
	}
}

void CBonus::Render()
{
	if (!this->isDead)
	{
		if (type == RED_MUSHROOM) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
		else if (type == GREEN_MUSHROOM) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
		else sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	}	
}
