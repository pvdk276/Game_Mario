#pragma once


class GameObject
{
public:
	int id;
	int typeId;
	float positionX;
	float positionY;
	float width;
	float height;

	GameObject();

	GameObject(int id, int typeId, float positionX, float positionY, float width, float height);

	virtual void Render() {}

};