#pragma once

#include "DynamicObject.h"
#include "LivingObject.h"
#include "Bonus.h"

class CBlock : public CDynamicObject
{
public:
	CBlock(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2);
	~CBlock();

	void Update(float delta_time);
	void Render();
	void ActiveBonus();

	CBonus* bonus;
};
