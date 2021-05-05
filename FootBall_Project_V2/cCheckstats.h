#pragma once
#include "wx/wx.h"
#include "cMatchstats.h"
#include "cTeamstats.h"
#include "cPlayerslist.h"
#include "cStatsteam.h"
#include "cPlayerstats.h"

class cCheckstats : public wxFrame
{
private:
	wxButton* b_teamstats;
	wxButton* b_playerstats;
	wxButton* b_matchstats;
	wxButton* m_back;
	wxButton* b_playerlist;
	wxButton* b_teamslist;
public:
	cCheckstats();
	~cCheckstats();

	void onback(wxCommandEvent& evt);
	void onmatchstats(wxCommandEvent& evt);
	void onplayerstats(wxCommandEvent& evt);
	void onteamstats(wxCommandEvent& evt);
	void onplayerslist(wxCommandEvent& evt);
	void onstatsteam(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

