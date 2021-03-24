#pragma once
#include "wx/wx.h"
#include "cQuit.h"

class cNewComp;

class cMenu1 : public wxFrame
{
private:
	wxStaticText* m_title1 = nullptr;
	wxStaticText* m_menu1 = nullptr;

	
	cQuit* m_quitframe = nullptr;
	cNewComp* m_newcompframe = nullptr;

public:
	wxButton* m_exit = nullptr;
	wxButton* m_newcompetition = nullptr;
	wxButton* m_checkstats = nullptr;
	
public:
	cMenu1();
	~cMenu1();

	void b_exit(wxCommandEvent& evt);
	void b_newcompetition(wxCommandEvent& evt);
	void b_checkstats(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

