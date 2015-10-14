#include "Camera.h"
#include "GameGraphic.h"

CCamera::CCamera()
{
	positionX = 0;
	positionY = 750;
}

CCamera::~CCamera()
{
	
}

void CCamera::Render()
{

	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);

	int columnBegin = positionX / 50;
	for (int i = 0; i < 15; i++)
	{
		for (int j = columnBegin; j < columnBegin + 16; j++)
		{
			if (matrix[i][j] != 0)
			{
				int posX = j * 50;
				int posY = (15 - i) * 50;
				sprite->RenderMap(posX, posY, positionX, positionY, matrix[i][j]);
			}
		}
	}
}

void CCamera::Update(float x, float y)
{
	positionX = x - 375;
	if (positionX < 0) positionX = 0;
}