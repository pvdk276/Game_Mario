#include "GameObject.h"

CGameObject::CGameObject()
{

}

CGameObject::CGameObject(int id, int typeId, float positionX, float positionY, float width, float height)
{
	this->id = id;
	this->typeId = typeId;
	this->position.x = positionX;
	this->position.y = positionY;
	this->width = width;
	this->height = height;
}

CGameObject::~CGameObject()
{

}

CBox CGameObject::GetBox()
{
	CBox box(position.x, position.y, width, height, velocity.x, velocity.y);
	return box;
}
//void CGameObject::SetBound() {
//	m_bound.left = (LONG)(m_pos.x - m_sprite->GetSpriteWidth() / 2);
//	m_bound.bottom = (LONG)(m_pos.y - m_sprite->GetSpriteHeight() / 2);
//	m_bound.right = (LONG)(m_bound.left + m_sprite->GetSpriteWidth());
//	m_bound.top = (LONG)(m_bound.bottom + m_sprite->GetSpriteHeight() - 2);
//
//}
//void CGameObject::SetBound(RECT *r) {
//	m_bound.left = (LONG)r->left;//(LONG)m_pos.x - m_sprite->GetSpriteWidth()/2;
//	m_bound.bottom = (LONG)r->bottom;// (LONG)m_pos.y - m_sprite->GetSpriteHeight()/2;
//	m_bound.right = (LONG)r->right;//(LONG)(m_bound.left + m_sprite->GetSpriteWidth());
//	m_bound.top = (LONG)r->top;//(LONG)(m_bound.bottom + m_sprite->GetSpriteHeight());
//}

//void CGameObject::UpdatePosition(CInput *m_input, float _time) {
//
//	m_veloc += m_accel * _time;
//	m_pos += m_veloc * _time + 1.0f / 2 * m_accel*_time*_time;
//	SetBound();
//}