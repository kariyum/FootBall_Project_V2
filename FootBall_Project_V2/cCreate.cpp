#include "cCreate.h"
#include "cMenu1.h"
#include "cNewComp.h"
#include "cNextcreate.h"

wxBEGIN_EVENT_TABLE(cCreate, wxFrame)
EVT_BUTTON(12, b_cancel)
EVT_COMBOBOX(13, f_display)
EVT_BUTTON(14, b_back)
EVT_BUTTON(15, b_next)
EVT_BUTTON(1000, deletefunction)
wxEND_EVENT_TABLE()

cCreate::cCreate() : wxFrame(nullptr, wxID_ANY, "Create Window", wxPoint(300, 150), wxSize(1000, 600)) {
	m_select = new wxStaticText(this, wxID_ANY, wxT("Select Continent :"), wxPoint(20, 70), wxSize(-1, -1));
	m_select->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	m_create = new wxStaticText(this, wxID_ANY, wxT("Create"), wxPoint(10, 10), wxSize(-1, -1));
	m_create->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));

	m_cancel = new wxButton(this, 12, "Cancel", wxPoint(880, 530), wxDefaultSize);
	m_next = new wxButton(this, 15, "Next", wxPoint(880, 500));
	m_back = new wxButton(this, 14, "Back", wxPoint(797, 500));

	m_combobox = new wxComboBox(this, 13, "Select a Continent", wxPoint(20, 130), wxSize(150, 40), 0, NULL, wxCB_READONLY | wxCB_SORT);
	m_combobox->AppendString(wxT("Asia"));
	m_combobox->AppendString(wxT("Africa"));
	m_combobox->AppendString(wxT("South America"));
	m_combobox->AppendString(wxT("North America"));
	m_combobox->AppendString(wxT("Oceania"));
	m_combobox->AppendString(wxT("Europe"));
	//m_combobox->Select(0);

	//m_delete = new wxButton(this, 1000, "Delete", wxPoint(700, 500));
}

cCreate::~cCreate() {
	if (firstselection == true) {
		for (int i = 0; i < 8; i++) {
			delete m_groupe[i];
			delete m_b_groupe[i];
			delete m_b_rm[i];
		}
		delete m_continentlist;
	}
	delete m_select;
	delete m_create;
	delete m_cancel;
	delete m_next;
	delete m_combobox;
}

void cCreate::b_cancel(wxCommandEvent& evt) {
	m_menu1_frame = new cMenu1();
	m_menu1_frame->Show();
	this->Close();
	evt.Skip();
}

