#pragma once
#include "wx/wx.h"

class cMenu1;
class cNewComp;
class cNextcreate;

class cCreate : public wxFrame
{
private:
	wxStaticText* m_create;

	wxButton* m_cancel;
	wxButton* m_next;
	
	wxButton* m_b_groupe[8];

	wxButton* m_b_rm[8];

	wxListBox* m_continentlist = nullptr;

	wxListBox* m_groupe[8];
	wxButton* m_back = nullptr;
	wxStaticText* m_select;

	wxComboBox* m_combobox;

	bool firstselection = false;

	cMenu1* m_menu1_frame = nullptr;
	cNewComp* m_newcomp_frame = nullptr;
	cNextcreate* m_nextcreate_frame = nullptr;

	wxButton* m_delete;

	
public:
	cCreate();
	~cCreate();

	void b_cancel(wxCommandEvent& evt);
	void f_display(wxCommandEvent& evt);
	void b_back(wxCommandEvent& evt);
	void b_next(wxCommandEvent& evt);
	void b_addteam(wxCommandEvent& evt);
	void b_rm(wxCommandEvent& evt);

	void deletefunction(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

