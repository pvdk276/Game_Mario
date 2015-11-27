#include "PipeUp1.h"

CPipeUp1::CPipeUp1(int id, D3DXVECTOR2 position, CSprite* sprite) : CStaticObject(id, position, sprite)
{
	this->type = PIPE;
	this->width = 100;
	this->height = 150;
}

CPipeUp1::~CPipeUp1()
{

}

void CPipeUp1::Update(float delta_time)
{
}

void CPipeUp1::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}
