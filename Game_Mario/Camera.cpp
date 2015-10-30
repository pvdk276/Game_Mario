#include "Camera.h"
#include "GameGraphic.h"

CCamera::CCamera()
{
	position.x = 0;
	position.y = 750;
}

CCamera::~CCamera()
{
	
}

void CCamera::Render()
{

	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);

	int columnBegin = position.x / 50;
	for (int i = 0; i < 15; i++)
	{
		for (int j = columnBegin; j < columnBegin + 16; j++)
		{
			if (matrix[i][j] != 0)
			{
				int posX = j * 50;
				int posY = (15 - i) * 50;
				sprite->RenderMap(posX, posY, position.x, position.y, matrix[i][j]);
			}
		}
	}
}

void CCamera::Update(float x, float y)
{
	position.x = x - 375;
	if (position.x < 0) position.x = 0;
}