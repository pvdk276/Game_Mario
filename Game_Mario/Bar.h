#pragma once

#include "DynamicObject.h"
#include "Global.h"

class CBar : public CDynamicObject
{
private:
	D3DXVECTOR2 prePosition;
public:
	CBar(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite);
	~CBar();

	void Update(float delta_time);
	void Render();

	
};

