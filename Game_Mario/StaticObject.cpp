#include "StaticObject.h"

CStaticObject::CStaticObject(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite * sprite) : CBaseObject(type, position, width, height, sprite)
{

}

CStaticObject::~CStaticObject()
{

}

CBox CStaticObject::GetBox()
{
	CBox box(position.x, position.y, width, height, 0.0f, 0.0f);
	return box;
}

void CStaticObject::UpdateAnimation(float delta_time)
{
	sprite->SetCurrentIndex(0);
	sprite->UpdateSprite();
}

void CStaticObject::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

