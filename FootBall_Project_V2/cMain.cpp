#include "cMain.h" 
#include<fstream>
#include<iostream>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, OnConnect)
EVT_CHECKBOX(10002, ShowPassword)
EVT_CLOSE(cMain::OnClose)
EVT_BUTTON(12, cMain::onPlay)
EVT_TEXT_ENTER(100, cMain::OnConnect)
wxEND_EVENT_TABLE()

void cMain::onPlay(wxCommandEvent& evt){
	if (!isbeingplayed) {
		kawafel->Play();
		isbeingplayed = true;
		playbutton->SetLabel("| |");
	}
	else {
		isbeingplayed = false;
		kawafel->Pause();
		playbutton->SetLabel("|>");
	}
	kawafel->SetVolume(0.3f);
}
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Football Competition Management", wxPoint(300, 50), wxSize(800 * 1.25, 600 * 1.25), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN) {
	wxInitAllImageHandlers();
	wxBitmap TempBitmap;
	TempBitmap.LoadFile(wxT("login6.jpg"), wxBITMAP_TYPE_JPEG);
	wxBackgroundBitmap* NotebookBackground = new wxBackgroundBitmap(TempBitmap);
	this->PushEventHandler(NotebookBackground);


	wxFont myFont(26, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxFont password(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
	wxFont password_label(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);

	//m_title1 = new wxStaticText(this, wxID_ANY, wxT("FOOTBALL COMPETITION MANAGEMENT"), wxPoint(40, 90));
	//m_title1->SetFont(myFont);

	m_passwordEntry = new wxTextCtrl(this, 100, "", wxPoint(225 * 1.25, 340 * 1.25), wxSize(300, 35), wxTE_PASSWORD | wxTE_PROCESS_ENTER);
	m_passwordEntry->SetFont(password);

	//m_btn_connect = new wxButton(this, 10001, "Connect", wxPoint(300, 410), wxSize(150, 50));
	//m_btn_connect->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	//m_passwordLabel = new wxStaticText(this, wxID_ANY, wxT("Password: "), wxPoint(100, 335), wxSize(-1, -1));
	//m_passwordLabel->SetFont(password_label);

	m_checkbox = new wxCheckBox(this, 10002, "", wxPoint(575 * 1.25 - 50, 350 * 1.25));
	m_checkbox->SetBackgroundColour(wxTransparentColor);

	//m_showpass = new wxStaticText(this, wxID_ANY, "Show password", wxPoint(600, 333));
	//m_showpass->SetFont( wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	kawafel = new wxMediaCtrl();
	int ok = kawafel->Create(this, wxID_ANY, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/music.wav", wxDefaultPosition);
	playbutton = new wxButton(this, 12, "|>", wxPoint(10 * 1.25, 520 * 1.25), wxDefaultSize,wxBU_EXACTFIT);
	m_passwordEntry->SetHint("Type your password here");

}

void cMain::OnClose(wxCloseEvent& event)
{
	Destroy();
	this->PopEventHandler(true);
}


cMain::~cMain() {
	delete m_showpass;
	delete m_passwordEntry;
	delete m_passwordLabel;
	delete m_btn_connect;
	delete m_title1;
}

void cMain::OnConnect(wxCommandEvent& evt) { 

	wxString password = m_passwordEntry->GetValue();
	wxFont passwordd(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
	
	delete m_passwordEntry;

	if (m_checkbox->GetValue() == true)  m_passwordEntry = new wxTextCtrl(this, 100, "", wxPoint(225 * 1.25, 340 * 1.25), wxSize(300, 35), wxTE_PROCESS_ENTER);
	else m_passwordEntry = new wxTextCtrl(this, 100, "", wxPoint(225 * 1.25, 340 * 1.25), wxSize(300, 35), wxTE_PASSWORD | wxTE_PROCESS_ENTER);

	m_passwordEntry->SetFont(passwordd);
	
	if (password.empty()) {
		wxMessageBox(wxT("Password must not be empty"), wxT("Warning!"), wxICON_WARNING);
	}
	else {
		
		std::string truepassword = password.wxString::ToStdString();
		if (!valid(truepassword)) wxMessageBox(wxT("Password is incorrect"), wxT("Warning!"), wxICON_WARNING);
		else {
			m_menu1_frame = new cMenu1();
			m_menu1_frame->Show();
			Destroy();
			this->PopEventHandler(true);
			//wxMessageBox(wxT("Welcome"), wxT("Message!"), wxICON_INFORMATION); 
		}

	}
	m_passwordEntry->SetFocus();
	m_passwordEntry->SetHint("Type your password here");
}

void cMain::ShowPassword(wxCommandEvent& evt) {
	wxFont passwordd(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
	wxString passshow = m_passwordEntry->GetValue();
	delete m_passwordEntry;

	if (m_checkbox->GetValue() == true)  m_passwordEntry = new wxTextCtrl(this, 100, "", wxPoint(225 * 1.25, 340 * 1.25), wxSize(300, 35), wxTE_PROCESS_ENTER);
	else m_passwordEntry = new wxTextCtrl(this, 100, "", wxPoint(225 * 1.25, 340 * 1.25), wxSize(300, 35), wxTE_PASSWORD | wxTE_PROCESS_ENTER);
	m_passwordEntry->SetFont(passwordd);
	m_passwordEntry->AppendText(passshow);
	m_passwordEntry->SetHint("Type your password here");

	evt.Skip();
}

bool cMain::valid(std::string password)
{
	std::fstream input("passwords.txt");
	bool ans = false;
	std::hash<std::string> hasher;
	long long x, y = hasher(password);
	while (input >> x)
	{
		if (x == y)
		{
			ans = true;
			break;
		}
	}
	input.close();
	//if (ans) wxMessageBox(wxT("Welcome"), wxT("Message!"), wxICON_INFORMATION);
	return ans;
}