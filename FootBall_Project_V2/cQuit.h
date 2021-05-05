#pragma once
#include "wx/wx.h" 

class cMenu1;

class cQuit : public wxFrame
{
private:
	wxButton* m_yes = nullptr;
	wxButton* m_cancel = nullptr;

	wxStaticText* m_sure = nullptr;

	cMenu1* ptr_menu1_att = nullptr;
public:
	cQuit(cMenu1* ptr_menu1);
	~cQuit();

	void b_yes(wxCommandEvent& evt);
	void b_cancel(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

