#include "cNextcreate.h"
#include "cMenu1.h"
#include "cCreate.h"
#include "cKnockout.h"
#include "cStartmatch.h"

wxBEGIN_EVENT_TABLE(cNextcreate, wxFrame)
EVT_BUTTON(12, b_cancel)
EVT_BUTTON(15, b_next)
EVT_BUTTON(14, b_back)
EVT_CHOICE(13, ongroupselection)
EVT_BUTTON(20, deletefunction)
EVT_BUTTON(21, onselectgroup)
EVT_BUTTON(22, onbeginmatch)

//EVT_BUTTON(1000, onplayerselection)
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
	//m_delete = new wxButton(this, 20, "Delete", wxPoint(700, 530));
}

cNextcreate::~cNextcreate() {
	if (f_groupselection == false) {
		for (int i = 0; i < 6; i++) {
			if (m_selectplayers[i]->IsEnabled() == false) {
				for (int j = 0; j < 4; j++) delete m_t_name[j];
				for (int j = 0; j < 4; j++) delete m_playerslist[j];
				delete m_playeradd[0];
				delete m_playeradd[1];
				delete m_playeremove1;
				delete m_playeremove2;
				delete m_beginmatch;
			}
		}
		for (int i = 0; i < 6;i++) delete m_selectplayers[i];
		for (int i = 0; i < 12; i++) delete teams[i];

	}
	delete m_title;
	delete m_groupselect;
	delete m_next;
	delete m_back;
	delete m_cancel;
	delete m_choice;
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
	//wxMessageBox(m_choice->GetStringSelection() + " is selected", wxT("Warning!"), wxICON_WARNING);
	if (f_groupselection == false) {
		for (int i = 0; i < 6; i++) {
			if (m_selectplayers[i]->IsEnabled() == false) {
				for (int j = 0; j < 4; j++) delete m_t_name[j];
				for (int j = 0; j < 4; j++) delete m_playerslist[j];
				delete m_playeradd[0];
				delete m_playeradd[1];
				delete m_playeremove1;
				delete m_playeremove2;
				delete m_beginmatch;
				//delete gteams;
			}
		}
		for (int i = 0; i < 6;i++) delete m_selectplayers[i];
		for (int i = 0; i < 12; i++) delete teams[i];
	}
	f_groupselection = false;
	
	int x = 20;
	int y = 170;

	int dx = 200;
	int dy = 60;
	
	wxString s = m_choice->GetStringSelection();
	gteams = new wxString[4];

	for (int i =0 ; i<4 ; i++) {
		wxString ss;
		ss << i +1;
		gteams[i].append(s +" TEAM["+ ss + "]");
	}
	
	matchs[0][0] = gteams[0];
	matchs[0][1] = gteams[1];
	
	matchs[1][0] = gteams[0];
	matchs[1][1] = gteams[2];
	
	matchs[2][0] = gteams[0];
	matchs[2][1] = gteams[3];

	matchs[3][0] = gteams[1];
	matchs[3][1] = gteams[2];

	matchs[4][0] = gteams[1];
	matchs[4][1] = gteams[3];

	matchs[5][0] = gteams[2];
	matchs[5][1] = gteams[3];

	delete[] gteams;
	for (int i = 0; i < 6; i++) {
		m_vs_title[i] = new wxStaticText(this, wxID_ANY, "VS", wxPoint((x + dx) / 2 + 50, y + i * dy));
		m_vs_title[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}
	m_selectplayers[0] = new wxButton(this, 1000, "Select players", wxPoint(x + 300, y));
	teams[0] = new wxStaticText(this, wxID_ANY, matchs[0][0] , wxPoint(x, y));
	teams[1] = new wxStaticText(this, wxID_ANY, matchs[0][1], wxPoint(x + dx, y));

	m_selectplayers[1] = new wxButton(this, 1001, "Select players", wxPoint(x + 300, y + dy));
	teams[2] = new wxStaticText(this, wxID_ANY, matchs[1][0], wxPoint(x, y + dy));
	teams[3] = new wxStaticText(this, wxID_ANY, matchs[1][1], wxPoint(x + dx, y + dy));

	m_selectplayers[2] = new wxButton(this, 1002, "Select players", wxPoint(x + 300, y + 2 * dy));
	teams[4] = new wxStaticText(this, wxID_ANY, matchs[2][0], wxPoint(x, y + 2 * dy));
	teams[5] = new wxStaticText(this, wxID_ANY, matchs[2][1], wxPoint(x + dx, y + 2*dy));

	m_selectplayers[3] = new wxButton(this, 1003, "Select players", wxPoint(x + 300, y + 3 * dy));
	teams[6] = new wxStaticText(this, wxID_ANY, matchs[3][0], wxPoint(x, y + 3 * dy));
	teams[7] = new wxStaticText(this, wxID_ANY, matchs[3][1], wxPoint(x + dx, y + 3 * dy));
	
	m_selectplayers[4] = new wxButton(this, 1004, "Select players", wxPoint(x + 300, y + 4 * dy));
	teams[8] = new wxStaticText(this, wxID_ANY, matchs[4][0], wxPoint(x, y + 4 * dy));
	teams[9] = new wxStaticText(this, wxID_ANY, matchs[4][1], wxPoint(x + dx, y + 4 * dy));

	m_selectplayers[5] = new wxButton(this, 1005, "Select players", wxPoint(x + 300, y + 5 * dy));
	teams[10] = new wxStaticText(this, wxID_ANY, matchs[5][0], wxPoint(x, y + 5 * dy));
	teams[11] = new wxStaticText(this, wxID_ANY, matchs[5][1], wxPoint(x + dx, y + 5 * dy));

	for (int i = 0; i < 12; i++) {
		teams[i]->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}
	for (int i = 0; i < 6; i++) {
		m_selectplayers[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayerselection, this);
	}

	evt.Skip();
}

void cNextcreate::onplayerselection(wxCommandEvent& evt) {
	for (int i = 0; i < 6; i++) {
		if (m_selectplayers[i]->IsEnabled() == false) {
			for (int j = 0; j < 4; j++) delete m_t_name[j];
			for (int j = 0; j < 4; j++) delete m_playerslist[j];
			delete m_playeradd[0];
			delete m_playeradd[1];
			delete m_playeremove1;
			delete m_playeremove2;
			delete m_beginmatch;
		}
	}
	int id = evt.GetId()-1000;
	for (int i = 0; i < 6; i++) {
		if (i == id) m_selectplayers[id]->Enable(false);
		else  m_selectplayers[i]->Enable(true);
	}
	int x = 500;
	int y = 40;

	int dx = 300;
	int dy = 250;

	int sx = 150;
	int sy = 200;

	m_t_name[0] = new wxStaticText(this, wxID_ANY, matchs[id][0], wxPoint(x, y-30));
	m_t_name[1] = new wxStaticText(this, wxID_ANY, matchs[id][0], wxPoint(x+dx, y-30));
	m_t_name[2] = new wxStaticText(this, wxID_ANY, matchs[id][1], wxPoint(x, y+dy-30));
	m_t_name[3] = new wxStaticText(this, wxID_ANY, matchs[id][1], wxPoint(x+dx, y+dy-30));
	for (int i = 0; i < 4; i++) {
		m_t_name[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}

	m_playerslist[0] = new wxListBox(this, wxID_ANY, wxPoint(x, y), wxSize(sx, sy));
	
	//Players list box1
	for (int i = 0; i < 22; i++) {
		wxString number;
		number << i+1;
		m_playerslist[0]->AppendString(matchs[id][0] + wxT(" player[") + number + "]");
	}
	m_playerslist[0]->SetSelection(0);
	m_playerslist[1] = new wxListBox(this, wxID_ANY, wxPoint(x + dx, y), wxSize(sx, sy));
	m_playerslist[2] = new wxListBox(this, wxID_ANY, wxPoint(x, y + dy), wxSize(sx, sy));
	
	//Players list box2
	for (int i = 0; i < 22; i++) {
		wxString number;
		number << i+1;
		m_playerslist[2]->AppendString(matchs[id][1] + wxT(" player[") + number + "]");
	}
	m_playerslist[2]->SetSelection(0);
	
	m_playerslist[3] = new wxListBox(this, wxID_ANY, wxPoint(x + dx, y + dy), wxSize(sx, sy));
	
	m_playeradd[0] = new wxButton(this, 10000,"Add player" ,wxPoint(x + 190, 125));
	m_playeradd[1] = new wxButton(this, 10002,"Add player" ,wxPoint(x + 190, 375));
	
	m_playeradd[0]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayeradd, this);
	m_playeradd[1]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayeradd, this);

	m_playeremove1 = new wxButton(this, 20001, " - ", wxPoint(x + 160, 125), wxDefaultSize, wxBU_EXACTFIT);
	m_playeremove2 = new wxButton(this, 20003, " - ", wxPoint(x + 160, 375), wxDefaultSize, wxBU_EXACTFIT);

	m_playeremove1->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayeremove, this);
	m_playeremove2->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayeremove, this);

	m_beginmatch = new wxButton(this, 22, "Begin Match", wxPoint(x + 187, 500));
	m_beginmatch->Enable(false);
	evt.Skip();
}

