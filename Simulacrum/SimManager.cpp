#include "SimManager.h"

SimManager::SimManager(SDL_Renderer* rdr, int width, int height) : width{ width }, height{ height }, GoLGridWidth{width/GoLScale}, GoLGridHeight{ height / GoLScale }
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
		for (int x = 0; x < GoLGridWidth; x++)
		{
			std::vector<Cell> col;
			for (int y = 0; y < GoLGridHeight; y++)
			{
				col.push_back(Cell(rand()%2, x * GoLScale, y * GoLScale, GoLScale, GoLScale));
			}
			GoLGrid.push_back(col);
		}

		break;
	case FlowField:
		SDL_SetRenderDrawColor(renderer, 10, 200, 10, 255);

		
		SDL_RenderClear(renderer);


		break;
	default:
		break;
	}
}

void SimManager::MasterUpdate()
{
	std::vector<std::vector<int>> GoLTempValGrid;
	if (!isPaused)
	{
		switch (simState)
		{
		case None:
			break;
		case GameOfLife:
			//create temp grid
			
			for (int x = 0; x < GoLGridWidth; x++)
			{
				std::vector<int> col;
				for (int y = 0; y < GoLGridHeight; y++)
				{
					col.push_back(0);
				}
				GoLTempValGrid.push_back(col);
			}

			// Loop Over and Calculate New Values
			for (int x = 0; x < GoLGridWidth; x++)
			{

				for (int y = 0; y < GoLGridHeight; y++)
				{
					int nCount = 0;
					for (int ix = -1; ix <= 1; ix++)
					{
						for (int iy = -1; iy <= 1; iy++)
						{
							if (x + ix >= 0 && x + ix < GoLGridWidth && y + iy >= 0 && y + iy < GoLGridHeight && !(ix == 0 && iy == 0))
							{

								nCount += GoLGrid[x+ix][y+iy].val;
							}
						}
					}
					
					GoLTempValGrid[x][y] = nCount;
				}

			}

			for (int x = 0; x < GoLGridWidth; x++)
			{
				for (int y = 0; y < GoLGridHeight; y++)
				{
					if (GoLGrid[x][y].val == 1)
					{
						if (GoLTempValGrid[x][y] < 2 || GoLTempValGrid[x][y] >3)
						{
							GoLGrid[x][y].val = 0;
						}
					} 
					else
					{
						if (GoLTempValGrid[x][y] == 3)
						{
							GoLGrid[x][y].val = 1;
						}
					}

				}

			}

			break;
		case FlowField:
			break;
		default:
			break;
		}
	}
	
}

void SimManager::MasterRender()
{
	switch (simState)
	{
	case None:

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		break;
	case GameOfLife: // Gradient blue
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		// Loop Over and Render Grid
		for (int x = 0; x < GoLGridWidth; x++)
		{
			
			for (int y = 0; y < GoLGridHeight; y++)
			{
				SDL_SetRenderDrawColor(renderer, 20, 180, 20, 255);
				if (GoLGrid[x][y].val == 0)
				{
					//SDL_RenderRect(renderer, &GoLGrid[x][y]);
				} 
				else 
				{
					SDL_RenderFillRect(renderer, &GoLGrid[x][y]);
				}

			}
			
		}
		
		SDL_RenderPresent(renderer);
		break;
	case FlowField:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		if (width == 600)
		{
			SDL_SetRenderDrawColor(renderer, 200, 10, 10, 255);
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		break;
	default:
		break;
	}
}

void SimManager::TogglePause()
{
	isPaused = !isPaused;
}
