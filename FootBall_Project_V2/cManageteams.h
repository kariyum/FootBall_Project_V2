#pragma once
#include "wx/wx.h"
#include "api.h"

class cManageteams : public wxFrame
{
private:
	wxStaticText* title = nullptr;

	wxButton* addteam[2];
	wxButton* modidyteam = nullptr;
	wxButton* deleteteam[2];

	wxListBox* teamslistbox;
	wxListBox* playerslistbox[2];

	wxStaticText* teams_name[2];
	wxStaticText* team_label;

	wxTextCtrl* playername;
	vector<string> players;

	wxButton* saveteam;
	wxButton* selectteam;
	string teamname;
public:
	cManageteams();
	~cManageteams();

	void onaddplayer(wxCommandEvent& evt);
	void onremoveplayer(wxCommandEvent& evt);
	void onselectteam(wxCommandEvent& evt);
	void onsaveteam(wxCommandEvent& evt);
};

