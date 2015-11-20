#pragma once

#include "StaticObject.h"

class CPipeDown1 : public CStaticObject
{
public:
	CPipeDown1(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CPipeDown1();

	void Update();
	void Render();
};
