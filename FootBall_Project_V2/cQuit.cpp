#include "cQuit.h"
#include "cMenu1.h"

wxBEGIN_EVENT_TABLE(cQuit, wxFrame)
EVT_BUTTON(3, b_cancel)
EVT_BUTTON(2, b_yes)
wxEND_EVENT_TABLE()

cQuit::cQuit(cMenu1* ptr_menu1) : wxFrame(nullptr, wxID_ANY, "Exit Window", wxPoint(500, 250), wxSize(400, 225), wxSYSTEM_MENU | wxCAPTION | wxCLIP_CHILDREN) {
	wxFont myfont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	
	m_sure = new wxStaticText(this, wxID_ANY, "Are you sure you want to exit?", wxPoint(60, 60));
	m_sure->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	int x = 85;
	int y = 125;
	int dx = 130;

	int sx = 90;
	int sy = 30;
	m_yes = new wxButton(this, 2, "Yes",wxPoint(x, y), wxSize(sx, sy));
	m_cancel = new wxButton(this, 3, "Cancel", wxPoint(x + dx, y-3), wxSize(sx, sy+6));
	m_cancel->SetBackgroundColour(wxColor(251, 94, 94));

	m_yes->SetFont(myfont);
	m_cancel->SetFont(myfont);

	ptr_menu1_att = ptr_menu1; //ptr_menu1 is an automatic variable...
}

cQuit::~cQuit() {
}

void cQuit::b_yes(wxCommandEvent& evt) {
	((cMenu1*)ptr_menu1_att)->Close();
	this->Close();
	evt.Skip();
}
void cQuit::b_cancel(wxCommandEvent& evt) {
	ptr_menu1_att->Enable();
	this->Close();
	evt.Skip();
}