#include "Stone.h"

CStone::CStone(int id, D3DXVECTOR2 position, CSprite* sprite) : CStaticObject(id, position, sprite)
{
	this->type = STONE;
	this->width = 50;
	this->height = 50;
}

CStone::~CStone()
{
}

void CStone::Update()
{

}

void CStone::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}