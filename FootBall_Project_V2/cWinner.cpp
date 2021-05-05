#include "cWinner.h"
#include "wxBackgroundBitmap.h"

wxBEGIN_EVENT_TABLE(cWinner, wxFrame)
EVT_CLOSE(cWinner::onclose)
EVT_TIMER(1111, addsecond)
wxEND_EVENT_TABLE()

void cWinner::addsecond(wxTimerEvent& evt) {
	gif->Play();
	congratz->Play();
	//congradulation->SetPosition(wxPoint(congradulation->GetPosition().x + 1, congradulation->GetPosition().y));
	for (int i = 0; i < 4; i++) {
		if (us[i]->GetPosition().y > 0) us[i]->SetPosition(wxPoint(us[i]->GetPosition().x, us[i]->GetPosition().y - 1));
		else us[i]->SetPosition(wxPoint(us[i]->GetPosition().x, 750 * 1.44));
	}
}
cWinner::cWinner(wxString winnertext) : wxFrame(nullptr, wxID_ANY, "My frame", wxPoint(300 * 0, 100* 0), wxSize(1000 * 1.92, 750 * 1.44), wxICONIZE)
{
	gif = new wxMediaCtrl();
	//int ok = gif->Create(this, wxID_ANY, wxT("giphy.gif"), wxDefaultPosition, wxSize(1000 * 1.92, 700*1.44));
	int ok = gif->Create(this, wxID_ANY, wxT("giphy.gif"), wxPoint(456,0), wxSize(700 * 1.44, 700*1.44));
	if (!ok) wxMessageBox("Couldn't load file.");
	datetime = new wxTimer(this, 1111);
	datetime->Start(30);
	wxString winner = winnertext;
	congradulation = new wxStaticText(this, wxID_ANY, "Congradulations to " + winner, wxPoint(300 * 1.92 + 200, 700 * 1.44));
	congradulation->SetForegroundColour(wxColour(255, 255, 255));
	congradulation->SetFont(wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	this->SetBackgroundColour(wxColour(0, 0, 0));
	congratz = new wxMediaCtrl();
	congratz->Create(this, wxID_ANY, wxT("congratz.wav"));
	us[0] = new wxStaticText(this, wxID_ANY, "Karim Ben Amara", wxPoint(1500, 750 * 1.44));
	us[1] = new wxStaticText(this, wxID_ANY, "Iheb Haboubi", wxPoint(1500, 750 * 1.44 + 70));
	us[2] = new wxStaticText(this, wxID_ANY, "Motez Ouledissa", wxPoint(1500, 750 * 1.44 + 140));
	us[3] = new wxStaticText(this, wxID_ANY, "Synda Fhal", wxPoint(1500, 750 * 1.44 + 210));
	for (int i = 0; i < 4; i++) {
		us[i]->SetFont(wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
		us[i]->SetForegroundColour(wxColor(255, 255, 255));
	}
}

cWinner::~cWinner() {
	datetime->Stop();
	congratz->Stop();
	gif->Stop();
}

void cWinner::onclose(wxCloseEvent& evt) {
	Destroy();
}