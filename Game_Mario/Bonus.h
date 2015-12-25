#pragma once

#include "LivingObject.h"
#include "Global.h"

class CBonus : public CLivingObject
{
private:
	bool m_collisionX;
	bool m_collisionY;
	CBaseObject* m_pObject;
	D3DXVECTOR2 posOfBlock;

	void updatePosAnima(float delta_time);	//update position and Animation
public:
	CBonus(int id, ObjectName typeObj, D3DXVECTOR2 position, CSprite* sprite);
	~CBonus();

	void Update(float delta_time);
	void Render();
};