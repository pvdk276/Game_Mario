﻿#pragma once

#include "DynamicObject.h"
#include "Bonus.h"

class CBlock : public CDynamicObject
{
private:
	float pos;	//lưu tọa độ cũ của brick
	int direct; //biến xét chiều di chuyển viên gạch
	int numberCoin; // Số tiền
	int count; //đếm số lần va chạm
	CBonus* bonus;
	CSprite* sprite2;
	bool isBonus;
	bool isBlock;
public:
	CBlock(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2);
	~CBlock();

	void Update(float delta_time);
	void Render();
};
