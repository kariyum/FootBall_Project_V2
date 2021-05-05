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
EVT_BUTTON(16, onauto)
//EVT_BUTTON(1000, onplayerselection)
wxEND_EVENT_TABLE()

cNextcreate::cNextcreate() : wxFrame(nullptr, wxID_ANY, "Group Stage", wxPoint(250, 50), wxSize(1000 * 1.25, 600 * 1.25)) {
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

	m_cancel = new wxButton(this, 12, "Cancel", wxPoint(880 * 1.25, 530 * 1.25), wxDefaultSize);
	m_next = new wxButton(this, 15, "Next", wxPoint(880 * 1.25, 500 * 1.25));
	m_back = new wxButton(this, 14, "Back", wxPoint(797 * 1.25, 500 * 1.25));
	//m_delete = new wxButton(this, 20, "Delete", wxPoint(700 * 1.25, 530 * 1.25));
	m_autofill = new wxButton(this, 16, "Auto fill", wxPoint(20 * 1.25,530 * 1.25));
	m_autofill->Show(false);


	int x = 20;
	int y = 170;

	int dx = 200;
	int dy = 60;

	teams[0] = new wxStaticText(this, wxID_ANY, wxEmptyString , wxPoint(x * 1.25, y * 1.25));
	teams[1] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint((x + dx) * 1.25, y * 1.25));
	teams[2] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint(x * 1.25, (y + dy) * 1.25));
	teams[3] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint((x + dx) * 1.25, (y + dy) * 1.25));
	teams[4] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint(x * 1.25, (y + 2 * dy) * 1.25));
	teams[5] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint((x + dx) * 1.25, (y + 2*dy) * 1.25));
	teams[6] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint(x * 1.25, (y + 3 * dy) * 1.25));
	teams[7] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint((x + dx) * 1.25, (y + 3 * dy) * 1.25));
	teams[8] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint(x * 1.25, (y + 4 * dy) * 1.25));
	teams[9] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint((x + dx) * 1.25, (y + 4 * dy) * 1.25));
	teams[10] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint(x * 1.25, (y + 5 * dy) * 1.25));
	teams[11] = new wxStaticText(this, wxID_ANY, wxEmptyString, wxPoint((x + dx) * 1.25, (y + 5 * dy) * 1.25));

	for (int i = 0; i < 12; i++) {
		teams[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}

}

cNextcreate::~cNextcreate() {
	/*
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
	*/
}

void cNextcreate::deletefunction(wxCommandEvent& evt) {
	for (int i = 0;i < 12; i++) delete teams[i];
	evt.Skip();
}

