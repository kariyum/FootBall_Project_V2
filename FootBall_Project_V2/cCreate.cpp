#include "cCreate.h"
#include "cMenu1.h"
#include "cNewComp.h"
#include "cNextcreate.h"

wxBEGIN_EVENT_TABLE(cCreate, wxFrame)
EVT_BUTTON(12, b_cancel)
EVT_COMBOBOX(13, f_display)
EVT_BUTTON(14, b_back)
EVT_BUTTON(15, b_next)
wxEND_EVENT_TABLE()

cCreate::cCreate() : wxFrame(nullptr, wxID_ANY, "Create Window", wxPoint(300, 150), wxSize(1000, 600)) {
	m_select = new wxStaticText(this, wxID_ANY, wxT("Select Continent :"), wxPoint(20, 70), wxSize(-1, -1));
	m_select->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	m_create = new wxStaticText(this, wxID_ANY, wxT("Create"), wxPoint(10, 10), wxSize(-1, -1));
	m_create->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));

	m_cancel = new wxButton(this, 12, "Cancel", wxPoint(880, 530), wxDefaultSize);
	m_next = new wxButton(this, 15, "Next", wxPoint(880, 500));
	m_back = new wxButton(this, 14, "Back", wxPoint(797, 500));

	m_continentlist = new wxListBox(this, wxID_ANY, wxPoint(20, 200), wxSize(150, 240));

	m_groupe1 = new wxListBox(this, wxID_ANY, wxPoint(200, 40), wxSize(140, 170));
	m_groupe2 = new wxListBox(this, wxID_ANY, wxPoint(400, 40), wxSize(140, 170));
	m_groupe3 = new wxListBox(this, wxID_ANY, wxPoint(600, 40), wxSize(140, 170));
	m_groupe4 = new wxListBox(this, wxID_ANY, wxPoint(800, 40), wxSize(140, 170));
	m_groupe5 = new wxListBox(this, wxID_ANY, wxPoint(200, 270), wxSize(140, 170));
	m_groupe6 = new wxListBox(this, wxID_ANY, wxPoint(400, 270), wxSize(140, 170));
	m_groupe7 = new wxListBox(this, wxID_ANY, wxPoint(600, 270), wxSize(140, 170));
	m_groupe8 = new wxListBox(this, wxID_ANY, wxPoint(800, 270), wxSize(140, 170));

	m_combobox = new wxComboBox(this, 13, "Select a Continent", wxPoint(20, 130), wxSize(150, 40), 0, NULL, wxCB_READONLY | wxCB_SORT);
	m_combobox->AppendString(wxT("Asia"));
	m_combobox->AppendString(wxT("Africa"));
	m_combobox->AppendString(wxT("South America	"));
	m_combobox->AppendString(wxT("North America"));
	m_combobox->AppendString(wxT("Oceania"));
	m_combobox->AppendString(wxT("Europe"));
	m_combobox->Select(0);

	m_b_groupe1 = new wxButton(this, wxID_ANY, "Add to groupe 1", wxPoint(230, 230));
	m_b_groupe2 = new wxButton(this, wxID_ANY, "Add to groupe 2", wxPoint(430, 230));
	m_b_groupe3 = new wxButton(this, wxID_ANY, "Add to groupe 3", wxPoint(630, 230));
	m_b_groupe4 = new wxButton(this, wxID_ANY, "Add to groupe 4", wxPoint(830, 230));
	m_b_groupe5 = new wxButton(this, wxID_ANY, "Add to groupe 5", wxPoint(230, 465));
	m_b_groupe6 = new wxButton(this, wxID_ANY, "Add to groupe 6", wxPoint(430, 465));
	m_b_groupe7 = new wxButton(this, wxID_ANY, "Add to groupe 7", wxPoint(630, 465));
	m_b_groupe8 = new wxButton(this, wxID_ANY, "Add to groupe 8", wxPoint(830, 465));

	m_b_rm1 = new wxButton(this, wxID_ANY, " - ", wxPoint(203, 230), wxDefaultSize, wxBU_EXACTFIT);
	m_b_rm2 = new wxButton(this, wxID_ANY, " - ", wxPoint(403, 230), wxDefaultSize, wxBU_EXACTFIT);
	m_b_rm3 = new wxButton(this, wxID_ANY, " - ", wxPoint(603, 230), wxDefaultSize, wxBU_EXACTFIT);
	m_b_rm4 = new wxButton(this, wxID_ANY, " - ", wxPoint(803, 230), wxDefaultSize, wxBU_EXACTFIT);
	m_b_rm5 = new wxButton(this, wxID_ANY, " - ", wxPoint(203, 465), wxDefaultSize, wxBU_EXACTFIT);
	m_b_rm6 = new wxButton(this, wxID_ANY, " - ", wxPoint(403, 465), wxDefaultSize, wxBU_EXACTFIT);
	m_b_rm7 = new wxButton(this, wxID_ANY, " - ", wxPoint(603, 465), wxDefaultSize, wxBU_EXACTFIT);
	m_b_rm8 = new wxButton(this, wxID_ANY, " - ", wxPoint(803, 465), wxDefaultSize, wxBU_EXACTFIT);

}

cCreate::~cCreate() {

}

void cCreate::b_cancel(wxCommandEvent& evt) {
	m_menu1_frame = new cMenu1();
	m_menu1_frame->Show();
	this->Close();
	evt.Skip();
}

void cCreate::f_display(wxCommandEvent& evt) {
	wxMessageBox(wxT("WORKS!"), wxT("Warning!"), wxICON_WARNING);
	//Read from files to display teams from that continent...
}

void cCreate::b_back(wxCommandEvent& evt) {
	m_newcomp_frame = new cNewComp();
	m_newcomp_frame->Show();
	this->Close();
	evt.Skip();
}

void cCreate::b_next(wxCommandEvent& evt) {
	m_nextcreate_frame = new cNextcreate();
	m_nextcreate_frame->Show();
	this->Close();
	evt.Skip();
}