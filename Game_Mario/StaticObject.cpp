#include "StaticObject.h"

CStaticObject::CStaticObject(int id, D3DXVECTOR2 position, CSprite* sprite) : CBaseObject(id, position, sprite)
{

}

CStaticObject::~CStaticObject()
{

}

CBox CStaticObject::GetBox()
{
	CBox box(position.x, position.y, width, height, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	return box;
}

std::string CStaticObject::GetType()
{
	return "StaticObject";
}