void cNextcreate::ongroupselection(wxCommandEvent& evt) {
	m_autofill->Show(true);
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
		//for (int i = 0; i < 12; i++) delete teams[i];
	}
	f_groupselection = false;
	
	int x = 20;
	int y = 170;

	int dx = 200;
	int dy = 60;
	
	/*
	wxString s;
	s << m_choice->GetSelection() + 1 ;
	wxMessageBox(s);
	*/

	//gteams = new wxString[4];

	vector<string> groupe_matchs = load_group("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/groups.txt");
	groupe_teams = separate(groupe_matchs[m_choice->GetSelection()]);

	/*
	for (int i =0 ; i<4 ; i++) {
		wxString ss;
		ss << i +1;
		gteams[i].append(s +" TEAM["+ ss + "]");
	}
	*/

	
	matchs[0][0] = groupe_teams[0];
	matchs[0][1] = groupe_teams[1];
	
	matchs[1][0] = groupe_teams[0];
	matchs[1][1] = groupe_teams[2];
	
	matchs[2][0] = groupe_teams[0];
	matchs[2][1] = groupe_teams[3];

	matchs[3][0] = groupe_teams[1];
	matchs[3][1] = groupe_teams[2];

	matchs[4][0] = groupe_teams[1];
	matchs[4][1] = groupe_teams[3];

	matchs[5][0] = groupe_teams[2];
	matchs[5][1] = groupe_teams[3];

	for (int i = 0; i < 6; i++) {
		m_vs_title[i] = new wxStaticText(this, wxID_ANY, "VS", wxPoint(((x + dx) / 2 + 50) * 1.25, (y + i * dy) * 1.25));
		m_vs_title[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}

	
	m_selectplayers[0] = new wxButton(this, 1000, "Select players", wxPoint((x + 350) * 1.25, y * 1.25));
	
	/*
	teams[0] = new wxStaticText(this, wxID_ANY, matchs[0][0] , wxPoint(x * 1.25, y * 1.25));
	teams[1] = new wxStaticText(this, wxID_ANY, matchs[0][1], wxPoint((x + dx) * 1.25, y * 1.25));
	*/

	m_selectplayers[1] = new wxButton(this, 1001, "Select players", wxPoint((x + 350) * 1.25, (y + dy) * 1.25));
	/*
	teams[2] = new wxStaticText(this, wxID_ANY, matchs[1][0], wxPoint(x * 1.25, (y + dy) * 1.25));
	teams[3] = new wxStaticText(this, wxID_ANY, matchs[1][1], wxPoint((x + dx) * 1.25, (y + dy) * 1.25));
	*/

	m_selectplayers[2] = new wxButton(this, 1002, "Select players", wxPoint((x + 350) * 1.25, (y + 2 * dy) * 1.25));
	/*
	teams[4] = new wxStaticText(this, wxID_ANY, matchs[2][0], wxPoint(x * 1.25, (y + 2 * dy) * 1.25));
	teams[5] = new wxStaticText(this, wxID_ANY, matchs[2][1], wxPoint((x + dx) * 1.25, (y + 2*dy) * 1.25));
	*/

	m_selectplayers[3] = new wxButton(this, 1003, "Select players", wxPoint((x + 350) * 1.25, (y + 3 * dy) * 1.25));
	/*
	teams[6] = new wxStaticText(this, wxID_ANY, matchs[3][0], wxPoint(x * 1.25, (y + 3 * dy) * 1.25));
	teams[7] = new wxStaticText(this, wxID_ANY, matchs[3][1], wxPoint((x + dx) * 1.25, (y + 3 * dy) * 1.25));
	*/
	
	m_selectplayers[4] = new wxButton(this, 1004, "Select players", wxPoint((x + 350) * 1.25, (y + 4 * dy) * 1.25));
	/*
	teams[8] = new wxStaticText(this, wxID_ANY, matchs[4][0], wxPoint(x * 1.25, (y + 4 * dy) * 1.25));
	teams[9] = new wxStaticText(this, wxID_ANY, matchs[4][1], wxPoint((x + dx) * 1.25, (y + 4 * dy) * 1.25));
	*/

	m_selectplayers[5] = new wxButton(this, 1005, "Select players", wxPoint((x + 350) * 1.25, (y + 5 * dy) * 1.25));
	/*
	teams[10] = new wxStaticText(this, wxID_ANY, matchs[5][0], wxPoint(x * 1.25, (y + 5 * dy) * 1.25));
	teams[11] = new wxStaticText(this, wxID_ANY, matchs[5][1], wxPoint((x + dx) * 1.25, (y + 5 * dy) * 1.25));

	for (int i = 0; i < 12; i++) {
		teams[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}
	*/

	for (int i = 0; i < 12; i += 2) {
		teams[i]->SetLabel(matchs[i/2][0]);
		teams[i + 1]->SetLabel(matchs[i / 2][1]);
	}

	for (int i = 0; i < 6; i++) {
		m_selectplayers[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayerselection, this);
	}


	displaywinners();
	notification_done_matchs();

	evt.Skip();
}

