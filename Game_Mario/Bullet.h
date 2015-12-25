#pragma once
#include "LivingObject.h"

class CBullet : public CLivingObject
{
public:
	CBullet(int direction, D3DXVECTOR2 position, CSprite* sprite);
	~CBullet();

	void Update(float delta_time);
	void Render();
};
