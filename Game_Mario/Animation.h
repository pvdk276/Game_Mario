#pragma once
#include "Global.h"
class CAnimation
{
public:
	int curIndex;
	int beginIndex;
	int endIndex;
	float curTime;

	void UpdateAnimation(float delta_time, int beginIndex, int endIndex, int flag, float timeAnimation = TIME_ANIMATION);
};