void cNextcreate::onauto(wxCommandEvent& evt) {
	string filename_winners = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/winners.txt";
	vector<string> winner;
	string winner_line;
	wxString goal_string;
	for (int i = 0; i < 6; i++) {
		int goal = rand() % 2;
		goal_string << goal;
		if (m_selectplayers[i]->IsShown()) {
			winner_line = matchs[i][0] + ";" + matchs[i][1] + ";" + goal_string;
			winner.push_back(winner_line);
			//wxMessageBox(winner_line);
			goal_string = "";
		}
	}
	save_winners(winner, filename_winners);
	displaywinners();
	notification_done_matchs();
	evt.Skip();
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


void cNextcreate::displaywinners() {
	wxString winner;
	for (auto index : statictextdeleter) {
		delete m_winners[index];
	}
	statictextdeleter.clear();

	int x = 20;
	int y = 170;

	int dx = 200;
	int dy = 60;

	for (int i = 0; i < 6; i++) {
		if (!matchispending(matchs[i][0].ToStdString(), matchs[i][1].ToStdString(), winner)) {
			m_selectplayers[i]->Show(false);
			m_winners[i] = new wxStaticText(this, wxID_ANY, "->" + winner, wxPoint((x + 350) * 1.25, (y + dy * i) * 1.25));
			m_winners[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
			statictextdeleter.push_back(i);
		}
	}
}

void cNextcreate::onplayerselection(wxCommandEvent& evt) {
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
	}
	f_groupselection = false; // might cause memory access troubles

	int id = evt.GetId()-1000;
	for (int i = 0; i < 6; i++) {
		if (i == id) m_selectplayers[id]->Enable(false);
		else  m_selectplayers[i]->Enable(true);
	}
	int x = 500; // 500 480
	int y = 40;

	int dx = 300;
	int dy = 250;

	int sx = 150 * 1.25; //150 170
	int sy = 200 * 1.25;

	m_t_name[0] = new wxStaticText(this, wxID_ANY, matchs[id][0], wxPoint(x * 1.25, (y-30) * 1.25));
	m_t_name[1] = new wxStaticText(this, wxID_ANY, matchs[id][0], wxPoint((x+dx) * 1.25, (y-30) * 1.25));
	m_t_name[2] = new wxStaticText(this, wxID_ANY, matchs[id][1], wxPoint(x * 1.25, (y+dy-30) * 1.25));
	m_t_name[3] = new wxStaticText(this, wxID_ANY, matchs[id][1], wxPoint((x+dx) * 1.25, (y+dy-30) * 1.25));
	for (int i = 0; i < 4; i++) {
		m_t_name[i]->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL)); // 17
	}

	m_playerslist[0] = new wxListBox(this, wxID_ANY, wxPoint(x * 1.25, y * 1.25), wxSize(sx, sy));
	m_playerslist[1] = new wxListBox(this, wxID_ANY, wxPoint((x + dx) * 1.25, y * 1.25), wxSize(sx, sy));
	m_playerslist[2] = new wxListBox(this, wxID_ANY, wxPoint(x * 1.25, (y + dy) * 1.25), wxSize(sx, sy));
	m_playerslist[3] = new wxListBox(this, wxID_ANY, wxPoint((x + dx) * 1.25, (y + dy) * 1.25), wxSize(sx, sy));
	
	
	//Players list box1
	vector<string> players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + matchs[id][0].ToStdString() + ".txt");
	if (players.size() != 0) {
		for (int i = 0; i < players.size(); i++) m_playerslist[0]->AppendString(players[i]);

	}
	else {
		for (int i = 0; i < 22; i++) {
			wxString number;
			number << i + 1;
			m_playerslist[0]->AppendString(matchs[id][0] + wxT(" player[") + number + "]");
		}
	}
	m_playerslist[0]->SetSelection(0);

	//Players list box2
	players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + matchs[id][1].ToStdString() + ".txt");
	if (players.size() != 0) {
		for (auto player : players) m_playerslist[2]->AppendString(player);
	}
	else {
		for (int i = 0; i < 22; i++) {
			wxString number;
			number << i + 1;
			m_playerslist[2]->AppendString(matchs[id][1] + wxT(" player[") + number + "]");
		}
	}
	m_playerslist[2]->SetSelection(0);
	
	
	m_playeradd[0] = new wxButton(this, 10000,"Add player" ,wxPoint((x + 190) * 1.25, 125 * 1.25));
	m_playeradd[1] = new wxButton(this, 10002,"Add player" ,wxPoint((x + 190) * 1.25, 375 * 1.25));
	
	m_playeradd[0]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayeradd, this);
	m_playeradd[1]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayeradd, this);

	m_playeremove1 = new wxButton(this, 20001, " - ", wxPoint((x + 160) * 1.25, 125 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
	m_playeremove2 = new wxButton(this, 20003, " - ", wxPoint((x + 160) * 1.25, 375 * 1.25), wxDefaultSize, wxBU_EXACTFIT);

	m_playeremove1->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayeremove, this);
	m_playeremove2->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cNextcreate::onplayeremove, this);

	m_beginmatch = new wxButton(this, 22, "Begin Match", wxPoint((x + 187) * 1.25, 500 * 1.25));
	m_beginmatch->Enable(false);
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
				m_playerslist[id + 1]->AppendString(s);
				m_playerslist[id]->Delete(m_playerslist[id]->GetSelection());
			}
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
	vector<string> players1;

	for (int i = 0; i < 11; i++) {
		players1.push_back(m_playerslist[1]->GetString(i).ToStdString());
	}
	for (int i = 0;i < 11;i++)	players1.push_back(m_playerslist[3]->GetString(i).ToStdString());
	int id = 0;
	for (int i = 0; i < 6; i++) {
		if (m_selectplayers[i]->IsEnabled() == false) {
			id = i;
		}
	}
	wxString s = matchs[id][0] + ";" + matchs[id][1] + ".txt";

	save_groups(players1, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + s.ToStdString());

	m_startmatch_frame = new cStartmatch(matchs[id][0], matchs[id][1], players1, this);
	m_startmatch_frame->Show();
	evt.Skip();
}

