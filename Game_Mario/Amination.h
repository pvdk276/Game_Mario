#pragma once
class CAmination
{
public:
	int curSprite;
	int beginSprite;
	int endSprite;
	float timeAmination;
	float timecurrent;
	int spritePerRow;
	int totalSprite;
	int GetCurrentSprite();
	CAmination();
	~CAmination();
};

