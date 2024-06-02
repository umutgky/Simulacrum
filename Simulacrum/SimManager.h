#pragma once
#include "wx/wx.h"
#include "SDL3/SDL.h"
#include "State.h"
#include <vector>
#include "Cell.h"
class SimManager : public wxTimer
{
public:

	SimManager(SDL_Renderer* rdr, int width = 0, int height = 0);
	~SimManager();

	void SwitchSim(State val);
	void TogglePause();
	virtual void Notify();
	void MasterInit();
	
private:

	const int width;
	const int height;

	bool isPaused = false;

	State simState = None;

	SDL_Renderer* renderer;

	
	void MasterUpdate();
	void MasterRender();

	bool isInitialised = false;

	// GoL Variables
	const int GoLScale = 20;
	const int GoLGridWidth;
	const int GoLGridHeight;
	std::vector<std::vector<Cell>> GoLGrid;
};

