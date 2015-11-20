#pragma once

#include "LivingObject.h"

class CCarnivorousFlower : public CLivingObject
{
public:
	CCarnivorousFlower(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CCarnivorousFlower();
	
	void Update(float delta_time);
	void Render();
};
