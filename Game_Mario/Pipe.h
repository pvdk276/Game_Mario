#pragma once

#include "StaticObject.h"

class CPipe : public CStaticObject
{
public:
	CPipe(CSprite* _mushroom, D3DXVECTOR2 _position);
	~CPipe();

	void Render();
	void UpdateAnimation(float delta_time);
};
