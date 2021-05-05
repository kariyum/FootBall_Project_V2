#pragma once
#include "wx/wx.h"
#include "api.h"

class cMatchstats : public wxFrame
{
private:
	wxListBox* matchs_list;
	wxChoice* matchs_choice;
	wxStaticText* title;
	wxPanel* panel1;
public:
	cMatchstats();
	~cMatchstats();

	void onselection(wxCommandEvent& evt);
	vector<string> matchstring(wxString);
	wxDECLARE_EVENT_TABLE();
};

