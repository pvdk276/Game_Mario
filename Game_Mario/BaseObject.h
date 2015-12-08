#pragma once

#include "Box.h"
#include "Sprite.h"
#include "Global.h"
#include "Collision.h"
#include <string>
#include "Collision.h"
class CBaseObject
{
public:
	int id;
	ObjectName type;
	D3DXVECTOR2 position;
	float width;
	float height;
	CSprite* sprite;

	CBaseObject(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CBaseObject();
	
	virtual std::string GetType() = 0;
	virtual CBox GetBox() = 0;
	virtual void Render() {};
	virtual void Update(float delta_time) {};
};