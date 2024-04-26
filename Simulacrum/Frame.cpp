#include "Frame.h"



Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Simulacrum")
{
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* simsMenu = new wxMenu();
	simsMenu->AppendRadioItem(None, _("None"));
	simsMenu->AppendRadioItem(GameOfLife, _("Game Of Life"));
	simsMenu->AppendRadioItem(FlowField, _("Flow Field"));
	menuBar->Append(simsMenu, "Simulations");
	SetMenuBar(menuBar);
	menuBar->Bind(wxEVT_MENU, &Frame::SwitchSimState, this);
	wxPanel* renderPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 600));
	//renderPanel->SetBackgroundColour(wxColor(100, 200, 100));

	render_window = SDL_CreateWindowFrom((void*)renderPanel->GetHandle());
	
	if (render_window != NULL) {
		renderer = SDL_CreateRenderer(render_window, NULL, 0);

	}
	
	simManager = std::make_unique<SimManager>(renderer);
	

	wxSimplebook* sideBook = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxSize(200,600), wxBORDER_SIMPLE);

	wxPanel* sidePanel = new wxPanel(sideBook, wxID_ANY, wxDefaultPosition);
	sidePanel->SetBackgroundColour(wxColor(0, 255, 255));

	wxPanel* sideElement1 = new wxPanel(sidePanel, wxID_ANY, wxDefaultPosition);
	sideElement1->SetBackgroundColour(wxColor(255, 255, 0));
	//sideElement1->SetMinSize(wxSize(1, 1));

	wxPanel* sideElement2 = new wxPanel(sidePanel, wxID_ANY, wxDefaultPosition);
	sideElement2->SetBackgroundColour(wxColor(255, 0, 0));
	//sideElement2->SetMinSize(wxSize(1, 1));

	wxBoxSizer* sideSizer = new wxBoxSizer(wxVERTICAL);
	sideSizer->Add(sideElement1,1, wxEXPAND);
	sideSizer->Add(sideElement2,1, wxEXPAND);

	sidePanel->SetSizer(sideSizer);


	wxPanel* sidePanel2 = new wxPanel(sideBook);
	sidePanel2->SetBackgroundColour(wxColor(255, 255, 255));

	sideBook->AddPage(sidePanel, "side", false);
	sideBook->AddPage(sidePanel2, "side2", false);
	sideBook->SetSelection(0);
	
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
	simManager->SwitchSim(static_cast<State>(evt.GetId()));
}
