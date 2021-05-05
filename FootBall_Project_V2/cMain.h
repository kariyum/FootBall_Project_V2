#pragma once
#include "wx/wx.h" 
#include "cMenu1.h"
#include "wxBackgroundBitmap.h"
#include <wx/mediactrl.h>


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

	wxButton* playButton;

	wxString filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/kawafel.mp3";
	wxMediaCtrl* kawafel;
	wxButton* playbutton;
	bool isbeingplayed = false;
	void ShowPassword(wxCommandEvent& evt);
	void OnConnect(wxCommandEvent& evt);
	bool valid(std::string truepassword);
	void OnClose(wxCloseEvent&);
	void onPlay(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};
