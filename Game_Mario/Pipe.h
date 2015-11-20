#pragma once

#include "StaticObject.h"

class CPipe : public CStaticObject
{
public:
	CPipe(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CPipe();

	void Update(float delta_time);
	void Render();
};
