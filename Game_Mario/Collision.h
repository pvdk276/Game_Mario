#pragma once

#include "Singleton.h"
#include "Box.h"
#include <algorithm>
#include <Windows.h>
#include <d3dx9.h>

class CCollision : public CSingleton<CCollision>
{
private:
	D3DXVECTOR2 m_deltaPosition;
	D3DXVECTOR2 m_deltaPosition1;	//quãng đường di chuyển của first
	D3DXVECTOR2 m_deltaPosition2;	//quãng đường di chuyển của second
	
	float m_normalx;
	float m_normaly;
	bool m_isStandOn;

	//Tính quãng đường di chuyển
	void DeltaPosition(CBox first, CBox second, float deltaTime);
	//Tạo vùng biên
	CBox GetSweptBroadphaseBox(CBox b);
	//Kiểm tra va chạm
	float SweptAABB(CBox first, CBox second, float& distanceX, float& distanceY);
	//Kiểm tra đang đứng hay không
	int checkCollisionDirection(CBox box1, CBox box2);
public:

	//check collision between 2 CBox, normalx and normaly are directions of collision, deltaTime is duration of collision checking
	float CheckCollision(CBox first, CBox second, float& normalx, float& normaly, float& distanceX,float& distanceY, float deltaTime);

	//

	
};