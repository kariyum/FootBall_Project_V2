#pragma once
#include "wx/wx.h" 
#include "cMenu1.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
private:
	cMenu1* m_menu1_frame = nullptr;

	wxButton* m_btn_connect = nullptr;
	
	wxTextCtrl* m_txt1 = nullptr;
	wxTextCtrl* m_passwordEntry;

	wxListBox* m_list1 = nullptr;
	
	wxStaticText* m_passwordLabel;
	wxStaticText* m_title1;
	wxStaticText* m_showpass;

	wxCheckBox* m_checkbox;

	void ShowPassword(wxCommandEvent& evt);
	void OnConnect(wxCommandEvent& evt);
	bool valid(std::string truepassword);

	wxDECLARE_EVENT_TABLE();
};