void cCreate::f_display(wxCommandEvent& evt) {
	//wxMessageBox(wxT("WORKS!"), wxT("Warning!"), wxICON_WARNING);
	//Read from files to display teams from that continent...
	if (firstselection == true) {
		for (int i = 0; i < 8; i++) {
			//delete m_groupe[i];
			//delete m_b_groupe[i];
			//delete m_b_rm[i];
		}
		delete m_continentlist;
	}

	m_continentlist = new wxListBox(this, wxID_ANY, wxPoint(20, 200), wxSize(150, 240));
	m_continentlist->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	bool added = false;
	for (int i = 0; i < 10; i++) {
		wxString s;
		s << i+1;
		if (firstselection == true) {
			for (int j = 0; j < 8; j++) {
				for (int k = 0; k < m_groupe[j]->GetCount(); k++) {
					if (m_groupe[j]->GetStrings()[k] == m_combobox->GetStringSelection() + s) added = true;
				}
			}
		}
		if (!added) m_continentlist->AppendString(m_combobox->GetStringSelection() + s); 
		added = false;
	}
	if (m_continentlist->GetCount() != 0) m_continentlist->SetSelection(0);
	if (firstselection == false) {
		m_groupe[0] = new wxListBox(this, 100, wxPoint(200, 40), wxSize(140, 170));
		m_groupe[1] = new wxListBox(this, 101, wxPoint(400, 40), wxSize(140, 170));
		m_groupe[2] = new wxListBox(this, 102, wxPoint(600, 40), wxSize(140, 170));
		m_groupe[3] = new wxListBox(this, 103, wxPoint(800, 40), wxSize(140, 170));
		m_groupe[4] = new wxListBox(this, 104, wxPoint(200, 270), wxSize(140, 170));
		m_groupe[5] = new wxListBox(this, 105, wxPoint(400, 270), wxSize(140, 170));
		m_groupe[6] = new wxListBox(this, 106, wxPoint(600, 270), wxSize(140, 170));
		m_groupe[7] = new wxListBox(this, 107, wxPoint(800, 270), wxSize(140, 170));
		for (int i = 0; i < 8; i++) m_groupe[i]->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		m_b_groupe[0] = new wxButton(this, 200, "Add to groupe 1", wxPoint(230, 230));
		m_b_groupe[1] = new wxButton(this, 201, "Add to groupe 2", wxPoint(430, 230));
		m_b_groupe[2] = new wxButton(this, 202, "Add to groupe 3", wxPoint(630, 230));
		m_b_groupe[3] = new wxButton(this, 203, "Add to groupe 4", wxPoint(830, 230));
		m_b_groupe[4] = new wxButton(this, 204, "Add to groupe 5", wxPoint(230, 465));
		m_b_groupe[5] = new wxButton(this, 205, "Add to groupe 6", wxPoint(430, 465));
		m_b_groupe[6] = new wxButton(this, 206, "Add to groupe 7", wxPoint(630, 465));
		m_b_groupe[7] = new wxButton(this, 207, "Add to groupe 8", wxPoint(830, 465));
		for (int i = 0; i < 8; i++) m_b_groupe[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cCreate::b_addteam, this);

		m_b_rm[0] = new wxButton(this, 300, " - ", wxPoint(203, 230), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[1] = new wxButton(this, 301, " - ", wxPoint(403, 230), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[2] = new wxButton(this, 302, " - ", wxPoint(603, 230), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[3] = new wxButton(this, 303, " - ", wxPoint(803, 230), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[4] = new wxButton(this, 304, " - ", wxPoint(203, 465), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[5] = new wxButton(this, 305, " - ", wxPoint(403, 465), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[6] = new wxButton(this, 306, " - ", wxPoint(603, 465), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[7] = new wxButton(this, 307, " - ", wxPoint(803, 465), wxDefaultSize, wxBU_EXACTFIT);
		for (int i = 0; i < 8; i++) m_b_rm[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cCreate::b_rm, this);
	}

	firstselection = true;
	evt.Skip();
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

void cCreate::b_addteam(wxCommandEvent& evt) {
	if (m_continentlist->GetStringSelection() != "") {
		int id = evt.GetId() - 200;
		if (m_groupe[id]->GetCount() < 4) {
			m_groupe[id]->AppendString(m_continentlist->GetStringSelection());
			m_continentlist->Delete(m_continentlist->GetSelection());
		}
		else wxMessageBox(wxT("This groupe is full, please choose another one."));
	}
	if (m_continentlist->GetCount()!=0) m_continentlist->SetSelection(0);
	evt.Skip();
}

void cCreate::b_rm(wxCommandEvent& evt) {
	int id = evt.GetId() - 300;
	m_groupe[id]->Deselect(m_groupe[id]->GetSelection());
	if (!m_groupe[id]->IsEmpty()) {
		m_continentlist->AppendString( (m_groupe[id]->GetStrings()[m_groupe[id]->GetCount() - 1]));
		m_groupe[id]->Delete(m_groupe[id]->GetCount() - 1);
	}
	evt.Skip();
}

void cCreate::deletefunction(wxCommandEvent& evt) {
	if (firstselection == true) {
		for (int i = 0; i < 8; i++) {
			delete m_groupe[i];
			delete m_b_groupe[i];
			delete m_b_rm[i];
		}
		delete m_continentlist;
	}
	evt.Skip();
}