#include "Collision.h"

//SweptAABB 
float CCollision::SweptAABB(CBox first, CBox second, float& normalx, float& normaly, D3DXVECTOR2 timer, float deltaTime)
{
	float dxEntry, dyEntry;
	float dxExit, dyExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (first.vx >= 0.0f && first.ax > 0.0f || first.vx > 0 && first.ax < 0 ||
		first.vx > 0.0f && first.ax == 0)	// Nếu box1 đang di chuyển sang phải ( nhanh dần và chậm dần)
	{
		//Khoảng cách gần nhất từ box1 và box2
		dxEntry = (second.x - second.w / 2) - (first.x + first.w / 2);
		//Khoảng cách xa nhất từ box1 đến box2
		dxExit = (second.x + second.w / 2) - (first.x - first.w / 2);
	}
	else 
	{
		dxEntry = (second.x + second.w / 2) - (first.x - first.w / 2);
		dxExit = (second.x - second.w / 2) - (first.x + first.w / 2);
	}

	if (first.vy >= 0.0f && first.ay > 0.0f || first.vy > 0 && first.ay < 0 ||
		first.vy > 0.0f && first.ay == 0)
	{
		dyEntry = (second.y - second.h / 2) - (first.y + first.h / 2);
		dyExit = (second.y + second.h / 2) - (first.y - first.h / 2);
	}
	else
	{
		dyEntry = (second.y + second.h / 2) - (first.y - first.h / 2);
		dyExit = (second.y - second.h / 2) - (first.y + first.h / 2);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float txEntry, tyEntry;
	float txExit, tyExit;

	if (m_deltaPosition.x == 0 && abs(dxEntry) != 0)
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
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (txEntry > tyEntry)
		{
			if (dxEntry <= 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (dyEntry <= 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

//Broadphase box : if block is not within broadphase box, there is not a collision.
//If block is within broadphase box , there is maybe a collision
CBox CCollision::GetSweptBroadphaseBox(CBox b)
{
	CBox broadphasebox;
	float posX;
	float posY;

	if (b.vx >= 0.0f && b.ax > 0.0f || b.vx > 0 && b.ax < 0)
	{
		broadphasebox.x = b.x + m_deltaPosition.x;
		broadphasebox.w = 2 * (0.5*b.w + m_deltaPosition.x);
	}
	else
	{
		broadphasebox.x = b.x + m_deltaPosition.x;
		broadphasebox.w = 2 * (0.5*b.w + abs(m_deltaPosition.x));

	}

	if (b.vy >= 0.0f && b.ay > 0.0f || b.vy > 0 && b.ay < 0)
	{
		broadphasebox.y = b.y + m_deltaPosition.y;
		broadphasebox.h = 2 * (0.5*b.h + m_deltaPosition.y);
	}
	else
	{
		broadphasebox.y = b.y + m_deltaPosition.y;
		broadphasebox.h = 2 * (0.5*b.h + abs(m_deltaPosition.y));
	}

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

float CCollision::CheckCollision(CBox first, CBox second, float& normalx, float& normaly, D3DXVECTOR2 timer, float deltaTime)
{
	CBox box1 = first;;
	CBox box2 = second;

	if (!(first.vx == 0.0f && first.ax == 0.0f) && !(second.vx == 0.0f && second.ax == 0.0f))
	{
		second.x += second.vx * deltaTime + 0.5 * second.ax * deltaTime * deltaTime;
	}
	if (!(first.vy == 0.0f && first.ay == 0.0f) && !(second.vy == 0.0f && second.ay == 0.0f))
	{
		second.y += second.vy * deltaTime + 0.5* second.ay * deltaTime * deltaTime;
	}
	if (((first.vx == 0 && first.ax == 0) && !(second.vx == 0 && second.ax == 0) ) || 
		((first.vy == 0 && first.ay == 0) && !(second.vy == 0 && second.ay == 0)))
	{
		box1 = second;
		box2 = first;
	}
	else
	{
		box1 = first;
		box2 = second;
		//m_timer = timer;
	}

	DeltaPosition(box1, box2, timer, deltaTime);
	CBox broadphasebox = GetSweptBroadphaseBox(box1);

	if (AABBCheck(broadphasebox, box2))
	{
		return SweptAABB(box1, box2, normalx, normaly, timer, deltaTime);
	}
	return 1;
	//else return 1.0f;
}

void CCollision::DeltaPosition(CBox first, CBox second, D3DXVECTOR2 timer, float deltaTime)
{
	CBox a = first;
	CBox b = second;

	m_deltaPosition.x = (first.vx * (timer.x + deltaTime) + 0.5 * first.ax * (timer.x + deltaTime) * (timer.x + deltaTime)) -
		(first.vx * timer.x + 0.5 * first.ax * timer.x * timer.x);

	if (first.vx > 0 && first.ax < 0 && m_deltaPosition.x < 0 ||
		first.vx < 0 && first.ax > 0 && m_deltaPosition.x > 0)
	{
		m_deltaPosition.x = 0;
	}

	m_deltaPosition.y = (first.vy * (timer.y + deltaTime) + 0.5 * first.ay * (timer.y + deltaTime) * (timer.y + deltaTime)) -
		(first.vy * timer.y + 0.5 * first.ay * timer.y * timer.y);
}