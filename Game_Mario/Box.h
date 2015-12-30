#pragma once

struct CBox
{
	float x, y;
	float w, h;
	float vx, vy;
	float ax, ay;
	float tx, ty;

	CBox()
	{
		x = y = 0.0f;
		w = h = 0.0f;
		vx = vy = 0.0f;
		ax = ay = 0.0f;
		tx = ty = 0.0f;
	}

	CBox(float posX, 
		float posY, 
		float Width, 
		float Height, 
		float vantocx, 
		float vantocy, 
		float giatocX, 
		float giatocY, 
		float timerX, 
		float timerY)
	{
		x = posX;
		y = posY;
		w = Width;
		h = Height;
		vx = vantocx;
		vy = vantocy;
		ax = giatocX;
		ay = giatocY;
		tx = timerX;
		ty = timerY;
	}
};
