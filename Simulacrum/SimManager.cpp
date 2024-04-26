#include "SimManager.h"

SimManager::SimManager(SDL_Renderer* rdr)
{
	this->renderer = rdr;
}

SimManager::~SimManager()
{
	SDL_DestroyRenderer(renderer);
}

void SimManager::SwitchSim(State val)
{
	simState = val;
	MasterInit();
}

void SimManager::Notify()
{
	if (!isInitialised)
	{
		MasterInit();
		isInitialised = true;
	}
	MasterUpdate();
	MasterRender();
	
}

void SimManager::MasterInit()
{
	switch (simState)
	{
	case None: // Initial empty state
		SDL_SetRenderDrawColor(renderer, 10, 200, 10, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		break;
	case GameOfLife:
		value = 0;
		break;
	case FlowField:
		break;
	default:
		break;
	}
}

void SimManager::MasterUpdate()
{
	switch (simState)
	{
	case None:
		break;
	case GameOfLife: // Gradient blue
		if (value < 255)
		{
			value++;
		}
		else
		{
			value = 0;
		}
	case FlowField:
		break;
	default:
		break;
	}
}

void SimManager::MasterRender()
{
	switch (simState)
	{
	case None:

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderLine(renderer, 0,300,600,300);
		SDL_RenderPresent(renderer);

		break;
	case GameOfLife: // Gradient blue
		SDL_SetRenderDrawColor(renderer, 0, 0, value, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	case FlowField:
		break;
	default:
		break;
	}
}
