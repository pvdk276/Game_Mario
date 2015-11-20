#pragma once

#include "StaticObject.h"
#include "Sprite.h"

class CBrick : public CStaticObject
{
private:
public:

	CBrick(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CBrick();

	void Update();
	void Render();
};
