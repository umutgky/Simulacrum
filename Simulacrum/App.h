#pragma once
#include "wx/wx.h"
#include "Frame.h"

class App : public wxApp
{
public:
	App();
	~App();

private:

	Frame* frame = nullptr;




public:
	virtual bool OnInit();
};

