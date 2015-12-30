#include "PlayState.h"
#include "GameGraphic.h"
#include "SoundManagement.h"

CPlayState::CPlayState(int idmap)
{
	id_map = idmap;
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
	CScoreManagement::getInstance()->Init();

}

void CPlayState::LoadResource()
{
	//Khởi tạo Binary tree
	switch (id_map)
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
	//CBinaryTree::getInstance()->Init("Resources/Maps/map1_ListObject.txt", "Resources/Maps/map1_BinaryTree.txt");

	//Khởi tạo camera
	/*CCamera::getInstance()->matrix = CFileUtils::getInstance()->LoadMatrix(15, 166, "Resources/Maps/map1.txt");
	CCamera::getInstance()->m = 15;
	CCamera::getInstance()->n = 166;*/
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
		status = 1;
		this->End();	//Pause State
	}
	if (CMario::getInstance()->isDead)
	{
		status = 2;
		this->End();	//GameOver State
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

