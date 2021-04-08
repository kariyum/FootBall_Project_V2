#pragma once
#include "wx/wx.h"

class cStartmatch : public wxFrame
{
private:
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

    int numberoflines = 1;
    int time1111 = 0;
    int created[2];
    float minuteriestatus = false;
    int recenttime = 0;
    int breakperiod = 0;
public:
	cStartmatch();
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

    wxString inttotime(int);
    wxVector<wxString> separate(wxString s, int cols);



    DECLARE_EVENT_TABLE()
};

