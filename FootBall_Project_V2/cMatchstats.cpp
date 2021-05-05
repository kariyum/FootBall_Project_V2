#include "cMatchstats.h"
#include "cStartmatch.h"

wxBEGIN_EVENT_TABLE(cMatchstats, wxFrame)

wxEND_EVENT_TABLE()

cMatchstats::cMatchstats() : wxFrame(nullptr, wxID_ANY, "Menu", wxPoint(300, 50), wxSize(1240, 940), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN) {
	title = new wxStaticText(this, wxID_ANY, wxT("Match Stats"), wxPoint(10, 10), wxSize(-1, -1));
	title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));
	string winnerfile = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/winners.txt";
	vector<string> matchs = load_winners(winnerfile);

	matchs_choice = new wxChoice();
	matchs_choice->Create(this, wxID_ANY, wxPoint(10, 50), wxDefaultSize);
	matchs_choice->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &cMatchstats::onselection, this);
	
	vector<string> players;
	for (auto match : matchs) {
		string filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + separate(match)[0] + ";" + separate(match)[1]+".txt";
		players = load_players(filename);
		if (players.size() == 0) {
			//wxMessageBox("This match hasn't been played, or have been auto filled.");
		}
		else {
			matchs_choice->Append(separate(match)[0] + " VS " + separate(match)[1]);
		}
		//wxMessageBox(match);
		players.clear();
	}
	
	matchs_choice->SetSize(wxSize(250, -1));
	matchs_choice->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	panel1 = new wxPanel(this, wxID_ANY, wxPoint(10, 80), wxSize(1200, 800));
	panel1->SetBackgroundColour(this->GetBackgroundColour());
	

}

cMatchstats::~cMatchstats() {

}

void cMatchstats::onselection(wxCommandEvent& evt) {
	delete panel1;
	panel1 = new wxPanel(this, wxID_ANY, wxPoint(10, 80), wxSize(1200, 800));
	//panel1->SetBackgroundColour(this->GetBackgroundColour());
	panel1->SetBackgroundColour(wxColor(125, 153, 166));
	wxString team1, team2;
	vector<string> players;
	string resultat[22][3];
	vector<string> teams, notes, res;
	teams = matchstring(matchs_choice->GetStringSelection());
	string filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + teams[0] + ";" + teams[2] + ".txt";
	players = load_players(filename);
	filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + teams[0] + ";" + teams[2] + ";notes.txt";
	notes = load_players(filename);
	//for (int i = 0; i < players.size();i++) wxMessageBox(players[i]);
	filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + teams[0] + ";" + teams[2] + ";results.txt";
	res = load_players(filename);
	vector<string> sep;
	for (int i = 0; i < res.size(); i++) {
		sep = separate(res[i]);
		resultat[i][0] = sep[0];
		resultat[i][1] = sep[1];
		resultat[i][2] = sep[2];
	}
	//wxMessageBox(resultat[0][0] + " " + resultat[0][1]);
	cStartmatch* match = new cStartmatch(panel1, teams[0], teams[2], players, resultat, notes);
	match->Close();

	evt.Skip();
}

vector<string> cMatchstats::matchstring(wxString ch) {
	vector<string> res;
	res = separate_space(ch.ToStdString());
	return res;
}