#pragma once
#include "wx/wx.h"

class cMenu1;
class cCreate;

class cNewComp : public wxFrame
{
private:
	wxStaticText* m_new;
	wxStaticText* m_yearLabel;

	wxStaticText* m_nameLabel;
	wxTextCtrl* m_name = nullptr;


	wxButton* m_create = nullptr;
	wxButton* m_cancel = nullptr;
	 
	wxTextCtrl* m_year = nullptr;

	cCreate* m_createframe = nullptr;
	cMenu1* m_menu1_frame = nullptr;
public:
	cNewComp();
	~cNewComp();
	void b_cancel(wxCommandEvent& evt);
	void b_create(wxCommandEvent& evt);
	void b_onselection(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
	
};

