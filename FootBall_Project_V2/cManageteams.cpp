#include "cManageteams.h"

cManageteams::cManageteams() : wxFrame(nullptr, wxID_ANY, "Team Management", wxPoint(300, 50), wxSize(1200, 750)) {
	wxFont myfont = wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont myfont1 = wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	title = new wxStaticText(this, wxID_ANY, "Team Management", wxPoint(20, 10));
	title->SetFont(wxFont(26, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));

	addteam[0] = new wxButton(this, 0, "Add Player", wxPoint(720, 190));
	teamslistbox = new wxListBox(this, wxID_ANY, wxPoint(20, 150), wxSize(250, 400));
	teamslistbox->SetFont(myfont);

	teams_name[0] = new wxStaticText(this, wxID_ANY, "Algeria", wxPoint(420, 100));
	teams_name[0]->SetFont(myfont1);

	playerslistbox[0] = new wxListBox(this, wxID_ANY, wxPoint(420, 150), wxSize(250, 400));
	playerslistbox[1] = new wxListBox(this, wxID_ANY, wxPoint(820, 150), wxSize(250, 330));

	teams_name[1] = new wxStaticText(this, wxID_ANY, "Algeria", wxPoint(820, 100));
	teams_name[1]->SetFont(myfont1);

	team_label = new wxStaticText(this, wxID_ANY, "Teams", wxPoint(20, 100));
	team_label->SetFont(myfont1);
	vector<string> players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/Algeria.txt");
	if (players.size() != 0) {
		for (int i = 0; i < players.size(); i++) playerslistbox[0]->AppendString(players[i]);

	}
	else {
		for (int i = 0; i < 33; i++) {
			wxString s = "Algeria Player[";
			s << i + 1;
			s += ']';
			playerslistbox[0]->AppendString(s);
		}
	}
	playerslistbox[0]->SetFont(myfont);
	playerslistbox[0]->SetSelection(0);
	playerslistbox[1]->SetFont(myfont);

	deleteteam[0] = new wxButton(this, wxID_ANY, " - ", wxPoint(690, 190), wxSize(-1, -1), wxBU_EXACTFIT);

	playername = new wxTextCtrl(this, wxID_ANY, "", wxPoint(820, 520), wxSize(250, 30));
	playername->SetFont(myfont);
	addteam[1] = new wxButton(this, 1, "Add Player", wxPoint(850, 490));
	deleteteam[1] = new wxButton(this, wxID_ANY, " - ", wxPoint(820, 490), wxSize(-1, -1), wxBU_EXACTFIT);
	for (int i = 0; i < 2; i++) addteam[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cManageteams::onaddplayer, this);
	for (int i = 0; i < 2; i++) deleteteam[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cManageteams::onremoveplayer, this);
	vector<string> continent = { "africa.txt", "asia.txt", "oceania.txt", "europe.txt", "south_america.txt", "north_america.txt" };
	for (auto con : continent) {
		players = load_continent("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/continents/" + con);
		for (auto line : players) teamslistbox->AppendString(line);
	}
	teamslistbox->SetSelection(0);
	selectteam = new wxButton(this, wxID_ANY, "Select team", wxPoint(300, 190));
	selectteam->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cManageteams::onselectteam, this);
	saveteam = new wxButton(this, wxID_ANY, "Save team", wxPoint(1090, 190));
	saveteam->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cManageteams::onsaveteam, this);
	teamname = "Algeria";
}

cManageteams::~cManageteams() {

}

void cManageteams::onaddplayer(wxCommandEvent& evt) {
	if (playerslistbox[1]->GetCount() == 22) {
		wxMessageBox("22 players are inserted");
	}
	else {
		int Id = evt.GetId();
		if (Id == 0) {
			if (playerslistbox[0]->GetCount() != 0) {
				playerslistbox[1]->AppendString(playerslistbox[0]->GetStringSelection());
				playerslistbox[0]->Delete(playerslistbox[0]->GetSelection());
				if (playerslistbox[0]->GetCount() != 0)  playerslistbox[0]->SetSelection(0);
			}
		}
		else {
			if (playername->GetValue() != "") {
				playerslistbox[1]->AppendString(playername->GetValue());
				playername->Clear();
			}
		}
	}
	playerslistbox[1]->PageDown();
	evt.Skip();
}

void cManageteams::onremoveplayer(wxCommandEvent& evt) {
	if (playerslistbox[1]->GetCount() != 0) {
		playerslistbox[1]->Delete(playerslistbox[1]->GetCount()-1);
	}
	evt.Skip();
}

void cManageteams::onselectteam(wxCommandEvent& evt) {
	if (teamslistbox->GetStringSelection() != "") {
		teams_name[0]->SetLabel(teamslistbox->GetStringSelection());
		teams_name[1]->SetLabel(teamslistbox->GetStringSelection());
		teamname = teamslistbox->GetStringSelection();
		playerslistbox[0]->Clear();
		playerslistbox[1]->Clear();
		vector<string> players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + teamslistbox->GetStringSelection().ToStdString() + ".txt");
		if (players.size() != 0) {
			for (int i = 0; i < players.size(); i++) playerslistbox[0]->AppendString(players[i]);

		}
		else {
			for (int i = 0; i < 33; i++) {
				wxString s = teamslistbox->GetStringSelection() + " Player[";
				s << i + 1;
				s += ']';
				playerslistbox[0]->AppendString(s);
			}
		}
		playerslistbox[0]->SetSelection(0);
	}
	evt.Skip();
}

void cManageteams::onsaveteam(wxCommandEvent& evt) {
	if (playerslistbox[1]->GetCount() != 22) {
		wxMessageBox("Please add 22 players");
	}
	else{
		players.clear();
		for (int i = 0; i < playerslistbox[1]->GetCount(); i++) {
			players.push_back(playerslistbox[1]->GetString(i).ToStdString());
		}
		save_groups(players, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + teamname + ".txt");
		wxMessageBox("Saving done successfully !");
	}
	evt.Skip();
}