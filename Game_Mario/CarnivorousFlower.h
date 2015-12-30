#pragma once
#include "LivingObject.h"
#include "Mario.h"

enum Direction
{
	NONE = 0,
	LEFT = 0x01,
	JUMP = 0x02,
	RIGHT = 0x04,
	FALL = 0x08
};
class CCarnivorousFlower : public CLivingObject
{
private:
	float m_posPosition;
	float m_counter;
public:
	CCarnivorousFlower(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CCarnivorousFlower();
	
	void Update(float delta_time);
	void Render();
};
