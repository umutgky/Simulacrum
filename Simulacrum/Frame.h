#pragma once
#include "wx/wx.h"
#include "SDL3/SDL.h"
#include "SimManager.h"
#include "State.h"
#include <wx/simplebook.h>
#include <wx/wrapsizer.h>

class Frame : public wxFrame
{
public:
	Frame();
	~Frame();
	

private:
	SDL_Window* render_window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::unique_ptr<SimManager> simManager;

	wxSimplebook* sideBook = nullptr;

	void SwitchSimState(wxCommandEvent& evt);
};

