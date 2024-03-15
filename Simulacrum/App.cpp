#include "App.h"


wxIMPLEMENT_APP(App);

App::App()
{

}

App::~App()
{

}

bool App::OnInit()
{
	frame = new Frame();
	frame->SetClientSize(wxSize(800, 600));
	frame->Center();

	frame->Show();

	return true;

}
