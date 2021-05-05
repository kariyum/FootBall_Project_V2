#include "cPlayerselection.h"

BEGIN_EVENT_TABLE(cPlayerselection, wxFrame)


END_EVENT_TABLE()

cPlayerselection::cPlayerselection(wxString team1, wxString team2, cKnockout* parent_pointer) : wxFrame(nullptr, wxID_ANY, "Player selection", wxPoint(300, 150), wxSize(1000, 630)) {
	this->parent_pointer = parent_pointer;

	m_title = new wxStaticText(this, wxID_ANY, wxT("PLAYER SELECTION"), wxPoint(10, 10), wxSize(-1, -1));
	m_title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));

	wxFont teamfont = wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	team[0] = new wxStaticText(this, wxID_ANY, team1, wxPoint(250, 70));
	team[1] = new wxStaticText(this, wxID_ANY, team2, wxPoint(550, 310));
	team[2] = new wxStaticText(this, wxID_ANY, team2, wxPoint(250, 310));
	team[3] = new wxStaticText(this, wxID_ANY, team1, wxPoint(550, 70));
	for (int i = 0; i < 4;i++) team[i]->SetFont(teamfont);

	m_startmatch = new wxButton(this, wxID_ANY, "Start Match", wxPoint(750, 310));
	m_startmatch->Enable(false);
	m_startmatch->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cPlayerselection::onstartmatch, this);

	m_players[0] = new wxListBox(this, wxID_ANY, wxPoint(250, 100), wxSize(150, 200));
	m_players[1] = new wxListBox(this, wxID_ANY, wxPoint(550, 100), wxSize(150, 200));
	m_players[2] = new wxListBox(this, wxID_ANY, wxPoint(250, 340), wxSize(150, 200));
	m_players[3] = new wxListBox(this, wxID_ANY, wxPoint(550, 340), wxSize(150, 200));
	
	vector<string> players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + team1.ToStdString() + ".txt");
	if (players.size() != 0) {
		for (int i = 0; i < players.size(); i++) m_players[0]->AppendString(players[i]);

	}
	else {
		for (int i = 0; i < 22; i++) {
			wxString number;
			number << i + 1;
			m_players[0]->AppendString(team1 + wxT(" player[") + number + "]");
		}
	}
	players.clear(); //zeyda ama why not.
	players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + team2.ToStdString() + ".txt");
	if (players.size() != 0) {
		for (int i = 0; i < players.size(); i++) m_players[2]->AppendString(players[i]);

	}
	else {
		for (int i = 0; i < 22; i++) {
			wxString number;
			number << i + 1;
			m_players[2]->AppendString(team2 + wxT(" player[") + number + "]");
		}
	}

	m_players[0]->SetSelection(0);
	m_players[2]->SetSelection(0);


	add[0] = new wxButton(this, 0, "Add Player", wxPoint(440, 200));
	add[1] = new wxButton(this, 1, "Add Player", wxPoint(440, 220 + 200));
	add[0]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cPlayerselection::onplayeradd, this);
	add[1]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cPlayerselection::onplayeradd, this);


	remove[0] = new wxButton(this, 0, " - ", wxPoint(410, 200), wxSize(-1,-1), wxBU_EXACTFIT);
	remove[1] = new wxButton(this, 1, " - ", wxPoint(410, 220 + 200), wxSize(-1,-1),wxBU_EXACTFIT);
	remove[0]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cPlayerselection::onremove, this);
	remove[1]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cPlayerselection::onremove, this);
}

cPlayerselection::~cPlayerselection() {

}

void cPlayerselection::onplayeradd(wxCommandEvent& evt) {
	int Id = evt.GetId();
	if (Id == 1) Id++; 
	if (m_players[Id + 1]->GetCount() < 11) {
		wxString s = m_players[Id]->GetStringSelection();
		vector<string> suspended_players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/suspended.txt");
		bool suspended = false;
		for (int i = 0; i < suspended_players.size();i++) {
			vector<string> line = separate(suspended_players[i]);
			//wxMessageBox(suspended_players[i]);
			if (line[0] == s) {
				suspended = true;
			}
		}
		if (suspended) wxMessageBox("Please is suspended, please choose another one.");
		else {
			m_players[Id + 1]->AppendString(m_players[Id]->GetStringSelection());
			m_players[Id]->Delete(m_players[Id]->GetSelection());
			m_players[Id]->SetSelection(0);
		}
	}
	else wxMessageBox("Insert 11 players only please");
	if (m_players[2]->GetCount() == 11 && m_players[3]->GetCount() == 11) m_startmatch->Enable(true);
	else m_startmatch->Enable(false);

	evt.Skip();
}

void cPlayerselection::onremove(wxCommandEvent& evt) {
	int Id = evt.GetId();
	if (Id == 1) Id++;
	if (m_players[Id + 1]->GetCount() > 0) {
		m_players[Id]->AppendString(m_players[Id + 1]->GetString(m_players[Id + 1]->GetCount()-1));
		m_players[Id + 1]->Delete(m_players[Id+1]->GetCount()-1);
		m_players[Id]->SetSelection(0);
	}
	evt.Skip();
}

void cPlayerselection::onstartmatch(wxCommandEvent& evt) {
	wxString line = team[0]->GetLabel() + ";" + team[1]->GetLabel();
	for (int i = 0;i < 11;i++) players1.push_back(m_players[1]->GetString(i).ToStdString());
	for (int i = 0;i < 11;i++) players1.push_back(m_players[3]->GetString(i).ToStdString());
	save_groups(players1, line.ToStdString());

	m_startmatch_frame = new cStartmatch(team[0]->GetLabel(), team[1]->GetLabel(),players1, parent_pointer);
	m_startmatch_frame->Show();
	this->Close();
	evt.Skip();
}