void cNextcreate::deletefunction(wxCommandEvent& evt) {
	if (f_groupselection == false) {
		for (int i = 0; i < 6; i++) {
			if (m_selectplayers[i]->IsEnabled() == false) {
				for (int j = 0; j < 4; j++) delete m_t_name[j];
				for (int j = 0; j < 4; j++) delete m_playerslist[j];
				delete m_playeradd[0];
				delete m_playeradd[1];
				delete m_playeremove1;
				delete m_playeremove2;
				delete m_beginmatch;
			}
		}
		for (int i = 0; i < 6;i++) delete m_selectplayers[i];
		for (int i = 0; i < 12; i++) delete teams[i];

	}
	delete m_title;
	delete m_groupselect;
	delete m_next;
	delete m_back;
	delete m_cancel;
	delete m_choice;
	evt.Skip();
}

void cNextcreate::onselectgroup(wxCommandEvent& evt) {
	//delete m_selectgroup;
	if (m_choice != nullptr) delete m_choice;
	m_choice = new wxChoice(this, 13, wxPoint(20, 120), wxSize(150, 240));
	for (int i = 1; i < 9; i++) {
		wxString s;
		s << i;
		m_choice->AppendString("Groupe " + s);
	}
	//m_choice->Select(0);
	//m_choice->Enable(true);
	evt.Skip();
}

