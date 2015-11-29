#pragma once

#include "LivingObject.h"

class CEnemy : public CLivingObject
{
private:
	int verlocity = -1;
public:
	CEnemy(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CEnemy();

	void Update(float delta_time);
	void Render();
};
