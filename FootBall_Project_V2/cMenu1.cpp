#include "cMenu1.h"
#include "cNewComp.h"

wxBEGIN_EVENT_TABLE(cMenu1, wxFrame)
EVT_BUTTON(1, b_exit)
EVT_BUTTON(11, b_newcompetition)
EVT_BUTTON(12, b_checkstats)
EVT_CLOSE(onclose)
wxEND_EVENT_TABLE()

cMenu1::cMenu1() : wxFrame(nullptr, wxID_ANY, "Menu", wxPoint(300, 50), wxSize(800 * 1.25, 600 * 1.25), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)  {
	wxInitAllImageHandlers();
	wxBitmap TempBitmap;
	TempBitmap.LoadFile(wxT("ball6.jpg"), wxBITMAP_TYPE_JPEG);
	wxBackgroundBitmap* NotebookBackground = new wxBackgroundBitmap(TempBitmap);
	this->PushEventHandler(NotebookBackground);
	//m_title1 = new wxStaticText(this, wxID_ANY, "FOOTBALL COMPETITION MANAGEMENT", wxPoint(40, 90));
	//m_title1->SetFont(wxFont(26, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	//m_menu1 = new wxStaticText(this, wxID_ANY, "Menu :", wxPoint(50, 250));
	//m_menu1->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	wxFont menu_font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	m_newcompetition = new wxButton(this, 11, "New Competition",wxPoint(50 * 1.25, 300 * 1.25), wxSize(650 * 1.25, 38 * 1.25));
	m_newcompetition->SetFont(menu_font);

	m_checkstats = new wxButton(this, 12, "Check stats", wxPoint(50 * 1.25, 350 * 1.25), wxSize(650 * 1.25, 38 * 1.25));
	m_checkstats->SetFont(menu_font);

	m_manage = new wxButton(this, wxID_ANY, "Manage Teams", wxPoint(50 * 1.25, 400 * 1.25), wxSize(650 * 1.25, 38 * 1.25));
	m_manage->SetFont(menu_font);
	m_manage->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMenu1::b_manageteam, this);

	m_exit = new wxButton(this, 1, "Exit", wxPoint(600 * 1.25, 475 * 1.25), wxSize(100 * 1.25, 38 * 1.25));
	m_exit->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
}

cMenu1::~cMenu1() {

}

void cMenu1::b_checkstats(wxCommandEvent& evt) {
	cCheckstats* checkstats_frame = new cCheckstats();
	checkstats_frame->Show();
	Destroy();
	this->PopEventHandler(true);
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
	//m_newcompframe = new cNewComp();
	//m_newcompframe->Show();
	m_create_frame = new cCreate();
	m_create_frame->Show();
	Destroy();
	this->PopEventHandler(true);

	//this->Close();
	//evt.Skip();
}

void cMenu1::b_manageteam(wxCommandEvent& evt) {
	m_manageteam_frame = new cManageteams();
	m_manageteam_frame->Show();
	evt.Skip();
}

void cMenu1::onclose(wxCloseEvent& evt) {
	Destroy();
	this->PopEventHandler(true);
}