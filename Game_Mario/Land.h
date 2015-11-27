#pragma once

#include "StaticObject.h"

class CLand : public CStaticObject
{
public:
	CLand(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite);
	~CLand();

	void Update(float delta_time);
	void Render();
};