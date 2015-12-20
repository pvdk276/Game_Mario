#include "Collision.h"

//SweptAABB 
float SweptAABB(CBox first, CBox second, float& normalx, float& normaly, float deltaTime)
{
	float dxEntry, dyEntry;
	float dxExit, dyExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (first.vx > 0.0f)	// Nếu box1 đang di chuyển
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

	if (first.vy > 0.0f)
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

	if (first.vx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		/*txEntry = dxEntry / first.vx;
		txExit = dxExit / first.vx;*/
		txEntry = dxEntry / (first.vx * deltaTime);
		txExit = dxExit / (first.vx * deltaTime);
	}

	if (first.vy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / (first.vy * deltaTime);
		tyExit = dyExit / (first.vy * deltaTime);
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
			if (dxEntry < 0.0f)
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
			if (dyEntry < 0.0f)
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
CBox GetSweptBroadphaseBox(CBox b, float deltaTime)
{
	CBox broadphasebox;
	float posX;
	float posY;
	posX = b.vx > 0 ? (b.x - b.w / 2) : (b.x - b.w / 2) + b.vx * deltaTime;
	posY = b.vy > 0 ? (b.y + b.h / 2) + b.vy * deltaTime : (b.y + b.h / 2);
	broadphasebox.w = b.vx > 0 ? b.vx * deltaTime + b.w : b.w - b.vx * deltaTime;
	broadphasebox.h = b.vy > 0 ? b.vy * deltaTime + b.h : b.h - b.vy * deltaTime;
	broadphasebox.x = posX + broadphasebox.w / 2;
	broadphasebox.y = posY - broadphasebox.h / 2;
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

float CCollision::CheckCollision(CBox first, CBox second, float& normalx, float& normaly, float deltaTime)
{
	CBox box1 = first;;
	CBox box2 = second;

	if (first.vx != 0 && second.vx != 0)
	{
		second.x += second.vx * deltaTime;
	}
	if (first.vy != 0 && second.vy != 0)
	{
		second.y += second.vy * deltaTime;
	}
	if (first.vx == 0 && second.vx != 0 || first.vy == 0 && second.vy != 0)
	{
		box1 = second;
		box2 = first;
	}
	else
	{
		box1 = first;
		box2 = second;
	}

	CBox broadphasebox = GetSweptBroadphaseBox(box1, deltaTime);
	if (AABBCheck(broadphasebox, box2))
	{
		return SweptAABB(box1, box2, normalx, normaly, deltaTime);
	}
	else return 1.0f;
}