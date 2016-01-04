#include "MenuState.h"
#include "GameGraphic.h"

CMenuState::CMenuState()
{
	this->m_indexMenu = 0;
	this->m_bFinished = false;
	this->LoadResource();
	//this->Init();
}

CMenuState::~CMenuState()
{
	if (sprMenu)
		delete sprMenu;
}

void CMenuState::Init()
{
	
}

void CMenuState::LoadResource()
{
	sprMenu = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/StartMenu2.png", 360, 120, 8, 2, NULL);
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/StartScreen.jpg");
	SoundManagement::GetInstance()->Get(MENUMUSIC_SOUND)->PlayLoop();
}

void CMenuState::Update(float deltaTime)
{
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		this->m_keyDown = true;
	}
	if (CGameKeyboard::getInstance()->IsKeyUp(DIK_DOWN) == true)
	{
		if (this->m_keyDown == true && m_indexMenu < 3)
		{
			m_indexMenu++;
			SoundManagement::GetInstance()->Get(MENUCHANGE_SOUND)->Play();
		}	
		this->m_keyDown = false;
	}

	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_UP))
	{
		this->m_keyUp = true;
	}
	if (CGameKeyboard::getInstance()->IsKeyUp(DIK_UP))
	{
		if (this->m_keyUp == true && m_indexMenu > 0)
		{
			m_indexMenu--;
			SoundManagement::GetInstance()->Get(MENUCHANGE_SOUND)->Play();
		}	
		this->m_keyUp = false;
	}

	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RETURN))
	{
		SoundManagement::GetInstance()->Get(SMALLER_SOUND)->Play();
		this->End();
	}
}

void CMenuState::Render()
{
	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);
	sprMenu->Render(200, -200, 0, 0, 0);
	if(this->m_indexMenu == 0)
		sprMenu->Render(200, -200, 0, 0, 1);
	sprMenu->Render(200, -300, 0, 0, 2);
	if (this->m_indexMenu == 1)
		sprMenu->Render(200, -300, 0, 0, 3);
	sprMenu->Render(200, -400, 0, 0, 4);
	if (this->m_indexMenu == 2)
		sprMenu->Render(200, -400, 0, 0, 5);
	sprMenu->Render(200, -500, 0, 0, 6);
	if (this->m_indexMenu == 3)
		sprMenu->Render(200, -500, 0, 0, 7);	
}

void CMenuState::End()
{
	this->m_bFinished = true;
	delete m_pNextState;
	switch (m_indexMenu)
	{
	case 0:
	{
		CMario::getInstance()->Reset();
		CScoreManagement::getInstance()->SetLife(LIFE);
		m_pNextState = new CPlayState();
	}
	break;
	case 1:
	{
		m_pNextState = new CGuideState();
	}
	break;
	case 2:
	{
		m_pNextState = new CAboutState();
	}
	break;
	case 3:
	{
		exit(0);
	}
	break;
	default:
		break;
	}	
	SoundManagement::GetInstance()->Get(MENUMUSIC_SOUND)->Stop();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}

