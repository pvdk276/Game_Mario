#pragma once

#include "StaticObject.h"
#include "Sprite.h"

class CBrick : public CStaticObject
{
private:
public:

	CBrick(CSprite *brick,D3DXVECTOR2 _position);
	~CBrick();

	void Render();
	void UpdateAnimation(float delta_time);
};
