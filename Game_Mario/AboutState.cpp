#include "AboutState.h"
#include "GameGraphic.h"


CAboutState::CAboutState()
{
	this->Init();
}


CAboutState::~CAboutState()
{
}

void CAboutState::Init()
{
	this->m_bFinished = false;
	this->LoadResource();
	position = -900;
}

void CAboutState::LoadResource()
{
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/background.jpg");
	m_sprite = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Name.png", 360, 600, 1, 1, NULL);
	SoundManagement::GetInstance()->Get(MENUMUSIC_SOUND)->Play();
}

void CAboutState::Update(float deltaTime)
{
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_ESCAPE))
	{
		this->End();
	}
	position += 100*deltaTime;
	if (position >= 300)
	{
		position = -900;
	}
	
}

void CAboutState::Render()
{
	
	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);
	m_sprite->Render(200, position, 0, 0, 0);
}

void CAboutState::End()
{
	SoundManagement::GetInstance()->Get(MENUMUSIC_SOUND)->Stop();
	this->m_bFinished = true;
	delete m_pNextState;
	m_pNextState = new CMenuState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}
