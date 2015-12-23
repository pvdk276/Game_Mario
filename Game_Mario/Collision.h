#pragma once

#include "Singleton.h"
#include "Box.h"
#include <algorithm>
#include <Windows.h>
#include <d3dx9.h>

class CCollision : public CSingleton<CCollision>
{
private:
	D3DXVECTOR2 accel;
	float m_timer;
	D3DXVECTOR2 m_deltaPosition;

	void DeltaPosition(CBox first, CBox second, D3DXVECTOR2 timer, float deltaTime);
	CBox GetSweptBroadphaseBox(CBox b);
	float SweptAABB(CBox first, CBox second, float& normalx, float& normaly, D3DXVECTOR2 timer, float deltaTime);
public:

	//check collision between 2 CBox, normalx and normaly are directions of collision, deltaTime is duration of collision checking
	float CheckCollision(CBox first, CBox second, float& normalx, float& normaly, D3DXVECTOR2 timer, float deltaTime);

	
};