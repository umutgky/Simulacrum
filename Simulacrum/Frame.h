#pragma once
#include "wx/wx.h"
#include "SDL3/SDL.h"

class Frame : public wxFrame
{
public:
	Frame();
	~Frame();
	

private:
	SDL_Window* render_window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
};