void cNextcreate::b_next(wxCommandEvent& evt) {
	m_knockout_frame = new cKnockout();
	m_knockout_frame->Show();
	this->Close();
	evt.Skip();
}

void cNextcreate::onplayeradd(wxCommandEvent& evt) {
	int id = evt.GetId() - 10000;
	if (m_playerslist[id + 1]->GetCount() < 11) {
		wxString s = m_playerslist[id]->GetStringSelection();
		if (s != "") {
			m_playerslist[id + 1]->AppendString(s);
			m_playerslist[id]->Delete(m_playerslist[id]->GetSelection());
		}
		if (m_playerslist[id]->GetCount() > 0) m_playerslist[id]->SetSelection(0);
	}
	else wxMessageBox(wxT("Insert 11 players only please."));
	
	if (m_playerslist[1]->GetCount() == 11 && m_playerslist[3]->GetCount() == 11) m_beginmatch->Enable(true);
	else m_beginmatch->Enable(false);
	
	evt.Skip();
}

void cNextcreate::onplayeremove(wxCommandEvent& evt) {
	int Id = evt.GetId() - 20000;
	if (!m_playerslist[Id]->IsEmpty()) {
		m_playerslist[Id - 1]->AppendString(m_playerslist[Id]->GetString(m_playerslist[Id]->GetCount() - 1));
		m_playerslist[Id]->Delete(m_playerslist[Id]->GetCount() - 1);
	}
	m_beginmatch->Enable(false);
	evt.Skip();
}

void cNextcreate::onbeginmatch(wxCommandEvent& evt) {
	m_startmatch_frame = new cStartmatch();
	m_startmatch_frame->Show();
	evt.Skip();
}