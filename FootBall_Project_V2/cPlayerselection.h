#pragma once
#include "wx/wx.h"
#include "api.h"
#include "cStartmatch.h"
#include "cKnockout.h"

class cPlayerselection : public wxFrame
{
private:
	cKnockout* parent_pointer = nullptr;

	wxStaticText* m_title;

	wxListBox* m_players[4];

	wxButton* add[2];
	wxButton* remove[2];
	wxButton* m_startmatch;

	wxStaticText* team[4];

	vector<string> players1;
	cStartmatch* m_startmatch_frame = nullptr;
public:

	cPlayerselection(wxString ,wxString, cKnockout*);
	~cPlayerselection();

	void onplayeradd(wxCommandEvent& evt);
	void onremove(wxCommandEvent& evt);
	void onstartmatch(wxCommandEvent& evt);

	void displaywinners() {} 
	void playerslistdelete() {}
	void notification_done_matchs(){}
	//need to pass the cKnockout pointer to cStartmatch to display winner..
	//don't need those 3 functions, don't forget the constructor.
	//check match buttons on the left

	wxDECLARE_EVENT_TABLE();
};

