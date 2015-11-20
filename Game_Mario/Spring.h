#pragma once

#include "DynamicObject.h"
#include "Global.h"

class CSpring : public CDynamicObject
{
public:
	CSpring(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CSpring();

	void Update(float delta_time);
	void Render();
};

