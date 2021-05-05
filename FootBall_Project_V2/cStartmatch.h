#pragma once
#include "wx/wx.h"
#include "api.h"
#include "cNextcreate.h"
#include "wx/mediactrl.h"

class cPlayerselection;

class cStartmatch : public wxFrame
{
private:
    cNextcreate* parent_pointer = nullptr;
    cPlayerselection* parent_pointer1 = nullptr;
    cKnockout* parent_pointer2 = nullptr;

    bool iscnextcreate = true;

    wxMediaCtrl* commentary, * goalcommentary, * finalcommentary = nullptr;

    wxStaticText* windowtitle;
    wxButton** redcards;
    wxButton* add_r1[22];
    wxButton* sub_r1[22];
    wxButton* yellowcards[22];
    wxButton* add_y1[22];
    wxButton* sub_y1[22];
    wxButton* m_add_goals[2];
    wxButton* m_endmatch;
    wxButton* m_addnote;
    wxButton* m_startstoptime;
    wxButton* m_takebreak;

    wxTimer* datetime;

    wxStaticText* playersname[22];
    wxStaticText* teams_title[2];
    wxStaticText* m_vs_title;
    wxStaticText* m_goals[2];
    wxStaticText* m_matchnotes;
    wxStaticText* chornotime;
    wxStaticText* minuterie;

    wxChoice* m_choices[2];

    wxListBox* m_note;
    wxTextCtrl* m_notetext;

    vector<string> players;
    vector<string> notes;
    vector<string> vector_player_resulsts;

    int player_results[22][3];

    int numberoflines = 1;
    int time1111 = 0;
    int created[2];
    float minuteriestatus = false;
    int recenttime = 0;
    int breakperiod = 0;
public:
	cStartmatch(wxPanel* p1, wxString team1, wxString team2, vector<string>& players1, string tab[22][3], vector<string> n_notes);


	cStartmatch(wxString team1, wxString team2, vector<string> players1, cNextcreate*);
	cStartmatch(wxString team1, wxString team2, vector<string> players1, cPlayerselection*);
	cStartmatch(wxString team1, wxString team2, vector<string> players1, cKnockout*);

	~cStartmatch();


    void onendmatch(wxCommandEvent& evt);
    void onaddnote(wxCommandEvent& evt);
    void onstartstoptime(wxCommandEvent& evt);
    void addsecond(wxTimerEvent& evt);
    void onaddgoals(wxCommandEvent& evt);
    void onchoiceselection(wxCommandEvent& evt);
    void onplus(wxCommandEvent& evt);
    void onminus(wxCommandEvent& evt);
    void ontakebreak(wxCommandEvent& evt);

    void initialize();

    wxString inttotime(int);
    wxVector<wxString> separate(wxString s, int cols);

    void save_playerstats(vector<string>);

    DECLARE_EVENT_TABLE()
};

