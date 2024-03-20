#pragma once
#define SDL_MAIN_HANDLED
#include "wx/wx.h"
#include "SDL3/SDL.h"
#include "Frame.h"

class App : public wxApp
{
public:
	App();
	~App();

private:

	Frame* frame = nullptr;



public:
	virtual bool OnInit();
};

