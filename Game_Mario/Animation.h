#pragma once

class CAnimation
{
public:
	int curIndex;
	int beginIndex;
	int endIndex;
	float animationTime;
	float curTime;

	void UpdateAnimation(float delta_time, int beginIndex, int endIndex, int flag);
};