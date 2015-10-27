#pragma once

#include "Box.h"

class CGameObject
{
public:
	int id;
	int typeId;
	float positionX;
	float positionY;
	float width;
	float height;
	float speedX;
	float speedY;

	CGameObject();

	CGameObject(int id, int typeId, float positionX, float positionY, float width, float height);

	virtual void Render() {}
	CBox GetBox();
};