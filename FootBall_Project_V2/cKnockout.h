#pragma once
#include "wx/wx.h"
class cMenu1;
class cKnockout : public wxFrame
{
private:
	wxStaticText* m_title;

	wxButton* m_cancel;
	wxButton* m_match1[4];
	wxButton* m_match2[2];

	wxChoice* m_choices[8];
	wxChoice* m_choices1[4];
	wxChoice* m_choices2[2];
	wxChoice* m_choices3 = nullptr;

	cMenu1* m_menu1_frame = nullptr;
public:
	cKnockout();
	~cKnockout();

	void onpaint(wxPaintEvent& evt);
	void oncancel(wxCommandEvent& evt);
	void onm_match(wxCommandEvent& evt);
	void onchoiceselsection(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

