#include "PlayState.h"
#include "GameGraphic.h"

CPlayState::CPlayState()
{
	this->Init();
}

CPlayState::~CPlayState()
{

}

void CPlayState::Init()
{
	this->m_bFinished = false;
	//sprMenu = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Background.png", 800, 600, 1, 1, NULL);
	this->LoadResource();
}

void CPlayState::LoadResource()
{
	CCamera::getInstance()->matrix = CFileUtils::getInstance()->LoadMatrix(15, 166, "Resources/Maps/map1.txt");
	CCamera::getInstance()->m = 15;
	CCamera::getInstance()->n = 166;
	CCamera::getInstance()->sprite = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Maps/tiles.png", 50, 50, 216, 18, NULL);

	CSprite* smallMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/SmallMario.png", 50, 50, 10, 5, NULL);
	CSprite* bigMario = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Mario/BigMario.png", 50, 100, 10, 5, NULL);
	//CMario::getInstance()->currentSprite = CMario::getInstance()->smallMario;
	CMario::getInstance()->Init(smallMario, bigMario, NULL);
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/Background.png");
}

void CPlayState::Update(float deltaTime)
{
	CBinaryTree::getInstance()->listCurrentObject->clear();
	CBinaryTree::getInstance()->loadListCurrentObject(CBinaryTree::getInstance()->rootNode, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, CCamera::getInstance()->width, CCamera::getInstance()->height);
	
	/*-------------------------------------------------------------
	begin demo
	---------------------------------------------------------------*/
	bool isCollision = false;

	/*for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == PIPE)
		{
			float normalx, normaly;
			float value = CCollision::getInstance()->CheckCollision(
				CMario::getInstance()->GetBox(),
				CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox(),
				normalx, normaly, deltaTime / 100);
			if (value < 1) //a collision occur
			{
				isCollision = true;
				break;
			}
		}
	}*/
	/*-------------------------------------------------------------
	end demo
	---------------------------------------------------------------*/
	
	for (int i = 0;i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
	{
		CBinaryTree::getInstance()->listCurrentObject->at(i)->Update(deltaTime / 100);
	}

	if(isCollision == false) CMario::getInstance()->Update(deltaTime / 100);
	CCamera::getInstance()->Update(CMario::getInstance()->position.x, CMario::getInstance()->position.y);
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_ESCAPE))
	{
		this->End();
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
	m_pNextState = new CMenuState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}

