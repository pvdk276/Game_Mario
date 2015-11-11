#pragma once

#include "StaticObject.h"

class CStone : public CStaticObject
{
public:
	CStone(CSprite* _stone, D3DXVECTOR2 _position);
	~CStone();

	void Render();
	void UpdateAnimation(float delta_time);
};
