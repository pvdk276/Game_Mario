#pragma once


class CGameObject
{
public:
	int id;
	int typeId;
	float positionX;
	float positionY;
	float width;
	float height;

	CGameObject();

	CGameObject(int id, int typeId, float positionX, float positionY, float width, float height);

	virtual void Render() {}

};