#pragma once

struct CBox
{
	float x, y;
	float w, h;
	float vx, vy;

	CBox()
	{
		x = y = 0.0f;
		w = h = 0.0f;
		vx = vy = 0.0f;
	}

	CBox(float posX, float posY, float Width, float Height, float vantocx, float vantocy)
	{
		x = posX;
		y = posY;
		w = Width;
		h = Height;
		vx = vantocx;
		vy = vantocy;
	}
};
