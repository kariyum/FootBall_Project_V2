#include "cTeamstats.h"
wxBEGIN_EVENT_TABLE(cTeamstats, wxFrame)
EVT_TIMER(1111, addsecond)

wxEND_EVENT_TABLE()
cTeamstats::cTeamstats() : wxFrame(nullptr, wxID_ANY, "Menu", wxPoint(300, 50), wxSize(800 * 1.25, 600 * 1.25), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN) {
	windowtitle = new wxStaticText(this, wxID_ANY, "Team Stats", wxPoint(10, 10));
	windowtitle->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true));

	listbox = new wxListBox(this, wxID_ANY, wxPoint(10, 50), wxSize(200,650));
	listbox->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	listbox->SetBackgroundColour(wxColor(125, 153, 166));
	vector<string> res;
	string filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/teamstats.txt";
	res = load_players(filename);
	vector<string> sep_res;
	pair<int, string> duo;
	for (auto r : res) {
		sep_res = separate_sus(r);
		duo.first = wxAtoi(sep_res[1]);
		duo.second = sep_res[0];
		map.push_back(duo);
	}
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < i - 1; j++) {
			if (map[j + 1].first > map[j].first) {
				duo = map[j];
				map[j] = map[j + 1];
				map[j + 1] = duo;
			}
		}
	}
	for (auto m : map) {
		listbox->Append(m.second);
	}
	names = new wxStaticText * [map.size()];
	for (int i = 0; i < map.size(); i++) {
		names[i] = new wxStaticText(this, wxID_ANY, map[i].second, wxPoint(300,300 + i * 50));
		names[i]->SetFont(wxFont(22, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}
	datetime = new wxTimer(this, 1111);
	datetime->Start(30);
}

cTeamstats::~cTeamstats() {
	datetime->Stop();
}

void cTeamstats::addsecond(wxTimerEvent& evt) {
	for (int i = 0; i < map.size(); i++) {
		names[i]->SetPosition(wxPoint(names[i]->GetPosition().x, names[i]->GetPosition().y - 1));
		if (names[i]->GetPosition().y == 0) {
			names[i]->SetPosition(wxPoint(names[i]->GetPosition().x, map.size() * 50 + 300));
		}
	}
	evt.Skip();
}