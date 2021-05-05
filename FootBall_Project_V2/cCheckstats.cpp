#include "cCheckstats.h"
#include "wxBackgroundBitmap.h"
#include "cMenu1.h"

wxBEGIN_EVENT_TABLE(cCheckstats, wxFrame)
EVT_BUTTON(10, onback)
EVT_BUTTON(11, onmatchstats)
EVT_BUTTON(12, onplayerstats)
EVT_BUTTON(13, onteamstats)
EVT_BUTTON(14, onplayerslist)
EVT_BUTTON(15, onstatsteam)
wxEND_EVENT_TABLE()

cCheckstats::cCheckstats(): wxFrame(nullptr, wxID_ANY, "Menu", wxPoint(300, 50), wxSize(1000, 750)) {
	wxInitAllImageHandlers();
	wxBitmap TempBitmap;
	TempBitmap.LoadFile(wxT("checkstats.png"), wxBITMAP_TYPE_PNG);
	wxBackgroundBitmap* NotebookBackground = new wxBackgroundBitmap(TempBitmap);
	this->PushEventHandler(NotebookBackground);


	wxFont menu_font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	b_teamstats = new wxButton(this, 15, "Teams Stats", wxPoint(50 * 1.25, 250 * 1.25), wxSize(650 * 1.25, 38 * 1.25));
	b_teamstats->SetFont(menu_font);
	

	b_playerlist = new wxButton(this, 14, "Players Ordered List", wxPoint(50 * 1.25, 350 * 1.25), wxSize(650 * 1.25, 38 * 1.25));
	b_playerlist->SetFont(menu_font);

	b_teamslist = new wxButton(this, 13, "Teams Ordered List", wxPoint(50 * 1.25, 300 * 1.25), wxSize(650 * 1.25, 38 * 1.25));
	b_teamslist->SetFont(menu_font);

	//b_playerstats = new wxButton(this, 12, "Player Stats", wxPoint(50 * 1.25, 350 * 1.25), wxSize(650 * 1.25, 38 * 1.25));
	//b_playerstats->SetFont(menu_font);

	b_matchstats = new wxButton(this, 11, "Match Stats", wxPoint(50 * 1.25, 400 * 1.25), wxSize(650 * 1.25, 38 * 1.25));
	b_matchstats->SetFont(menu_font);

	m_back = new wxButton(this, 10, "Back", wxPoint(600 * 1.25, 475 * 1.25), wxSize(100 * 1.25, 38 * 1.25));
	m_back->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
}

cCheckstats::~cCheckstats() {
	Destroy();
	this->PopEventHandler(true);

}

void cCheckstats::onplayerslist(wxCommandEvent& evt) {
	cPlayerslist* playerslist_frame = new cPlayerslist();
	playerslist_frame->Show();
	evt.Skip();
}

void cCheckstats::onback(wxCommandEvent& evt) {
	cMenu1* frame = new cMenu1();
	frame->Show();
	this->Close();
	evt.Skip();
}

void cCheckstats::onplayerstats(wxCommandEvent& evt) {
	//cPlayerstats* players_stats_frame = new cPlayerstats();
	//players_stats_frame->Show();
	evt.Skip();
}

void cCheckstats::onteamstats(wxCommandEvent& evt) {
	cTeamstats* teamstats_frame = new cTeamstats();
	teamstats_frame->ShowWithEffect(wxSHOW_EFFECT_NONE, 1000);
	evt.Skip();
}

void cCheckstats::onmatchstats(wxCommandEvent& evt) {
	cMatchstats* matchstats_frame = new cMatchstats();
	matchstats_frame->Show();

	evt.Skip();
}

void cCheckstats::onstatsteam(wxCommandEvent& evt) {
	cStatsteam* statsteam_frame = new cStatsteam();
	statsteam_frame->Show();
	this->Close();
	evt.Skip();
}


