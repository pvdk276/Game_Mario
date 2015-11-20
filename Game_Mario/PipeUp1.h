#pragma once

#include "StaticObject.h"

class CPipeUp1 : public CStaticObject
{
public:
	CPipeUp1(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CPipeUp1();

	void Update(float delta_time);
	void Render();
};
