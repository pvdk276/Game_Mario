#pragma once

#include "Singleton.h"
#include "Box.h"
#include <algorithm>
#include <Windows.h>

class CCollision : public CSingleton<CCollision>
{
public:

	//check collision between 2 CBox, normalx and normaly are directions of collision, deltaTime is duration of collision checking
	float CheckCollision(CBox first, CBox second, float& normalx, float& normaly, float deltaTime);
};