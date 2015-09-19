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
	CGameGraphic::getInstance()->d3ddv->StretchRect(
		CGameGraphic::getInstance()->surface,			// from 
		NULL,				// which portion?
		CGameGraphic::getInstance()->backBuffer,			// to 
		NULL,				// which portion?
		D3DTEXF_NONE);


	int columnBegin = positionX / 50;
	for (int i = 0; i < 15; i++)
	{
		for (int j = columnBegin; j < columnBegin + 16; j++)
		{
			if (matrix[i][j] != 0)
			{
				//MessageBox(NULL, "value != 0", "Error", MB_OK);
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