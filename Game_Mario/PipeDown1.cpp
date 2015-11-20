#include "PipeDown1.h"

CPipeDown1::CPipeDown1(int id, D3DXVECTOR2 position, CSprite* sprite) : CStaticObject(id, position, sprite)
{
	this->type = PIPE;
	this->width = 100;
	this->height = 150;
}

CPipeDown1::~CPipeDown1()
{

}

void CPipeDown1::Update()
{

}

void CPipeDown1::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}