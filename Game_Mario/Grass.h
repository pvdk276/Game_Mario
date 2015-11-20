#pragma once

#include "DynamicObject.h"

class CGrass : public CDynamicObject
{
public:
	CGrass(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CGrass();

	void Update(float delta_time);
	void Render();	
};