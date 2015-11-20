#pragma once

#include "DynamicObject.h"

class CMushroomBlock : public CDynamicObject
{
public:
	CMushroomBlock(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CMushroomBlock();

	void Update(float delta_time);
	void Render();
};
