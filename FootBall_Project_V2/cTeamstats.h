#pragma once
#include "wx/wx.h"
#include "api.h"
class cTeamstats : public wxFrame
{
private:
	wxStaticText* windowtitle;
	wxListBox* listbox;
	wxTimer* datetime;
	vector< pair<int, string>> map;
	wxStaticText** names;

public:
	cTeamstats();
	~cTeamstats();
	void addsecond(wxTimerEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

