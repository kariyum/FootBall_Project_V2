#include "cNextcreate.h"
#include "cMenu1.h"
#include "cCreate.h"

wxBEGIN_EVENT_TABLE(cNextcreate, wxFrame)
EVT_BUTTON(12, b_cancel)
EVT_BUTTON(15, b_next)
EVT_BUTTON(14, b_back)
EVT_CHOICE(13, ongroupselection)
EVT_BUTTON(1000, onplayerselection)
wxEND_EVENT_TABLE()

cNextcreate::cNextcreate() : wxFrame(nullptr, wxID_ANY, "Group Stage", wxPoint(300, 150), wxSize(1000, 600)) {
	m_title = new wxStaticText(this, wxID_ANY, wxT("GROUP STAGE"), wxPoint(10, 10), wxSize(-1, -1));
	m_title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));

	m_groupselect = new wxStaticText(this, wxID_ANY, wxT("Select a group :"), wxPoint(20, 70), wxSize(-1, -1));
	m_groupselect->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	m_choice = new wxChoice(this, 13, wxPoint(20, 120), wxSize(150, 240));
	for (int i = 1; i < 9; i++) {
		wxString s;
		s << i;
		m_choice->AppendString("Groupe " + s);
	}
	//m_choice->Select(0);

	m_cancel = new wxButton(this, 12, "Cancel", wxPoint(880, 530), wxDefaultSize);
	m_next = new wxButton(this, 15, "Next", wxPoint(880, 500));
	m_back = new wxButton(this, 14, "Back", wxPoint(797, 500));

}

cNextcreate::~cNextcreate() {

}

void cNextcreate::b_next(wxCommandEvent& evt) {

}

void cNextcreate::b_back(wxCommandEvent& evt) {
	m_create_frame = new cCreate();
	m_create_frame->Show();
	this->Close();
	evt.Skip();
}

void cNextcreate::b_cancel(wxCommandEvent& evt) {
	m_menu1_frame = new cMenu1();
	m_menu1_frame->Show();
	this->Close();
	evt.Skip();
}

void cNextcreate::ongroupselection(wxCommandEvent& evt) {
	wxMessageBox(m_choice->GetStringSelection() + " selected", wxT("Warning!"), wxICON_WARNING);
	int x = 20;
	int y = 170;

	int dx = 200;
	int dy = 60;
	
	m_selectplayers[0] = new wxButton(this, 1000, "Select players", wxPoint(x + 300, y));
	teams[0] = new wxStaticText(this, wxID_ANY, "Team 1	       VS", wxPoint(x, y));
	teams[1] = new wxStaticText(this, wxID_ANY, "Team 2", wxPoint(x + dx, y));

	m_selectplayers[1] = new wxButton(this, wxID_ANY, "Select players", wxPoint(x + 300, y + dy));
	teams[2] = new wxStaticText(this, wxID_ANY, "Team 1	       VS", wxPoint(x, y + dy));
	teams[3] = new wxStaticText(this, wxID_ANY, "Team 3", wxPoint(x + dx, y + dy));

	m_selectplayers[2] = new wxButton(this, wxID_ANY, "Select players", wxPoint(x + 300, y + 2 * dy));
	teams[4] = new wxStaticText(this, wxID_ANY, "Team 1	       VS", wxPoint(x, y + 2 * dy));
	teams[5] = new wxStaticText(this, wxID_ANY, "Team 4", wxPoint(x + dx, y + 2*dy));

	m_selectplayers[3] = new wxButton(this, wxID_ANY, "Select players", wxPoint(x + 300, y + 3 * dy));
	teams[6] = new wxStaticText(this, wxID_ANY, "Team 2	       VS", wxPoint(x, y + 3 * dy));
	teams[7] = new wxStaticText(this, wxID_ANY, "Team 3", wxPoint(x + dx, y + 3 * dy));
	
	m_selectplayers[4] = new wxButton(this, wxID_ANY, "Select players", wxPoint(x + 300, y + 4 * dy));
	teams[8] = new wxStaticText(this, wxID_ANY, "Team 2	       VS", wxPoint(x, y + 4 * dy));
	teams[9] = new wxStaticText(this, wxID_ANY, "Team 4", wxPoint(x + dx, y + 4 * dy));

	m_selectplayers[5] = new wxButton(this, wxID_ANY, "Select players", wxPoint(x + 300, y + 5 * dy));
	teams[10] = new wxStaticText(this, wxID_ANY, "Team 3	       VS", wxPoint(x, y + 5 * dy));
	teams[11] = new wxStaticText(this, wxID_ANY, "Team 4", wxPoint(x + dx, y + 5 * dy));

	for (int i = 0; i < 12; i++) {
		teams[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}

	evt.Skip();
}

void cNextcreate::onplayerselection(wxCommandEvent& evt) {
	int x = 500;
	int y = 40;

	int dx = 300;
	int dy = 250;

	int sx = 150;
	int sy = 200;
	m_playerslist[0] = new wxListBox(this, wxID_ANY, wxPoint(x, y), wxSize(sx, sy));
	m_playerslist[1] = new wxListBox(this, wxID_ANY, wxPoint(x, y + dy), wxSize(sx, sy));
	m_playerslist[2] = new wxListBox(this, wxID_ANY, wxPoint(x + dx, y), wxSize(sx, sy));
	m_playerslist[3] = new wxListBox(this, wxID_ANY, wxPoint(x + dx, y + dy), wxSize(sx, sy));
	
	m_playeradd[0] = new wxButton(this, wxID_ANY,"Add player" ,wxPoint(x + 190, 125));
	m_playeradd[1] = new wxButton(this, wxID_ANY,"Add player" ,wxPoint(x + 190, 375));

	m_beginmatch = new wxButton(this, wxID_ANY, "Begin Match", wxPoint(x + 187, 500));

	evt.Skip();
}