#pragma once
#include "wx/wx.h"
class cMenu1;
class cCreate;

class cNextcreate : public wxFrame
{
private:
	wxStaticText* m_title = nullptr;
	wxStaticText* m_groupselect = nullptr;
	wxStaticText* teams[12];

	wxChoice* m_choice = nullptr;

	wxButton* m_next = nullptr;
	wxButton* m_cancel = nullptr;
	wxButton* m_back = nullptr;
	wxButton* m_selectplayers[6];

	wxListBox* m_playerslist[4];
	wxButton* m_playeradd[2];
	wxButton* m_beginmatch;

	cMenu1* m_menu1_frame = nullptr;
	cCreate* m_create_frame = nullptr;

public:
	cNextcreate();
	~cNextcreate();

	void b_next(wxCommandEvent& evt);
	void b_back(wxCommandEvent& evt);
	void b_cancel(wxCommandEvent& evt);
	void ongroupselection(wxCommandEvent& evt);
	void onplayerselection(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

