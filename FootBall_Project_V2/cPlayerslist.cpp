#include "cPlayerslist.h"
#include <wx/infobar.h>
#include <wx/richtooltip.h>
#include <wx/cshelp.h>

wxBEGIN_EVENT_TABLE(cPlayerslist, wxFrame)
EVT_TIMER(1111, addsecond)

wxEND_EVENT_TABLE()

cPlayerslist::cPlayerslist() : wxFrame(nullptr, wxID_ANY, "Players List", wxPoint(300, 50), wxSize(800 * 1.25, 600 * 1.25)){
	windowtitle = new wxStaticText(this, wxID_ANY, "Players List", wxPoint(10, 10));
	windowtitle->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true));
	sorted = new wxStaticText(this, wxID_ANY, "sorted by number of goals.", wxPoint(20, 50));

	listbox = new wxListBox(this, wxID_ANY, wxPoint(10, 70), wxSize(250, 630));
	listbox->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	listbox->SetBackgroundColour(wxColor(125, 153, 166));

	vector<string> resultats;
	string filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/playerstats.txt";
	resultats = load_players(filename);
	pair<string, int> duo;

	vector<string> aux;
	for (auto res : resultats) {
		aux = separate_sus(res);
		duo.first = aux[0];
		int score = 0;
		score += 5 * wxAtoi(aux[1]);
		//score -= 4 * wxAtoi(aux[2]);
		//score -= 2 * wxAtoi(aux[3]);
		duo.second = score;
		map.push_back(duo);
	}

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < i - 1; j++) {
			if (map[j + 1].second > map[j].second) {
				duo = map[j];
				map[j] = map[j + 1];
				map[j + 1] = duo;
			}
		}
	}
	for (int i = 0; i < map.size(); i++) {
		wxString s;
		s << (i+1);
		listbox->Append(s + ". " +map[i].first);
	}
	wxString s;
	s << map[0].second;
	bestplayer = new wxStaticText(this, wxID_ANY, "Best Player \n" + map[0].first + " : " + s, wxPoint(650, 300));
	bestplayer->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	names = new wxStaticText * [map.size()];
	for (int i = 0; i < map.size(); i++) {
		wxString s;
		s << (i+1);
		names[i] = new wxStaticText(this, wxID_ANY, (s+ ". " + map[i].first), wxPoint(300, 300 + i * 50));
		names[i]->SetFont(wxFont(22, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}
	datetime = new wxTimer(this, 1111);
	datetime->Start(30);
}

cPlayerslist::~cPlayerslist() {
	datetime->Stop();
}

void cPlayerslist::addsecond(wxTimerEvent& evt) {
	for (int i = 0; i < map.size(); i++) {
		names[i]->SetPosition(wxPoint(names[i]->GetPosition().x, names[i]->GetPosition().y - 1));
		if (names[i]->GetPosition().y == 0) {
			names[i]->SetPosition(wxPoint(names[i]->GetPosition().x, map.size() * 50 + 300));
		}
	}

	evt.Skip();
}