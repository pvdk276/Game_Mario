#include "WinnerState.h"
#include "GameGraphic.h"

CWinnerState::CWinnerState()
{
	this->m_bFinished = false;
	this->LoadResource();
	//this->Init();
}

CWinnerState::~CWinnerState()
{
	if (sprFireWork)
		delete sprFireWork;
}

void CWinnerState::Init()
{

}

void CWinnerState::LoadResource()
{
	sprFireWork = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Fireworks.png", 93, 25, 3, 3, NULL);
	//Phông nền
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/Winner.png");
}

void CWinnerState::Update(float delta_time)
{
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RETURN))
	{
		this->End();
	}

	CAnimation::UpdateAnimation(delta_time, 0, 2, 1, 0.2f);
}

void CWinnerState::Render()
{
	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);
	sprFireWork->Render(100, -200, 0.0f, 0.0f, curIndex);
}

void CWinnerState::End()
{
	this->m_bFinished = true;
	delete m_pNextState;
	m_pNextState = new CMenuState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}

