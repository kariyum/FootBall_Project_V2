#include "cMenu1.h"
#include "cNewComp.h"

wxBEGIN_EVENT_TABLE(cMenu1, wxFrame)
EVT_BUTTON(1, b_exit)
EVT_BUTTON(11, b_newcompetition)
wxEND_EVENT_TABLE()

cMenu1::cMenu1() : wxFrame(nullptr, wxID_ANY, "Menu", wxPoint(300, 50), wxSize(800, 600), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)  {
	m_title1 = new wxStaticText(this, wxID_ANY, "FOOTBALL COMPETITION MANAGEMENT", wxPoint(40, 90));
	m_title1->SetFont(wxFont(26, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	m_menu1 = new wxStaticText(this, wxID_ANY, "Menu :", wxPoint(50, 250));
	m_menu1->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	wxFont menu_font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	m_newcompetition = new wxButton(this, 11, "New Competition",wxPoint(50, 300), wxSize(650, 38));
	m_newcompetition->SetFont(menu_font);

	m_checkstats = new wxButton(this, wxID_ANY, "Check stats", wxPoint(50, 350), wxSize(650, 38));
	m_checkstats->SetFont(menu_font);

	m_exit = new wxButton(this, 1, "Exit", wxPoint(600, 475), wxSize(100, 38));
	m_exit->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
}

cMenu1::~cMenu1() {

}

void cMenu1::b_checkstats(wxCommandEvent& evt) {

}

void cMenu1::b_exit(wxCommandEvent& evt) {
	//verify if he is sure.
	/*m_exit->Enable(false);
	m_newcompetition->Enable(false);
	m_checkstats->Enable(false);*/

	m_quitframe = new cQuit(this);
	m_quitframe->Show();
	this->Disable();
	evt.Skip();
}

void cMenu1::b_newcompetition(wxCommandEvent& evt) {
	m_newcompframe = new cNewComp();
	m_newcompframe->Show();
	this->Close();
	evt.Skip();
}