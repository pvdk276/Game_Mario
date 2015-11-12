#include "DynamicObject.h"

CDynamicObject::CDynamicObject(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite* sprite, float timeAnimation) :CBaseObject(type, position, width, height, sprite)
{
	this->timeAnimation = timeAnimation;
}

CDynamicObject::~CDynamicObject()
{

}

void CDynamicObject::UpdateAnimation(float delta_time)
{
	sprite->SetTimeAnimation(timeAnimation);
	sprite->UpdateSprite(delta_time, 0, sprite->count - 1, 1);
}

void CDynamicObject::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}
