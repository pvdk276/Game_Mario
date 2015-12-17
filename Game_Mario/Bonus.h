#pragma once

#include "LivingObject.h"
#include "Global.h"

class CBonus : public CLivingObject
{
public:
	CBonus(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite);
	~CBonus();

	void Update(float delta_time);
	void Render();
	
	bool isOutOfBlock;
	D3DXVECTOR2 posOfBlock;
};