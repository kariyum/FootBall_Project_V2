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
//EVT_CLOSE(onclose)
wxEND_EVENT_TABLE()

void cCreate::onclose(wxCloseEvent& evt) {
	Destroy();
	this->PopEventHandler(true);
}

cCreate::cCreate() : wxFrame(nullptr, wxID_ANY, "Create Window", wxPoint(250, 50), wxSize(1000 * 1.25, 600 * 1.25)) {

	m_select = new wxStaticText(this, wxID_ANY, wxT("Select Continent :"), wxPoint(20, 70), wxSize(-1, -1));
	m_select->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	m_create = new wxStaticText(this, wxID_ANY, wxT("Create"), wxPoint(10, 10), wxSize(-1, -1));
	m_create->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));

	m_cancel = new wxButton(this, 12, "Cancel", wxPoint(880 * 1.25, 530 * 1.25), wxDefaultSize);
	m_next = new wxButton(this, 15, "Next", wxPoint(880 * 1.25, 500 * 1.25));
	//m_back = new wxButton(this, 14, "Back", wxPoint(797, 500));
	m_next->Enable(false);

	m_combobox = new wxComboBox(this, 13, "Select a Continent", wxPoint(20, 130), wxSize(150, 40), 0, NULL, wxCB_READONLY | wxCB_SORT);
	m_combobox->AppendString(wxT("Asia"));
	m_combobox->AppendString(wxT("Africa"));
	m_combobox->AppendString(wxT("South America"));
	m_combobox->AppendString(wxT("North America"));
	m_combobox->AppendString(wxT("Oceania"));
	m_combobox->AppendString(wxT("Europe"));
	//m_combobox->Select(0);

	//m_delete = new wxButton(this, 1000, "Delete", wxPoint(700, 500));
	initializetab();
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
	//evt.Skip();
}

