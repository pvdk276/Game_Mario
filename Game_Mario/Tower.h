#pragma once

#include "StaticObject.h"
#include "Sprite.h"

class CTower : public CStaticObject
{
public:
	CTower(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CTower();

	void Update(float delta_time);
	void Render();
};