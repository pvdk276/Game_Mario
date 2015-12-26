#include "Bonus.h"
#include "BinaryTree.h"

CBonus::CBonus(int id, ObjectName typeObj, D3DXVECTOR2 position, CSprite * sprite) : CLivingObject(id, position, sprite)
{
	type = typeObj;
	width = 50;
	height = 50;
	posOfBlock = position;
	velocity = D3DXVECTOR2(200.0f, 600.0f);
	accel = D3DXVECTOR2(0.0f, 550.0f);
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
							velocity.x = -velocity.x;
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
			timer.y = 0.0f;
			velocity.y = -(abs(velocity.y) + abs(accel.y) * timer.y);
			accel.y = -accel.y;
			flagPosition.y = position.y;
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
	{
		flagPosition.x = position.x;
		timer.x = 0.0f;
		velocity.x = -velocity.x;
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
	{
		if (!m_collisionY)
		{
			timer.y += delta_time;
			position.y = flagPosition.y + velocity.y * timer.y + 1.0f / 2 * accel.y * timer.y * timer.y;
		}
		else
		{
			timer.x += delta_time;
			position.x = flagPosition.x + velocity.x * timer.x + 1.0f / 2 * accel.x * timer.x * timer.x;
		}
		UpdateAnimation(delta_time, 0, 0, direction);
	}
	break;
	case GREEN_MUSHROOM:
	{
		if (!m_collisionY)
		{
			timer.y += delta_time;
			position.y = flagPosition.y + velocity.y * timer.y + 1.0f / 2 * accel.y * timer.y * timer.y;
		}
		else
		{
			timer.x += delta_time;
			position.x = flagPosition.x + velocity.x * timer.x + 1.0f / 2 * accel.x * timer.x * timer.x;
		}

		UpdateAnimation(delta_time, 1, 1, direction);
	}
	break;
	case COIN:
	{
		timer.y += delta_time;
		position.y = flagPosition.y + velocity.y * timer.y + 1.0f / 2 * accel.y * timer.y * timer.y;

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
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	}	
}
