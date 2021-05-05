#pragma once
#include "wx/wx.h"
#include "api.h"

class cPlayerslist : public wxFrame
{
private:
	wxListBox* listbox;
	wxStaticText* windowtitle;
	wxTimer* datetime;
	vector < pair<string, int>> map;

	wxStaticText** names;
	wxStaticText* bestplayer;
	wxStaticText* sorted;

public:
	cPlayerslist();
	~cPlayerslist();
	void addsecond(wxTimerEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

