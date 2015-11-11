#pragma once

#include "StaticObject.h"
#include "Global.h"

class CMushroomBlock : public CStaticObject
{
public:
	CMushroomBlock(CSprite* _mushroom, D3DXVECTOR2 _position);
	~CMushroomBlock();

	void Render();
	void UpdateAnimation(float delta_time);
};
