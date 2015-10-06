#include "Mario.h"
#include "Camera.h"

CMario::CMario()
{
	positionX = 20;
	positionY = 125;

	speedX = 0;
	speedY = 0;

	currentSprite = smallMario;

	state = STANDING;

	gravity = 0.08f;
}

CMario::~CMario()
{

}

void CMario::Render()
{
	smallMario->Render(positionX, positionY, CCamera::getInstance()->positionX, CCamera::getInstance()->positionY, 1);
}

void CMario::Update(float delta_time)
{
	positionX += speedX * delta_time;
	//MessageBox(NULL, "Cannot set property keyboard", "Error", MB_OK);
	//positionY += speedY * delta_time;
}