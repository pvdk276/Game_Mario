#pragma once

#include "LivingObject.h"

class CFireTurtle : public CLivingObject
{
public:
	CFireTurtle(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CFireTurtle();

	void Update(float delta_time);
	void Render();
};