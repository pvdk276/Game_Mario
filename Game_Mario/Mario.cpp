#include "Mario.h"
#include "Camera.h"

CMario::CMario()
{
	positionX = 20;
	positionY = 125;

	currentSprite = smallMario;
}

CMario::~CMario()
{

}

void CMario::Render()
{
	smallMario->Render(positionX, positionY, CCamera::getInstance()->positionX, CCamera::getInstance()->positionY, lastSpeedX);
}

void CMario::Update(float delta_time)
{
	positionX += speedX * delta_time;
	positionY += speedY * delta_time;
}