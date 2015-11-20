#pragma once

#include "DynamicObject.h"
#include "Global.h"

class CBar : public CDynamicObject
{
public:
	CBar(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CBar();

	void Update(float delta_time);
	void Render();
};

