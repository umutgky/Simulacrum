#include "Frame.h"



Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Simulacrum")
{
	// Create the Menu bar
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* simsMenu = new wxMenu();
	wxMenu* pauseMenu = new wxMenu();
	wxMenu* resetMenu = new wxMenu();

	simsMenu->AppendRadioItem(None, _("None"));
	simsMenu->AppendRadioItem(GameOfLife, _("Game Of Life"));
	simsMenu->AppendRadioItem(FlowField, _("Flow Field"));

	menuBar->Append(simsMenu, "Simulations");
	menuBar->Append(pauseMenu, "Pause");
	menuBar->Append(resetMenu, "Reset");
	
	SetMenuBar(menuBar);
	simsMenu->Bind(wxEVT_MENU, &Frame::SwitchSimState, this);
	pauseMenu->Bind(wxEVT_MENU_OPEN, &Frame::PauseSim, this);
	resetMenu->Bind(wxEVT_MENU_OPEN, &Frame::ResetSim, this);

	// Create Rendering Context
	wxPanel* renderPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 600));
	render_window = SDL_CreateWindowFrom((void*)renderPanel->GetHandle());
	if (render_window != NULL) {
		renderer = SDL_CreateRenderer(render_window, NULL, SDL_RENDERER_ACCELERATED);
	}
	// Create Sim Manager
	simManager = std::make_unique<SimManager>(renderer, 600, 600);
	
	// Create Side Panel
	sideBook = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxSize(200,600));

	// Create Side Panel - None
	wxPanel* sidePanelNone = new wxPanel(sideBook, wxID_ANY);
	sidePanelNone->SetBackgroundColour(wxColor(0, 0, 255));
	sideBook->ShowNewPage(sidePanelNone);

	// Create Side Panel - Game Of Life
	wxPanel* sidePanelGoF = new wxPanel(sideBook, wxID_ANY, wxDefaultPosition);
	sidePanelGoF->SetBackgroundColour(wxColor(0, 255, 255));

	//wxButton* btnResetGoF = new wxButton(sidePanelGoF, wxID_ANY, _("Reset"), wxDefaultPosition, wxSize(200,40));
	//wxBoxSizer* sideSizerGoF = new wxBoxSizer(wxVERTICAL);
	//sideSizerGoF->Add(btnResetGoF);
	//sidePanelGoF->SetSizer(sideSizerGoF);

	sideBook->AddPage(sidePanelGoF, "GoF", false);

	// Create Side Panel - Flow Field
	wxPanel* sidePanelFlow = new wxPanel(sideBook);
	sidePanelFlow->SetBackgroundColour(wxColor(255, 255, 255));

	sideBook->AddPage(sidePanelFlow, "Flow", false);
	
	// Main Layout
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(renderPanel);
	mainSizer->Add(sideBook);

	this->SetSizerAndFit(mainSizer);

	simManager->Start(1000 / 60);

}

Frame::~Frame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(render_window);
	
}

void Frame::SwitchSimState(wxCommandEvent& evt)
{
	int id = evt.GetId();
	sideBook->SetSelection(id - 10000);
	simManager->SwitchSim(static_cast<State>(id));
}

void Frame::PauseSim(wxMenuEvent& evt)
{
	simManager->TogglePause();
}

void Frame::ResetSim(wxMenuEvent& evt)
{
	simManager->MasterInit();
}
