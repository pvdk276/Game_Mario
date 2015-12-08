#pragma once
#include "DynamicObject.h"
class CFlower : public CDynamicObject
{
public:
	CFlower(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CFlower();
	void Update(float delta_time);
	void Render();
};

