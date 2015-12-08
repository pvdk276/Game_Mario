#pragma once

#include "DynamicObject.h"

class CMushroom : public CDynamicObject
{
public:
	CMushroom(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CMushroom();

	void Update(float delta_time);
	void Render();
};
