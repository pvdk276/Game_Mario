#include "ScoreManagement.h"
#include "GameGraphic.h"
#include "Camera.h"

void CScoreManagement::Init()
{
	currentScore = 0;
	numbers = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Number1.png", 30, 30, 10, 10, NULL);
}

void CScoreManagement::AddScore()
{
	currentScore += SCORE;
}

void CScoreManagement::Update()
{
	
}

void CScoreManagement::Render()
{
	int posx = 20;
	int posy = -20;
	numbers->Render(posx, posy, 0.0f, 0.0f, currentScore/100);
	numbers->Render(posx + 30, posy, 0.0f, 0.0f, (currentScore/10)%10);
	numbers->Render(posx + 60, posy, 0.0f, 0.0f, currentScore%10);
	numbers->Render(posx + 90, posy, 0.0f, 0.0f, 0);
	numbers->Render(posx + 120, posy, 0.0f, 0.0f, 0);
}

CScoreManagement::~CScoreManagement()
{
	if (numbers != NULL)
		delete numbers;
}
