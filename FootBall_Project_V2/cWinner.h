#pragma once
#include "wx/wx.h"
#include "wx/mediactrl.h"

class cWinner : public wxFrame
{
private:
	wxStaticText* congradulation;
	wxTimer* datetime;
	int time1111 = 0;

	wxStaticText* us[4];
public:
	cWinner(wxString);
	~cWinner();
	wxMediaCtrl* gif;
	wxMediaCtrl* congratz;
	void onclose(wxCloseEvent& evt);
	void addsecond(wxTimerEvent& evt);
	wxDECLARE_EVENT_TABLE();
};