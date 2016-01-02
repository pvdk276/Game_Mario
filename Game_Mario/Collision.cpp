#include "Collision.h"

//SweptAABB 
float CCollision::SweptAABB(CBox first, CBox second, float& distanceX, float& distanceY)
{
	float dxEntry, dyEntry;
	float dxExit, dyExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (m_deltaPosition.x > 0)	// Nếu box1 đang di chuyển sang phải
	{
		//Khoảng cách gần nhất từ box1 và box2
		dxEntry = (second.x - second.w / 2) - (first.x + first.w / 2);
		//Khoảng cách xa nhất từ box1 đến box2
		dxExit = (second.x + second.w / 2) - (first.x - first.w / 2);
	}
	else if(m_deltaPosition.x < 0)
	{
		dxEntry = (second.x + second.w / 2) - (first.x - first.w / 2);
		dxExit = (second.x - second.w / 2) - (first.x + first.w / 2);
	}
	else if (m_deltaPosition.x == 0)
	{
		float entry = (second.x - second.w / 2) - (first.x + first.w / 2);
		float exit = (second.x + second.w / 2) - (first.x - first.w / 2);
		if (abs(entry) == first.w + second.w && exit == 0)
		{
			dxEntry = exit;
			dxExit = entry;
		}
		else if (abs(entry) == 0 && exit == first.w + second.w)
		{
			dxEntry = entry;
			dxExit = exit;
		}
		else
		{
			dxEntry = (second.x + second.w / 2) - (first.x - first.w / 2);
			dxExit = (second.x - second.w / 2) - (first.x + first.w / 2);
		}
	}

	//chiều dọc
	if (m_deltaPosition.y > 0)
	{
		dyEntry = (second.y - second.h / 2) - (first.y + first.h / 2);
		dyExit = (second.y + second.h / 2) - (first.y - first.h / 2);
	}
	else if(m_deltaPosition.y < 0)
	{
		dyEntry = (second.y + second.h / 2) - (first.y - first.h / 2);
		dyExit = (second.y - second.h / 2) - (first.y + first.h / 2);
	}
	else if (m_deltaPosition.y == 0)
	{
		float entry = (second.y - second.h / 2) - (first.y + first.h / 2);
		float exit = (second.y + second.h / 2) - (first.y - first.h / 2);
		if (abs(entry) == first.h + second.h && exit == 0)
		{
			dyEntry = exit;
			dyExit = entry;
		}
		else if (abs(entry) == 0 && exit == first.h + second.h)
		{
			dyEntry = entry;
			dyExit = exit;
		}
		else
		{
			dyEntry = (second.y + second.h / 2) - (first.y - first.h / 2);
			dyExit = (second.y - second.h / 2) - (first.y + first.h / 2);
		}
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float txEntry, tyEntry;
	float txExit, tyExit;

	if (m_deltaPosition.x == 0 && abs(dxEntry) != 0)	//Nếu đang ở xa và đang đứng yên
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		/*txEntry = dxEntry / first.vx;
		txExit = dxExit / first.vx;*/
		if (dxEntry == 0 && m_deltaPosition.x == 0)
		{
			txEntry = 0;
			txExit = 0;
		}
		else
		{
			txEntry = dxEntry / m_deltaPosition.x;
			txExit = dxExit / m_deltaPosition.x;
		}
	}

	if (m_deltaPosition.y == 0 && abs(dyEntry) != 0)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		if (dyEntry == 0 && m_deltaPosition.y == 0)
		{
			tyEntry = 0;
			tyExit = 0;
		}		
		else
		{
			tyEntry = dyEntry / m_deltaPosition.y;
			tyExit = dyExit / m_deltaPosition.y;
		}
	}

	// Tìm khoảng thời gian va chạm sớm nhất và va chạm trễ nhất
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	// if there was no collision
	if (entryTime > exitTime || txEntry < 0.0f && tyEntry < 0.0f || txEntry > 1.0f || tyEntry > 1.0f)
	{
		m_normalx = 0.0f;
		m_normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (txEntry > tyEntry)
		{
			if (dxEntry <= 0.0f)
			{
				m_normalx = 1.0f;
				m_normaly = 0.0f;
			}
			else
			{
				m_normalx = -1.0f;
				m_normaly = 0.0f;
			}
		}
		else
		{
			if (dyEntry <= 0.0f)
			{
				m_normalx = 0.0f;
				m_normaly = 1.0f;
			}
			else
			{
				m_normalx = 0.0f;
				m_normaly = -1.0f;
			}
		}

		// return the time of collision
		distanceX = dxEntry;
		distanceY = dyEntry;
		return entryTime;
	}
}

int CCollision::checkCollisionDirection(CBox box1, CBox box2)
{
	if (box1.x + box1.w / 2 < box2.x - box2.w / 2 ||
		box1.x - box1.w / 2 > box2.x + box2.w / 2)
	{
		if (!((box1.y - box1.h / 2) > (box2.y + box2.h / 2) ||
			(box1.y + box1.h / 2) < (box2.y - box2.h / 2)))
			return 1; //va chạm ngang
	}
	else if ((box1.y - box1.h / 2) > (box2.y + box2.h / 2) ||
		(box1.y + box1.h / 2) < (box2.y - box2.h / 2))
	{
		if (!(box1.x + box1.w / 2 < box2.x - box2.w / 2 ||
			box1.x - box1.w / 2 > box2.x + box2.w / 2))
			return -1; //Va chạm dọc
	}
	return 0;	// không va chạm
}

