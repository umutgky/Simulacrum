#include "Frame.h"


Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Simulacrum")
{
	wxPanel* renderPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 600));
	//renderPanel->SetBackgroundColour(wxColor(100, 200, 100));

	render_window = SDL_CreateWindowFrom((void*)renderPanel->GetHandle());

	if (render_window != NULL) {
		renderer = SDL_CreateRenderer(render_window, NULL, 0);

	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_RenderPresent(renderer);
	

	wxPanel* sidePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200,600));
	sidePanel->SetBackgroundColour(wxColor(255, 255, 255));

	wxPanel* sideElement1 = new wxPanel(sidePanel, wxID_ANY, wxDefaultPosition, wxSize(200,100));
	sideElement1->SetBackgroundColour(wxColor(0, 0, 200));

	wxPanel* sideElement2 = new wxPanel(sidePanel, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	sideElement2->SetBackgroundColour(wxColor(200, 100, 200));

	wxBoxSizer* sideSizer = new wxBoxSizer(wxVERTICAL);
	sideSizer->Add(sideElement1);
	sideSizer->Add(sideElement2);


	sidePanel->SetSizer(sideSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(renderPanel);
	mainSizer->Add(sidePanel);

	this->SetSizerAndFit(mainSizer);


}

Frame::~Frame()
{
	SDL_DestroyWindow(render_window);
}
