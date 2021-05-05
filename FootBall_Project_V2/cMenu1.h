#pragma once
#include "wx/wx.h"
#include "cQuit.h"
#include "cManageteams.h"
#include "cCreate.h"
#include "wxBackgroundBitmap.h"
#include "cCheckstats.h"

class cNewComp;

class cMenu1 : public wxFrame
{
private:
	cManageteams* m_manageteam_frame = nullptr;
	cCreate* m_create_frame = nullptr;

	wxStaticText* m_title1 = nullptr;
	wxStaticText* m_menu1 = nullptr;

	
	cQuit* m_quitframe = nullptr;
	cNewComp* m_newcompframe = nullptr;

	wxButton* m_exit = nullptr;
	wxButton* m_newcompetition = nullptr;
	wxButton* m_checkstats = nullptr;
	wxButton* m_manage = nullptr;
public:
	cMenu1();
	~cMenu1();

	void b_exit(wxCommandEvent& evt);
	void b_newcompetition(wxCommandEvent& evt);
	void b_checkstats(wxCommandEvent& evt);
	void b_manageteam(wxCommandEvent& evt);
	void onclose(wxCloseEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

