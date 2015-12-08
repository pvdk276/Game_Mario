#pragma once

#include "DynamicObject.h"
#include"Mushroom.h"
#include "Coin.h"
#include "Flower.h"

class CSecretBlock : public CDynamicObject
{
public:
	CMushroom *mushroom;
	CCoin *coin;
	CFlower *flower;
	CSecretBlock(int id, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2, CSprite* sprite3, CSprite* sprite4, CSprite* sprite5);
	~CSecretBlock();

	void Update(float delta_time);
	void Render();
};
