#include "Frame.h"

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Simulacrum")
{
	wxPanel* renderPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 600));
	renderPanel->SetBackgroundColour(wxColor(100, 200, 100));

	wxPanel* sidePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200,600));
	sidePanel->SetBackgroundColour(wxColor(200, 100, 100));

	wxPanel* sideElement1 = new wxPanel(sidePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	sideElement1->SetBackgroundColour(wxColor(100, 100, 200));

	wxPanel* sideElement2 = new wxPanel(sidePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	sideElement2->SetBackgroundColour(wxColor(200, 100, 200));

	wxBoxSizer* sideSizer = new wxBoxSizer(wxVERTICAL);
	sideSizer->Add(sideElement1, 1, wxEXPAND | wxALL, 0);
	sideSizer->Add(sideElement2, 1, wxEXPAND | wxALL, 0);


	sidePanel->SetSizer(sideSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(renderPanel,0);
	mainSizer->Add(sidePanel,0);

	this->SetSizerAndFit(mainSizer);
}

Frame::~Frame()
{
}
