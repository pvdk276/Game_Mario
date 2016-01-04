#include "PlayState.h"
#include "GameGraphic.h"
#include "SoundManagement.h"

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
	m_id_map = CScoreManagement::getInstance()->GetLevel();
	this->m_bFinished = false;
	this->LoadResource();
	m_status = 0;

}

void CPlayState::LoadResource()
{
	//Khởi tạo Binary tree
	switch (m_id_map)
	{
	case 1: 
		CBinaryTree::getInstance()->Init("Resources/Maps/map1_ListObject.txt", "Resources/Maps/map1_BinaryTree.txt");

		CCamera::getInstance()->matrix = CFileUtils::getInstance()->LoadMatrix(15, 173, "Resources/Maps/map1.txt");
		CCamera::getInstance()->m = 15;
		CCamera::getInstance()->n = 173;
		break;
	case 2:
		CBinaryTree::getInstance()->Init("Resources/Maps/map2_ListObject.txt", "Resources/Maps/map2_BinaryTree.txt");

		CCamera::getInstance()->matrix = CFileUtils::getInstance()->LoadMatrix(15, 207, "Resources/Maps/map2.txt");
		CCamera::getInstance()->m = 15;
		CCamera::getInstance()->n = 207;
		break;
	case 3:
		CBinaryTree::getInstance()->Init("Resources/Maps/map3_ListObject.txt", "Resources/Maps/map3_BinaryTree.txt");

		CCamera::getInstance()->matrix = CFileUtils::getInstance()->LoadMatrix(15, 166, "Resources/Maps/map3.txt");
		CCamera::getInstance()->m = 15;
		CCamera::getInstance()->n = 166;
		break;
	default: 
		break;
	}

	CCamera::getInstance()->sprite = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Maps/tiles.png", 50, 50, 216, 18, NULL);
	
	//Khởi tạo mario
	CMario::getInstance()->Init();

	//Phông nền
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/Background.png");

	SoundManagement::GetInstance()->Get(BACKMUSIC_SOUND)->PlayLoop();
}

void CPlayState::Update(float deltaTime)
{
	CBinaryTree::getInstance()->listCurrentObject->clear();
	CBinaryTree::getInstance()->loadListCurrentObject(CBinaryTree::getInstance()->rootNode, CMario::getInstance()->position.x, CMario::getInstance()->position.y, 2000, CCamera::getInstance()->height);
	
	//Update các đối tượng trong binary tree
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		CBinaryTree::getInstance()->listCurrentObject->at(i)->Update(deltaTime);
	}

	CMario::getInstance()->Update(deltaTime);
	CCamera::getInstance()->Update(CMario::getInstance()->position.x, CMario::getInstance()->position.y);

	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_ESCAPE))
	{
		m_status = 1;
		this->End();	//Pause State
	}
	if (CMario::getInstance()->isDead)
	{
		m_status = 2;
		this->End();	//GameOver State
	}
	if (CMario::getInstance()->isWin && m_id_map < 3)
	{
		m_status = 3;	//ChangeLevel
		this->End();
	}
	if (CMario::getInstance()->isWin && m_id_map == 3)
	{
		m_status = 4;	//winerstate
		this->End();
	}
	//score
	CScoreManagement::getInstance()->Update();
}

void CPlayState::Render()
{
	
	CCamera::getInstance()->Render();
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		CBinaryTree::getInstance()->listCurrentObject->at(i)->Render();
	}

	CMario::getInstance()->Render();

	//score
	CScoreManagement::getInstance()->Render();
	
}

void CPlayState::End()
{	
	//Xóa con trỏ m_pNextState
	delete m_pNextState;

	switch (m_status)
	{
	case 1:	
		m_pNextState = new CMenuState();
	break;
	case 2:
	{
		m_pNextState = new CGameOverState();
	}	
	break;
	case 3:
	{
		int idmap = m_id_map + 1;
		CMario::getInstance()->Reset();
		CScoreManagement::getInstance()->SetLevel(idmap);
		m_pNextState = new CPlayState();
	}
	break;
	case 4:
	{
		m_pNextState = new CWinnerState();
	}
	break;
	default:
		m_pNextState = new CMenuState();
	break;
	}
	SoundManagement::GetInstance()->Get(BACKMUSIC_SOUND)->Stop();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}

