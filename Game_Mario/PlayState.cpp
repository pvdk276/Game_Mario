#include "PlayState.h"
#include "GameGraphic.h"

CPlayState::CPlayState()
{
	this->Init();
}

CPlayState::~CPlayState()
{
	if (CCamera::getInstance()) delete CCamera::getInstance();
	if (CMario::getInstance()) delete CMario::getInstance();
	if (CBinaryTree::getInstance()) delete CBinaryTree::getInstance();
	if (CGameGraphic::getInstance()) delete CGameGraphic::getInstance();
}

void CPlayState::Init()
{
	this->m_bFinished = false;
	//sprMenu = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Background.png", 800, 600, 1, 1, NULL);
	this->LoadResource();
	status = 0;
}

void CPlayState::LoadResource()
{
	//Khởi tạo Binary tree
	CBinaryTree::getInstance()->Init("Resources/Maps/map1_ListObject.txt", "Resources/Maps/map1_BinaryTree.txt");

	//Khởi tạo camera
	CCamera::getInstance()->matrix = CFileUtils::getInstance()->LoadMatrix(15, 166, "Resources/Maps/map1.txt");
	CCamera::getInstance()->m = 15;
	CCamera::getInstance()->n = 166;
	CCamera::getInstance()->sprite = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Maps/tiles.png", 50, 50, 216, 18, NULL);
	
	//Khởi tạo mario
	CMario::getInstance()->Init();

	//Phông nền
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/Background.png");
}

void CPlayState::Update(float deltaTime)
{
	CBinaryTree::getInstance()->listCurrentObject->clear();
	CBinaryTree::getInstance()->loadListCurrentObject(CBinaryTree::getInstance()->rootNode, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, CCamera::getInstance()->width, CCamera::getInstance()->height);
	
	//Update các đối tượng trong binary tree
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		CBinaryTree::getInstance()->listCurrentObject->at(i)->Update(deltaTime);
	}

	CMario::getInstance()->Update(deltaTime);
	CCamera::getInstance()->Update(CMario::getInstance()->position.x, CMario::getInstance()->position.y);
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_ESCAPE))
	{
		status = 1;
		this->End();	//Pause State
	}
	if (CMario::getInstance()->isDead)
	{
		status = 2;
		this->End();	//GameOver State
	}
}

void CPlayState::Render()
{
	CCamera::getInstance()->Render();
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		CBinaryTree::getInstance()->listCurrentObject->at(i)->Render();
	}

	CMario::getInstance()->Render();
	
}

void CPlayState::End()
{
	//Khi state kết thúc m_bFinished = true
	this->m_bFinished = true;
	//Xóa con trỏ m_pNextState
	delete m_pNextState;
	switch (status)
	{
	case 1:		
		m_pNextState = new CMenuState();
	break;
	case 2:
	{
		//delete CMario::getInstance();
		CMario::getInstance()->Reset();
		m_pNextState = new CGameOverState();
	}	
		break;
	default:
		m_pNextState = new CMenuState();
	}
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}

