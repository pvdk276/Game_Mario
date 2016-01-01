#pragma once

#include "StaticObject.h"
#include "Sprite.h"

class CTank : public CStaticObject
{
public:
	CTank(int id, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2);
	~CTank();

	void Update(float delta_time);
	void Render();

	CSprite* bullet;
};