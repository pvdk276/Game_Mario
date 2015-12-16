#include "MenuState.h"
#include "GameGraphic.h"


CMenuState::CMenuState()
{
	
	this->Init();
}

CMenuState::~CMenuState()
{

}

void CMenuState::Init()
{
	this->m_indexMenu = 0;
	this->m_bFinished = false;
	this->LoadResource();
}

void CMenuState::LoadResource()
{
	sprMenu = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/StartMenu.png", 200.5, 56.2, 10, 2, NULL);
}

void CMenuState::Update(float deltaTime)
{
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		this->m_keyDown = true;
	}
	if (CGameKeyboard::getInstance()->IsKeyUp(DIK_DOWN) == true)
	{
		if(this->m_keyDown == true && m_indexMenu < 4)
			m_indexMenu++;
		this->m_keyDown = false;
	}

	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_UP))
	{
		this->m_keyUp = true;
	}
	if (CGameKeyboard::getInstance()->IsKeyUp(DIK_UP))
	{
		if (this->m_keyUp == true && m_indexMenu > 0)
			m_indexMenu--;
		this->m_keyUp = false;
	}

	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_RETURN))
	{
		this->End();
	}
}

void CMenuState::Render()
{
	sprMenu->Render(200, -200, 0, 0, 0);
	if(this->m_indexMenu == 0)
		sprMenu->Render(200, -200, 0, 0, 1);
	sprMenu->Render(200, -250, 0, 0, 2);
	if (this->m_indexMenu == 1)
		sprMenu->Render(200, -250, 0, 0, 3);
	sprMenu->Render(200, -300, 0, 0, 4);
	if (this->m_indexMenu == 2)
		sprMenu->Render(200, -300, 0, 0, 5);
	sprMenu->Render(200, -350, 0, 0, 6);
	if (this->m_indexMenu == 3)
		sprMenu->Render(200, -350, 0, 0, 7);
	sprMenu->Render(200, -400, 0, 0, 8);
	if (this->m_indexMenu == 4)
		sprMenu->Render(200, -400, 0, 0, 9);
}

void CMenuState::End()
{
	this->m_bFinished = true;
	delete m_pNextState;
	m_pNextState = new CPlayState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}

