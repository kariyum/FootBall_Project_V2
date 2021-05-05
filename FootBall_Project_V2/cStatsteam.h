#pragma once
#include "wx/wx.h"
#include "api.h"
#include <wx/listctrl.h>

class cStatsteam : public wxFrame
{
private:
	wxStaticText* windowtitle;
	wxListBox* listbox;
	wxListCtrl* list;
public:
	cStatsteam();
	~cStatsteam();

	void onlistselection(wxListEvent&);
	void onboxselection(wxCommandEvent&);


	wxDECLARE_EVENT_TABLE();
	

};

