#include "App.h"


wxIMPLEMENT_APP_NO_MAIN(App);

// Initialise SDL before WX-Widgets and GTK3

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Initialise SDL and Error Check
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL Initialisation Error\n\n";
	}

	return wxEntry();
}


App::App()
{

}

App::~App()
{

}

bool App::OnInit()
{
	int width = 800;
	int height = 600;

	frame = new Frame();
	frame->SetClientSize(wxSize(800, 600));
	frame->Center();

	frame->Show();

	return true;

}
