#include "GameOverState.h"
#include "GameGraphic.h"

CGameOverState::CGameOverState()
{
	this->Init();
}


CGameOverState::~CGameOverState()
{
}

void CGameOverState::Init()
{
	this->m_bFinished = false;
	this->m_isGameOver = false;
	this->m_timer = 0.0f;
	this->LoadResource();
	if(CScoreManagement::getInstance()->GetLife() >= 1)
		m_Life = CScoreManagement::getInstance()->SubtractLife();
}

void CGameOverState::LoadResource()
{
	m_pNumbers = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Number2.png", 50, 50, 10, 10, NULL);
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/WaitScreen.png");
}

void CGameOverState::Update(float deltaTime)
{
	if (m_Life != 0)
	{
		if (CGameKeyboard::getInstance()->IsKeyDown(DIK_SPACE))
		{
			this->End();
		}
	}
	else //game over
	{
		m_timer += deltaTime;
		if (m_timer >= deltaTime * GAME_FPS)
		{
			m_isGameOver = true;
			CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/GameOverScreen.png");
			if(m_timer >= deltaTime * GAME_FPS * 4) this->End();
		}
	}
}

void CGameOverState::Render()
{
	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);
	if(!m_isGameOver) m_pNumbers->Render(395,-370,0.0f,0.0f,m_Life);
}

void CGameOverState::End()
{
	this->m_bFinished = true;
	delete m_pNextState;
	if (m_Life == 0)
		m_pNextState = new CMenuState();
	else
	{
		CMario::getInstance()->Resume();
		m_pNextState = CPlayState::getInstance();
	}
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}