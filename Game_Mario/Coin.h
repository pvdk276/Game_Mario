#pragma once

#include "DynamicObject.h"
#include "Global.h"

class CCoin : public CDynamicObject
{
public:
	CCoin(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CCoin();

	void Update(float delta_time);
	void Render();	
};