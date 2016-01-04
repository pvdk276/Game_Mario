#include "GuideState.h"
#include "GameGraphic.h"


CGuideState::CGuideState()
{
	this->Init();
}


CGuideState::~CGuideState()
{
}

void CGuideState::Init()
{
	this->m_bFinished = false;
	this->LoadResource();
}

void CGuideState::LoadResource()
{
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/GuideBackground.png");
}

void CGuideState::Update(float deltaTime)
{
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_ESCAPE))
	{
		this->End();
	}
}

void CGuideState::Render()
{
	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);
}

void CGuideState::End()
{
	this->m_bFinished = true;
	delete m_pNextState;
	m_pNextState = new CMenuState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}
