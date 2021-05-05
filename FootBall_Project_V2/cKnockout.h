#pragma once
#include "wx/wx.h"
#include "api.h"
#include "cPlayerselection.h"
#include "cNextcreate.h"
#include "cWinner.h"
class cMenu1;
class cKnockout : public wxFrame
{
private:
	vector<string> vec_runners;
	vector<string> vec_winners;

	wxStaticText* round16[2], *round8[2], *round4[2], *round2[2];

	wxStaticText* m_title;
	wxStaticText* m_vstitle;
	wxStaticText* m_winners3[4];
	wxStaticText* m_winners1[4];
	wxStaticText* m_winners2[2];
	wxStaticText* m_winners4[2];

	wxStaticText* m_choice_text1[8];
	wxStaticText* m_choice_text2[8];
	wxStaticText* m_12text[2];
	wxStaticText* m_finalwinner_text;

	wxButton* m_cancel;
	wxButton* m_match1[4];
	wxButton* m_match2[2];

	wxButton* m_match3[4];
	wxButton* m_match4[2];

	wxButton* m_12winner[2];

	wxButton* m_finalwinner = nullptr;

	wxChoice* m_choices[8];
	wxChoice* m_choices1[4];
	wxChoice* m_choices2[2];

	wxChoice* m_choices4[8];

	wxChoice* m_choices3 = nullptr;
	wxChoice* m_rightwinner = nullptr;

	cMenu1* m_menu1_frame = nullptr;
	cPlayerselection* m_playerselection_frame = nullptr;
	cNextcreate* m_nextcreate_frame = nullptr;
	wxButton* m_back;
	wxButton* m_auto;
	int real_id = 0;
	bool firstauto = true;
public:
	bool finaaal = false;
	cKnockout();
	~cKnockout();

	void onpaint(wxPaintEvent& evt);
	void oncancel(wxCommandEvent& evt);
	void onm_match(wxCommandEvent& evt);
	void onchoiceselsection(wxCommandEvent& evt);

	void displaywinners(wxString);
	void onback(wxCommandEvent& evt);

	void onauto(wxCommandEvent& evt);

	void enablematchbutton();
	int teamisselected(int, int);
	void save_team_stats_knockout(string winner);
	wxDECLARE_EVENT_TABLE();
};

