#pragma once
#include "GameKeyboard.h"
//#include "GameGraphic.h"

class CBaseGameState
{
private:
	CBaseGameState* m_nextState;
protected:
	virtual void Update(float deltaTime) = 0;

	virtual void Render() = 0;

public:
	CBaseGameState();
	~CBaseGameState();

	virtual void Init() = 0;
	virtual void LoadResource() = 0;
	void Run(float deltaTime);
	virtual void End() = 0;
	//Bi?n ki?m tra State ?ã k?t thúc ch?a
	bool m_bFinished;
	//Bi?n ch?a con tr? c?a state ti?p theo
	CBaseGameState* m_pNextState;
};

