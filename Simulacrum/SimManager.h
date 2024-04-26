#pragma once
#include "wx/wx.h"
#include "SDL3/SDL.h"
#include "State.h"
class SimManager : public wxTimer
{
public:

	SimManager(SDL_Renderer* rdr);
	~SimManager();

	void SwitchSim(State val);

	virtual void Notify();
private:

	State simState = None;

	SDL_Renderer* renderer;

	void MasterInit();
	void MasterUpdate();
	void MasterRender();

	int value = 1;

	bool isInitialised = false;
};

