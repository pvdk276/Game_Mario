/*+===================================================================
File:      Collision.cpp

Summary:   ??nh ngh?a các ph??ng th?c c?a CCollision.
===================================================================+*/

#include "Collision.h"


CCollision::CCollision()
{
}

CCollision::~CCollision()
{

}

CBox CCollision::GetSweptBroadphaseBox(CBox b, float t)
{
	CBox broadphaseBox;
	broadphaseBox.x = b.vx > 0 ? b.x : b.x + b.vx * t;
	broadphaseBox.y = b.vy < 0 ? b.y : b.y + b.vy * t;
	broadphaseBox.w = b.vx > 0 ? b.vx * t + b.w : b.w - b.vx * t;
	broadphaseBox.h = b.vy > 0 ? b.vy * t + b.h : b.h - b.vy * t;

	return broadphaseBox;
}

bool CCollision::AABBCheck(CBox b1, CBox b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y < b2.y - b2.h || b1.y - b1.h > b2.y);
}

float CCollision::SweepAABB(CBox b1, CBox b2, float& normalx, float& normaly, float timeFrame)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// Xác ??nh kho?ng cách b?t ??u và k?t thúc va ch?m theo hay chi?u x, y.
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else //Náº¿u box2 di chuyá»ƒn, box1 khÃ´ng di chuyá»ƒn
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = (b2.y - b2.h) - b1.y;
		yInvExit = b2.y - (b1.y - b1.h);
	}
	else
	{
		yInvEntry = b2.y - (b1.y - b1.h);
		yInvExit = (b2.y - b2.h) - b1.y;
	}

	float xEntry, xExit;
	float yEntry, yExit;

	// Tìm th?i gian b?t ??u và k?t thúc va ch?m theo 2 tr?c x, y.
	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// K?t h?p th?i gian b?t ??u và k?t thúc va ch?m theo 2 tr?c x, y
	// Tìm th?i gian b?t ??u và k?t thúc va ch?m t?ng h?p.
	float entryTime = __max(xEntry, yEntry);
	float exitTime = __min(xExit, yExit);

	// Khi không có va ch?m trong frame này.
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > timeFrame || yEntry > timeFrame)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return timeFrame;
	}
	else // Khi x?y ra va ch?m.
	{
		// Va ch?m theo chi?u x.
		if (xEntry > yEntry)
		{
			// Va ch?m t? trái qua ph?i.
			if (b1.vx > 0.0f)
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
			else // Va ch?m t? ph?i qua trái.
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
		}
		else // Va chạm theo chiều y
		{
			// Va chạm từ dưới lên
			if (b1.vy > 0.0f)
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
			else // Va chạm từ trên xuống
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
		}

		//if (entryTime < timeFrame && normalx = -1)
		//{
		//	
		//}

		return entryTime;
	}
}

