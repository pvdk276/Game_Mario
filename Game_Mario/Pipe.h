#pragma once

#include "StaticObject.h"
#include "CarnivorousFlower.h"

class CPipe : public CStaticObject
{
public:
	CCarnivorousFlower* flower;

	CPipe(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2);
	~CPipe();

	void Update(float delta_time);
	void Render();
};