void cCreate::f_display(wxCommandEvent& evt) {
	//wxMessageBox(wxT("WORKS!"), wxT("Warning!"), wxICON_WARNING);
	//Read from files to display teams from that continent...
	m_next->Enable(true);

	bool added = false;

	wxString continent_string = m_combobox->GetStringSelection();
	if (continent_string == "Asia") continent_string = "asia.txt";
	if (continent_string == "Africa") continent_string = "africa.txt";
	if (continent_string == "South America") continent_string = "south_america.txt";
	if (continent_string == "North America") continent_string = "north_america.txt";
	if (continent_string == "Oceania") continent_string = "oceania.txt";
	if (continent_string == "Europe") continent_string = "europe.txt";
	
	continent_string = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/continents/" + continent_string;
	string chaine;
	chaine = continent_string.wxString::ToStdString();
	vector<string> vector_continent = load_continent(chaine);
	
	//used to print the number of teams
	//wxString s1;
	//s1 << vector_continent.size();
	//wxMessageBox(m_combobox->GetStringSelection() + " has " + s1 + " teams.");
	
	//delets the listbox if it has been created previously
	if (firstselection == true) {
		for (int i = 0; i < 8; i++) {
			//delete m_groupe[i];
			//delete m_b_groupe[i];
			//delete m_b_rm[i];
		}
		delete m_continentlist;
	}
	m_continentlist = new wxListBox(this, wxID_ANY, wxPoint(20 * 1.25, 200 * 1.25), wxSize(150 * 1.25, 240 * 1.25));
	m_continentlist->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	//checks if the team hasn't been added yet if so it adds it to the list box.
	for (int i = 0; i < vector_continent.size(); i++) {
		wxString s;
		s << i+1;
		if (firstselection == true) {
			for (int j = 0; j < 8; j++) {
				for (int k = 0; k < m_groupe[j]->GetCount(); k++) {
					//if (m_groupe[j]->GetStrings()[k] == m_combobox->GetStringSelection() + s) added = true;
					if (m_groupe[j]->GetStrings()[k] == vector_continent[i]) added = true;

				}
			}
		}
		//if (!added) m_continentlist->AppendString(m_combobox->GetStringSelection() + s); 
		if (!added) m_continentlist->AppendString(vector_continent[i]); 
		added = false;
	}

	if (m_continentlist->GetCount() != 0) m_continentlist->SetSelection(0);
	if (firstselection == false) {
		m_groupe[0] = new wxListBox(this, 100, wxPoint(200 * 1.25, 40 * 1.25), wxSize(140 * 1.25, 170 * 1.25));
		m_groupe[1] = new wxListBox(this, 101, wxPoint(400 * 1.25, 40 * 1.25), wxSize(140 * 1.25, 170 * 1.25));
		m_groupe[2] = new wxListBox(this, 102, wxPoint(600 * 1.25, 40 * 1.25), wxSize(140 * 1.25, 170 * 1.25));
		m_groupe[3] = new wxListBox(this, 103, wxPoint(800 * 1.25, 40 * 1.25), wxSize(140 * 1.25, 170 * 1.25));
		m_groupe[4] = new wxListBox(this, 104, wxPoint(200 * 1.25, 270 * 1.25), wxSize(140 * 1.25, 170 * 1.25));
		m_groupe[5] = new wxListBox(this, 105, wxPoint(400 * 1.25, 270 * 1.25), wxSize(140 * 1.25, 170 * 1.25));
		m_groupe[6] = new wxListBox(this, 106, wxPoint(600 * 1.25, 270 * 1.25), wxSize(140 * 1.25, 170 * 1.25));
		m_groupe[7] = new wxListBox(this, 107, wxPoint(800 * 1.25, 270 * 1.25), wxSize(140 * 1.25, 170 * 1.25));
		for (int i = 0; i < 8; i++) m_groupe[i]->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		m_b_groupe[0] = new wxButton(this, 200, "Add to groupe 1", wxPoint(230 * 1.25, 230 * 1.25));
		m_b_groupe[1] = new wxButton(this, 201, "Add to groupe 2", wxPoint(430 * 1.25, 230 * 1.25));
		m_b_groupe[2] = new wxButton(this, 202, "Add to groupe 3", wxPoint(630 * 1.25, 230 * 1.25));
		m_b_groupe[3] = new wxButton(this, 203, "Add to groupe 4", wxPoint(830 * 1.25, 230 * 1.25));
		m_b_groupe[4] = new wxButton(this, 204, "Add to groupe 5", wxPoint(230 * 1.25, 465 * 1.25));
		m_b_groupe[5] = new wxButton(this, 205, "Add to groupe 6", wxPoint(430 * 1.25, 465 * 1.25));
		m_b_groupe[6] = new wxButton(this, 206, "Add to groupe 7", wxPoint(630 * 1.25, 465 * 1.25));
		m_b_groupe[7] = new wxButton(this, 207, "Add to groupe 8", wxPoint(830 * 1.25, 465 * 1.25));
		for (int i = 0; i < 8; i++) m_b_groupe[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cCreate::b_addteam, this);

		m_b_rm[0] = new wxButton(this, 300, " - ", wxPoint(203 * 1.25, 230 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[1] = new wxButton(this, 301, " - ", wxPoint(403 * 1.25, 230 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[2] = new wxButton(this, 302, " - ", wxPoint(603 * 1.25, 230 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[3] = new wxButton(this, 303, " - ", wxPoint(803 * 1.25, 230 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[4] = new wxButton(this, 304, " - ", wxPoint(203 * 1.25, 465 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[5] = new wxButton(this, 305, " - ", wxPoint(403 * 1.25, 465 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[6] = new wxButton(this, 306, " - ", wxPoint(603 * 1.25, 465 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
		m_b_rm[7] = new wxButton(this, 307, " - ", wxPoint(803 * 1.25, 465 * 1.25), wxDefaultSize, wxBU_EXACTFIT);
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
	//creats a file with groups
	bool groups_are_full = true;
	for (int i = 0; i < 8;i++) if (m_groupe[i]->GetCount() < 4) groups_are_full = false;
	if (!groups_are_full) wxMessageBox(wxT("Please make sure that all groups contains 4 teams each."));
	else {
		vector<string> groups_tab;
		string line = "";
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				line += m_groupe[i]->GetString(j) + ";";
			}
			//wxMessageBox(line);
			groups_tab.push_back(line);
			line = "";
		}
		//wxMessageBox(groups_tab[0]);
		save_groups(groups_tab, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/groups.txt");
		m_nextcreate_frame = new cNextcreate();
		m_nextcreate_frame->Show();

		this->Close();
	}
	/*
	m_nextcreate_frame = new cNextcreate();
	m_nextcreate_frame->Show();

	this->Close();
	*/

	evt.Skip();
}

void cCreate::b_addteam(wxCommandEvent& evt) {
	if (m_continentlist->GetStringSelection() != "") {
		int id = evt.GetId() - 200;
		wxString continent_string = m_combobox->GetStringSelection();
		int id1 = 0;
		if (continent_string == "Asia") id1 = 0;
		if (continent_string == "Africa") id1 = 1;
		if (continent_string == "South America") id1 = 2;
		if (continent_string == "North America") id1 = 3;
		if (continent_string == "Oceania") id1 = 4;
		if (continent_string == "Europe") id1 = 5;
		
		if (m_groupe[id]->GetCount() < 4) {
			if (teams_tab[id][id1] == 2) {
				wxMessageBox(wxT("This groupe is full of " + continent_string + " teams."));
			}
			else {
				group_names.push_back(make_pair(m_continentlist->GetStringSelection(), continent_string));
				m_groupe[id]->AppendString(m_continentlist->GetStringSelection());
				m_continentlist->Delete(m_continentlist->GetSelection());
				teams_tab[id][id1]++;
			}
		}
		else wxMessageBox(wxT("This groupe is full, please choose another one."));
	}
	if (m_continentlist->GetCount()!=0) m_continentlist->SetSelection(0);
	evt.Skip();
}

void cCreate::b_rm(wxCommandEvent& evt) {
	int id = evt.GetId() - 300;
	m_groupe[id]->Deselect(m_groupe[id]->GetSelection());

	wxString continent_string = m_combobox->GetStringSelection();
	int id1 = 0;
	if (continent_string == "Asia") id1 = 0;
	if (continent_string == "Africa") id1 = 1;
	if (continent_string == "South America") id1 = 2;
	if (continent_string == "North America") id1 = 3;
	if (continent_string == "Oceania") id1 = 4;
	if (continent_string == "Europe") id1 = 5;

	if (!m_groupe[id]->IsEmpty()) {
		for (auto pair : group_names) {
			if (pair.first == m_groupe[id]->GetStrings()[m_groupe[id]->GetCount() - 1]) {
				continent_string = pair.second;
				if (continent_string == "Asia") id1 = 0;
				if (continent_string == "Africa") id1 = 1;
				if (continent_string == "South America") id1 = 2;
				if (continent_string == "North America") id1 = 3;
				if (continent_string == "Oceania") id1 = 4;
				if (continent_string == "Europe") id1 = 5;
			}
		}
		if (continent_string == m_combobox->GetStringSelection()) {
			m_continentlist->AppendString((m_groupe[id]->GetStrings()[m_groupe[id]->GetCount() - 1]));
		}
		m_groupe[id]->Delete(m_groupe[id]->GetCount() - 1);
		teams_tab[id][id1]--;
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


void cCreate::initializetab() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			teams_tab[i][j] = 0;
		}
	}
}