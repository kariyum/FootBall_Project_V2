#include "cNewComp.h"
#include "cCreate.h"
#include "cMenu1.h"

wxBEGIN_EVENT_TABLE(cNewComp, wxFrame)
EVT_BUTTON(11, b_create)
EVT_BUTTON(12, b_cancel)
EVT_CHOICE(13, b_onselection)
wxEND_EVENT_TABLE()

cNewComp::cNewComp() : wxFrame(nullptr, wxID_ANY, "New Competition", wxPoint(400, 250), wxSize(500, 300), wxSYSTEM_MENU | wxCAPTION | wxCLIP_CHILDREN) {
	m_new = new wxStaticText(this, wxID_ANY, wxT("New"), wxPoint(10, 10), wxSize(-1, -1));

	m_yearLabel = new wxStaticText(this, wxID_ANY, wxT("Year "), wxPoint(60, 80));
	m_nameLabel = new wxStaticText(this, wxID_ANY, wxT("Name "), wxPoint(60, 140));

	m_name = new wxTextCtrl(this, wxID_ANY, "", wxPoint(145, 140), wxSize(200, 35));
	m_year = new wxChoice(this, 13, wxPoint(145, 80), wxSize(200, 35));
	
	for (int i = 2021; i < 2031; i++) {
		wxString s;
		s << i;
		m_year->AppendString(s);
	}
	m_year->Select(0);
	m_cancel = new wxButton(this, 12, "Cancel", wxPoint(300, 200), wxSize(90, 30));
	m_create = new wxButton(this, 11, "Create", wxPoint(110, 200), wxSize(90, 30));

	wxFont title(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true);
	m_new->SetFont(title);
	m_new->SetForegroundColour(wxColor(25, 25, 112));

	wxFont label(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	m_yearLabel->SetFont(label);
	m_nameLabel->SetFont(label);
	m_year->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_name->SetFont(label);

	wxFont btn_font(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	m_create->SetFont(btn_font);
	m_cancel->SetFont(btn_font);
}

cNewComp::~cNewComp() {}

void cNewComp::b_cancel(wxCommandEvent& evt) {
	//possibly prompt a warning to close
	m_menu1_frame = new cMenu1();
	m_menu1_frame->Show();
	this->Close();
	evt.Skip();
}
void cNewComp::b_create(wxCommandEvent& evt) {
	//check digits in year label prompt dialog msg
	m_createframe = new cCreate();
	m_createframe->Show();
	this->Close();
	evt.Skip();
}

void cNewComp::b_onselection(wxCommandEvent& evt) {
	wxMessageBox(wxT("WORKS!"), wxT("Warning!"), wxICON_WARNING);
	evt.Skip();
}