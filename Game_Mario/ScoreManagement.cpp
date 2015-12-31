#include "ScoreManagement.h"
#include "GameGraphic.h"
#include "Camera.h"

void CScoreManagement::Init()
{
	m_currentScore = 0;
	m_currentLife = LIFE;
	m_pNumbers = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Number1.png", 30, 30, 10, 10, NULL);
	m_pMarioIcon = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/MarioIcon.png", 21, 22, 1, 1, NULL);
	m_pLevel = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/World.png", 62, 13, 1, 1, NULL);
}

void CScoreManagement::AddScore()
{
	m_currentScore += SCORE;
}

void CScoreManagement::SubtractLife()
{
	m_currentLife -= 1;
}

void CScoreManagement::AddLife()
{
	m_currentLife += 1;
}

void CScoreManagement::Update()
{
	
}

void CScoreManagement::Render()
{
	//Hiển thị Điểm
	int posx = 20;
	int posy = -20;
	m_pNumbers->Render(posx, posy, 0.0f, 0.0f, m_currentScore/100);
	m_pNumbers->Render(posx + 30, posy, 0.0f, 0.0f, (m_currentScore/10)%10);
	m_pNumbers->Render(posx + 60, posy, 0.0f, 0.0f, m_currentScore%10);
	m_pNumbers->Render(posx + 90, posy, 0.0f, 0.0f, 0);
	m_pNumbers->Render(posx + 120, posy, 0.0f, 0.0f, 0);

	//Hiển thị Mạng
	m_pMarioIcon->Render(700, posy, 0.0f, 0.0f, 0);
	m_pNumbers->Render(730, posy, 0.0f, 0.0f, m_currentLife);
	//Hiển thị Level
	m_pLevel->Render(350, posy, 0.0f, 0.0f, 0);
}

CScoreManagement::~CScoreManagement()
{
	if (m_pNumbers != NULL)
		delete m_pNumbers;
	if (m_pLevel)
		delete m_pLevel;
	if (m_pMarioIcon)
		delete m_pMarioIcon;

}