bool cNextcreate::matchispending(string team1, string team2, wxString& winner){
	bool ans = true;
	vector<string> vector_winners = load_winners("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/winners.txt");
	vector<string> seperated_vector;
	for (auto line : vector_winners){
		seperated_vector = separate(line);
		if (team1 == seperated_vector[0] && team2 == seperated_vector[1]) {
			ans = false;
			int x = wxAtoi(seperated_vector[2]);
			if (x == 1) winner = seperated_vector[1];
			else winner = seperated_vector[0];
		}
	}
	wxString s;
	if (ans) s << 1;
	else s << 0;
	//wxMessageBox(s);
	return ans;
}

void cNextcreate::playerslistdelete() {
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
	f_groupselection = true;
}

void cNextcreate::notification_done_matchs() {
	bool ans = true;
	for (int i = 0; i < 6; i++) {
		if (m_selectplayers[i]->IsShown() == true) {
			ans = false;
		}
	}
	if (ans) {
		int score;
		wxString team[4];
		int scores[4];
		wxMessageBox("This groupe has no matchs left to play, please choose another group or procceed to the next stage.");
		for (int i = 0; i < 4; i++) {
			score = team_score(groupe_teams[i]);
			scores[i] = score;
			team[i] = groupe_teams[i];
		}
		// tri de tableaux
		for (int i = 0; i < 4; i++) {
			for (int j = i; j < 4; j++) {
				if (scores[i] < scores[j]) {
					int aux = scores[i];
					scores[i] = scores[j];
					scores[j] = aux;

					wxString team_aux = team[i];
					team[i] = team[j];
					team[j] = team_aux;
				}
			}
		}
		wxString s;
		for (int i = 0; i < 4; i++) {
			s = "";
			s << scores[i];
			//wxMessageBox(team[i] + " " + s);
			save_teamstats(team[i].ToStdString() + ";" + s.ToStdString());
		}
		wxString line;
		line = team[0] + ";" + team[1];
		save_runners(line.ToStdString());
	}
}

int cNextcreate::team_score(string team1) {
	int score = 0;
	//lecture men fichier winners
	//calcul du score = number of goals

	vector<string> vector_winners = load_winners("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/winners.txt");
	vector<string> seperated_vector;
	for (auto line : vector_winners) {
		seperated_vector = separate(line);
		if (team1 == seperated_vector[0]) {
			if (wxAtoi(seperated_vector[2]) == 0) score++;
		}
		else if (team1 == seperated_vector[1]) {
			if (wxAtoi(seperated_vector[2]) == 1) score++;
		}
	}
	wxString s;
	s << score;
	//wxMessageBox(s);
	return score;
}