#pragma once

#include "DynamicObject.h"

class CCoinBlock : public CDynamicObject
{
public:
	CCoinBlock(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CCoinBlock();

	void Update(float delta_time);
	void Render();
};
