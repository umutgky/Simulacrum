#include "Frame.h"



Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Simulacrum")
{
	// Create the Menu bar
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* simsMenu = new wxMenu();
	simsMenu->AppendRadioItem(None, _("None"));
	simsMenu->AppendRadioItem(GameOfLife, _("Game Of Life"));
	simsMenu->AppendRadioItem(FlowField, _("Flow Field"));
	menuBar->Append(simsMenu, "Simulations");
	SetMenuBar(menuBar);
	menuBar->Bind(wxEVT_MENU, &Frame::SwitchSimState, this);

	// Create Rendering Context
	wxPanel* renderPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 600));
	render_window = SDL_CreateWindowFrom((void*)renderPanel->GetHandle());
	if (render_window != NULL) {
		renderer = SDL_CreateRenderer(render_window, NULL, 0);
	}
	// Create Sim Manager
	simManager = std::make_unique<SimManager>(renderer);
	
	// Create Side Panel
	sideBook = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxSize(200,600));

	// Create Side Panel - None
	wxPanel* sidePanelNone = new wxPanel(sideBook, wxID_ANY);
	sidePanelNone->SetBackgroundColour(wxColor(0, 0, 255));
	sideBook->ShowNewPage(sidePanelNone);

	// Create Side Panel - Game Of Life
	wxPanel* sidePanelGoF = new wxPanel(sideBook, wxID_ANY, wxDefaultPosition);
	sidePanelGoF->SetBackgroundColour(wxColor(0, 255, 255));

	wxPanel* sideElement1 = new wxPanel(sidePanelGoF, wxID_ANY, wxDefaultPosition);
	sideElement1->SetBackgroundColour(wxColor(255, 255, 0));

	wxButton* btn = new wxButton(sideElement1, wxID_ANY, _("Reset"), wxDefaultPosition, wxSize(200,40));

	wxPanel* sideElement2 = new wxPanel(sidePanelGoF, wxID_ANY, wxDefaultPosition);
	sideElement2->SetBackgroundColour(wxColor(255, 0, 0));

	wxBoxSizer* sideSizer = new wxBoxSizer(wxVERTICAL);
	sideSizer->Add(sideElement1,1, wxEXPAND);
	sideSizer->Add(sideElement2,1, wxEXPAND);

	sidePanelGoF->SetSizer(sideSizer);
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
