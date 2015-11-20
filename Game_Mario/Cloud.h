#pragma once

#include "DynamicObject.h"
#include "Global.h"

class CCloud : public CDynamicObject
{
public:
	CCloud(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CCloud();

	void Update(float delta_time);
	void Render();	
};