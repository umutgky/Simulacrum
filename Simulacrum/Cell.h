#pragma once
#include "SDL3/SDL.h"
struct Cell : SDL_FRect
{
	int val;
	Cell(int v, int xpos, int ypos, int width, int height)
	{
		val = v;
		x = xpos;
		y = ypos;
		w = width;
		h = height;
	}
};