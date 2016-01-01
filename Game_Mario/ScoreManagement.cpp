#include "ScoreManagement.h"
#include "GameGraphic.h"
#include "Camera.h"

int CScoreManagement::Init()
{
	m_currentScore = 0;
	m_currentLife = LIFE;
	m_currentLevel = 1;
	m_pNumbers = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Number1.png", 30, 30, 10, 10, NULL);
	m_pMarioIcon = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/MarioIcon.png", 21, 22, 1, 1, NULL);
	m_pLevel = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/World.png", 62, 13, 1, 1, NULL);
	return 1;
}

void CScoreManagement::AddScore()
{
	m_currentScore += SCORE;
}

int CScoreManagement::SubtractLife()
{
	m_currentLife -= 1;
	return m_currentLife;
}

int CScoreManagement::AddLife()
{
	m_currentLife += 1;
	return m_currentLife;
}

int CScoreManagement::GetLife()
{
	return this->m_currentLife;
}

void CScoreManagement::SetLevel(int level)
{
	this->m_currentLevel = level;
}

int CScoreManagement::GetLevel()
{
	return this->m_currentLevel;
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
	m_pNumbers->Render(410, posy, 0.0f, 0.0f, m_currentLevel);
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
