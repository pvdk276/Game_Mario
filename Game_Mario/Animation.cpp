#include "Animation.h"

void CAnimation::UpdateAnimation(float delta_time, int spriteBegin, int spriteEnd, int flag, float timeAnimation)
{
	if (curTime >= timeAnimation)	//sau animationTime thì sẽ chuyển
	{
		if (flag == -1)
		{
			curIndex--;
			if (curIndex < spriteBegin) {
				curIndex = spriteEnd;
			}
			if (curIndex > spriteEnd) {
				curIndex = spriteEnd;
			}
		}
		if (flag == 1)
		{
			curIndex++;
			if (curIndex < spriteBegin) {
				curIndex = spriteBegin;
			}
			if (curIndex > spriteEnd) {
				curIndex = spriteBegin;
			}
		}
		curTime = 0;
	}
	else
	{
		curTime += delta_time;
	}
}
