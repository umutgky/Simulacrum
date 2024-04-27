#pragma once
#include "wx/wx.h"
#include "SDL3/SDL.h"
#include "State.h"
class SimManager : public wxTimer
{
public:

	SimManager(SDL_Renderer* rdr, int width = 0, int height = 0);
	~SimManager();

	void SwitchSim(State val);
	void TogglePause();
	virtual void Notify();
private:

	int width;
	int height;

	bool isPaused = false;

	State simState = None;

	SDL_Renderer* renderer;

	void MasterInit();
	void MasterUpdate();
	void MasterRender();

	

	int value = 1;

	bool isInitialised = false;
};

