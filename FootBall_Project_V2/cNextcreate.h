#pragma once
#include "wx/wx.h"
#include <fstream>
#include <iostream>
#include "api.h"
#include <map>;

class cKnockout;
class cMenu1;
class cCreate;
class cStartmatch;

class cNextcreate : public wxFrame
{
private:

	wxStaticText* m_title = nullptr;
	wxStaticText* m_groupselect = nullptr;
	wxStaticText* teams[12];
	wxStaticText* m_t_name[4];
	wxStaticText* m_vs_title[6];

	wxChoice* m_choice = nullptr;

	wxButton* m_next = nullptr;
	wxButton* m_cancel = nullptr;
	wxButton* m_back = nullptr;
	wxButton* m_selectplayers[6];
	wxButton* m_playeremove1 = nullptr;
	wxButton* m_playeremove2 = nullptr;
	wxButton* m_autofill = nullptr;

	wxButton* m_delete;

	wxListBox* m_playerslist[4];
	wxButton* m_playeradd[2];
	wxButton* m_beginmatch;

	wxString matchs[6][2];
	
	wxString* gteams;

	wxStaticText* m_winners[6];
	vector<int> statictextdeleter;

	cMenu1* m_menu1_frame = nullptr;
	cCreate* m_create_frame = nullptr;
	cKnockout* m_knockout_frame = nullptr;
	cStartmatch* m_startmatch_frame = nullptr;

	bool f_groupselection = true;

	vector<string> groupe_teams;
public:
	cNextcreate();
	~cNextcreate();

	void onauto(wxCommandEvent& evt);
	void b_next(wxCommandEvent& evt);
	void b_back(wxCommandEvent& evt);
	void b_cancel(wxCommandEvent& evt);
	void ongroupselection(wxCommandEvent& evt);
	void onplayerselection(wxCommandEvent& evt);
	void deletefunction(wxCommandEvent& evt);
	void onselectgroup(wxCommandEvent& evt);
	void onplayeradd(wxCommandEvent& evt);
	void onplayeremove(wxCommandEvent& evt);
	void onbeginmatch(wxCommandEvent& evt);

	bool matchispending(string, string, wxString&);
	void displaywinners();
	void playerslistdelete();
	void notification_done_matchs();
	int team_score(string);

	wxDECLARE_EVENT_TABLE();
};