//Broadphase box : if block is not within broadphase box, there is not a collision.
//If block is within broadphase box , there is maybe a collision
CBox CCollision::GetSweptBroadphaseBox(CBox b)
{
	CBox broadphasebox;

	broadphasebox.x = b.x + m_deltaPosition.x;
	broadphasebox.w = 2 * (0.5*b.w + abs(m_deltaPosition.x));
	broadphasebox.y = b.y + m_deltaPosition.y;
	broadphasebox.h = 2 * (0.5*b.h + abs(m_deltaPosition.y));

	return broadphasebox;
}

//check if b2 within b1(broadphase box)
bool AABBCheck(CBox b1, CBox b2)
{
	CBox a = b1;
	CBox b = b2;
	return !(b1.x + b1.w / 2 < b2.x - b2.w / 2 ||
		b1.x - b1.w / 2 > b2.x + b2.w / 2 ||
		b1.y + b1.h / 2 < b2.y - b2.h / 2 ||
		b1.y - b1.h / 2 > b2.y + b2.h / 2);
}

float CCollision::CheckCollision(CBox first, CBox second, float& normalx, float& normaly,float& distanceX, float& distanceY, float deltaTime)
{
	CBox box1 = first;
	CBox box2 = second;
	m_deltaPosition = m_deltaPosition1;
	//Tính quãng đường đi được của 2 box
	DeltaPosition(first, second, deltaTime);
	//Nếu 2 box cùng chuyển động
	if (m_deltaPosition1.x != 0.0f && m_deltaPosition2.x != 0)
	{
		second.x += m_deltaPosition2.x;
	}
	if (m_deltaPosition1.y != 0.0f && m_deltaPosition2.y != 0.0f)
	{
		second.y += m_deltaPosition2.y;
	}

	//nếu chuyển động vuông góc
	if (m_deltaPosition1.y != 0.0f && m_deltaPosition1.x == 0.0f && m_deltaPosition2.x != 0.0f && m_deltaPosition2.y == 0.0f)
	{
		second.x += m_deltaPosition2.x;
	}
	else if (m_deltaPosition1.y == 0.0f && m_deltaPosition1.x != 0.0f && m_deltaPosition2.x == 0.0f && m_deltaPosition2.y != 0.0f)
	{
		second.y += m_deltaPosition2.y;
	}
	
	//Xét va chạm ngang
	if (this->checkCollisionDirection(box1, box2) == 1)
	{
		//Nếu 2 chuyển động, 1 đứng yên
		if (m_deltaPosition1.x == 0.0f && m_deltaPosition2.x != 0.0f)
		{
			box1 = second;
			box2 = first;
			m_deltaPosition = m_deltaPosition2;
		}
		else  //Nếu 1 chuyển động
		{
			box1 = first;
			box2 = second;
			m_deltaPosition = m_deltaPosition1;
		}
	}
	else if (this->checkCollisionDirection(box1, box2) == -1)	// va chạm dọc
	{
		//Nếu 2 chuyển động, 1 đứng yên
		if (m_deltaPosition1.y == 0.0f && m_deltaPosition2.y != 0.0f)
		{
			box1 = second;
			box2 = first;
			m_deltaPosition = m_deltaPosition2;
		}
		else  //Nếu 1 chuyển động
		{
			box1 = first;
			box2 = second;
			m_deltaPosition = m_deltaPosition1;
		}
	}

	CBox broadphasebox = GetSweptBroadphaseBox(box1);

	if (AABBCheck(broadphasebox, box2))
	{
		float _distanceX, _distanceY;
		float value = SweptAABB(box1, box2,_distanceX,_distanceY);
		normalx = m_normalx;
		normaly = m_normaly;
		distanceX = _distanceX;
		distanceY = _distanceY;
		return value;
	}

	normalx = 0.0f;
	normaly = 0.0f;
	return 1;
}

void CCollision::DeltaPosition(CBox first, CBox second, float deltaTime)
{
	// First
	m_deltaPosition1.x = (first.vx * (first.tx + deltaTime) + 0.5 * first.ax * (first.tx + deltaTime) * (first.tx + deltaTime)) -
		(first.vx * first.tx + 0.5 * first.ax * first.tx * first.tx);

	if (first.vx > 0 && first.ax < 0 && m_deltaPosition1.x < 0 ||
		first.vx < 0 && first.ax > 0 && m_deltaPosition1.x > 0)
	{
		m_deltaPosition1.x = 0;
	}

	m_deltaPosition1.y = (first.vy * (first.ty + deltaTime) + 0.5 * first.ay * (first.ty + deltaTime) * (first.ty + deltaTime)) -
		(first.vy * first.ty + 0.5 * first.ay * first.ty * first.ty);

	//Second
	m_deltaPosition2.x = (second.vx * (second.tx + deltaTime) + 0.5 * second.ax * (second.tx + deltaTime) * (second.tx + deltaTime)) -
		(second.vx * second.tx + 0.5 * second.ax * second.tx * second.tx);
	
	if (second.vx > 0 && second.ax < 0 && m_deltaPosition2.x < 0 ||
		second.vx < 0 && second.ax > 0 && m_deltaPosition2.x > 0)
	{
		m_deltaPosition2.x = 0;
	}

	m_deltaPosition2.y = (second.vy * (second.ty + deltaTime) + 0.5 * second.ay * (second.ty + deltaTime) * (second.ty + deltaTime)) -
		(second.vy * second.ty + 0.5 * second.ay * second.ty * second.ty);
}