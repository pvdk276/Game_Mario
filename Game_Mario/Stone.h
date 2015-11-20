#pragma once

#include "StaticObject.h"

class CStone : public CStaticObject
{
public:
	CStone(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CStone();

	void Update();
	void Render();
};
