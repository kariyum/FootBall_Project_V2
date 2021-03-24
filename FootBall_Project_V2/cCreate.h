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

	wxButton* m_b_groupe1 = nullptr;
	wxButton* m_b_groupe2 = nullptr;
	wxButton* m_b_groupe3 = nullptr;
	wxButton* m_b_groupe4 = nullptr;
	wxButton* m_b_groupe5 = nullptr;
	wxButton* m_b_groupe6 = nullptr;
	wxButton* m_b_groupe7 = nullptr;
	wxButton* m_b_groupe8 = nullptr;

	wxButton* m_b_rm1 = nullptr;
	wxButton* m_b_rm2 = nullptr;
	wxButton* m_b_rm3 = nullptr;
	wxButton* m_b_rm4 = nullptr;
	wxButton* m_b_rm5 = nullptr;
	wxButton* m_b_rm6 = nullptr;
	wxButton* m_b_rm7 = nullptr;
	wxButton* m_b_rm8 = nullptr;

	wxListBox* m_continentlist = nullptr;
	wxListBox* m_groupe1 = nullptr;
	wxListBox* m_groupe2 = nullptr;
	wxListBox* m_groupe3 = nullptr;
	wxListBox* m_groupe4 = nullptr;
	wxListBox* m_groupe5 = nullptr;
	wxListBox* m_groupe6 = nullptr;
	wxListBox* m_groupe7 = nullptr;
	wxListBox* m_groupe8 = nullptr;

	wxButton* m_back = nullptr;
	wxStaticText* m_select;

	wxComboBox* m_combobox;

	cMenu1* m_menu1_frame = nullptr;
	cNewComp* m_newcomp_frame = nullptr;
	cNextcreate* m_nextcreate_frame = nullptr;
public:
	cCreate();
	~cCreate();

	void b_cancel(wxCommandEvent& evt);
	void f_display(wxCommandEvent& evt);
	void b_back(wxCommandEvent& evt);
	void b_next(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

