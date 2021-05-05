#include "cKnockout.h"
#include "cMenu1.h"
wxBEGIN_EVENT_TABLE(cKnockout, wxFrame)
EVT_BUTTON(12, oncancel)
EVT_PAINT(cKnockout::onpaint)
EVT_BUTTON(13, onback)
EVT_BUTTON(14, onauto)
wxEND_EVENT_TABLE()

cKnockout::cKnockout() : wxFrame(nullptr, wxID_ANY, "Overview", wxPoint(50, 150), wxSize(1800, 630)) {
	load_runners(vec_winners, vec_runners);
	
	m_title = new wxStaticText(this, wxID_ANY, wxT("OVERVIEW"), wxPoint(10, 10), wxSize(-1, -1));
	m_title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));

	//m_back = new wxButton(this, 13, "Back", wxPoint(1680, 500));
	m_cancel = new wxButton(this, 12, "Cancel", wxPoint(1680, 550), wxDefaultSize); //880
	m_auto = new wxButton(this, 14, "Auto fill", wxPoint(1680, 10));
	// wxchoices construction
	int xx = 1688; //1388
	int x = 150;
	int y = 100;
	round16[0] = new wxStaticText(this,wxID_ANY,"Round of 16" ,wxPoint(x - 100, 550));
	round16[1] = new wxStaticText(this,wxID_ANY,"Round of 16" ,wxPoint(xx - (x - 100) - 100, 550));
	for (int i = 0; i < 2;i++) round16[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	round8[0] = new wxStaticText(this, wxID_ANY, "Round of 8", wxPoint(x + 127, 550));
	round8[1] = new wxStaticText(this, wxID_ANY, "Round of 8", wxPoint(xx - (x - 100) - 327, 550));
	for (int i = 0; i < 2;i++) round8[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	round4[0] = new wxStaticText(this, wxID_ANY, "Semi-final", wxPoint(x + 315, 550));
	round4[1] = new wxStaticText(this, wxID_ANY, "Semi-final", wxPoint(xx - (x - 100) -  505, 550));
	for (int i = 0; i < 2;i++) round4[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	/*
	round2[0] = new wxStaticText(this, wxID_ANY, "Final", wxPoint(x + 490, 550));
	round2[1] = new wxStaticText(this, wxID_ANY, "Final", wxPoint(xx - (x - 100) -  690, 550));
	for (int i = 0; i < 2;i++) round2[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	*/
	round2[0] = new wxStaticText(this, wxID_ANY, "Final", wxPoint(x + 675, 550));
	round2[0]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			int y1 = y + i * 60 + (i + 1) % 2 * 10;
			int y2 = y + (i + 1) * 60 + (i + 2) % 2 * 10;
			//m_choices1[(int)i / 2] = new wxChoice(this, wxID_ANY, wxPoint(x + 130, (y1 + y2) / 2 - 10));
			//m_choices1[(int)i / 2]->AppendString(wxT("1/4 Round"));
			m_match1[(int)i / 2] = new wxButton(this, (int)i / 2 + 100, "Match", wxPoint(x + 130, (y1 + y2) / 2 - 10), wxSize(100,-1));
			m_match1[(int)i / 2]->Enable(false);
			m_match1[(int)i / 2]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);

			m_match3[(int)i / 2] = new wxButton(this, (int)i / 2 + 200, "Match", wxPoint(xx - (x + 130) - 100, (y1 + y2) / 2 - 10), wxSize(100, -1));
			m_match3[(int)i / 2]->Enable(false);
			m_match3[(int)i / 2]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);
			int j = i;
			if (j % 4 == 0) {
				int y11 = y + (i + 1) * 60 + (i + 2) % 2 * 10;
				int y22 = y + (i + 4) * 60 + (i + 5) % 2 * 10;
				//m_choices2[j / 4] = new wxChoice(this, wxID_ANY, wxPoint(x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 - 10));
				//m_choices2[j / 4]->AppendString(wxT("1/2 Round"));
				m_match2[j / 4] = new wxButton(this, j / 4 + 300, "Match" ,wxPoint(x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 - 10), wxSize(100, -1));
				m_match2[j / 4]->Enable(false);
				m_match2[j / 4]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);

				m_match4[j / 4] = new wxButton(this, j / 4 + 400, "Match", wxPoint(xx - (x + 310) - 100, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 - 10), wxSize(100, -1));
				m_match4[j / 4]->Enable(false);
				m_match4[j / 4]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);
				if (j % 8 == 0) {
					int y33 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2;
					int y44 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 + 240;
					/*
					m_choices3 = new wxChoice(this, wxID_ANY, wxPoint(x + 490, (y33 + y44) / 2 - 10));
					m_choices3->AppendString(wxT("Winner!!"));
					m_choices3->Select(0);
					*/

					m_12winner[0] = new wxButton(this, 500, "Match", wxPoint(x + 490, (y33 + y44) / 2 - 10), wxSize(100,-1));
					m_12winner[0]->Enable(false);
					m_12winner[0]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);

					m_12winner[1] = new wxButton(this, 501, "Match", wxPoint(xx - (x + 490) - 100, (y33 + y44) / 2 - 10), wxSize(100,-1));
					m_12winner[1]->Enable(false);
					m_12winner[1]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);

					/*
					m_rightwinner = new wxChoice(this, wxID_ANY, wxPoint(xx - (x + 490) - 100, (y33 + y44) / 2 - 10));
					m_rightwinner->AppendString(wxT("Winner!!"));
					m_rightwinner->Select(0);
					*/

					m_finalwinner = new wxButton(this, 600,"Match", wxPoint(((x + 590) + (x + 810)) / 2 - 50, (y33 + y44) / 2 + 100), wxSize(100,-1));
					m_finalwinner->Enable(false);
					m_finalwinner->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);

					m_vstitle = new wxStaticText(this, wxID_ANY, "VS", wxPoint(((x + 590) + (x + 810)) / 2 - 90, (y33 + y44) / 2 - 200));
					m_vstitle->SetFont(wxFont(100, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
				}
			}
		}
		m_choices[i] = new wxChoice(this, 200 + i, wxPoint(x - 100, y + i * 60 + (i + 1) % 2 * 10 - 10));
		
		m_choices4[i] = new wxChoice(this, 400 + i, wxPoint(xx - (x - 100) - 100, y + i * 60 + (i + 1) % 2 * 10 - 10));
		
		for (int j = 0; j < vec_winners.size(); j++) {
			//wxString s;
			//s << j + 1;
			//m_choices[i]->AppendString(wxT("1/8 Team " + s)); //Only these should be manually chosen.
			if (i % 2 == 0) {
				m_choices[i]->AppendString(vec_winners[j]);
				m_choices4[i]->AppendString(vec_winners[j]);
			}
			else {
				m_choices[i]->AppendString(vec_runners[j]);
				m_choices4[i]->AppendString(vec_runners[j]);
			}
		}
		m_choices[i]->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &cKnockout::onchoiceselsection, this);
		m_choices4[i]->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &cKnockout::onchoiceselsection, this);
	}
	//this->SetBackgroundColour(wxColor(34, 48, 39));
	
}

cKnockout::~cKnockout() {
	delete m_title;
	delete m_cancel;
}

void cKnockout::oncancel(wxCommandEvent& evt) {
	m_menu1_frame = new cMenu1();
	m_menu1_frame->Show();
	this->Close();
	evt.Skip();
}

void cKnockout::onpaint(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	int x = 150;
	int y = 100;
	dc.SetPen(wxPen(wxColor(0, 0, 0), 3));

	//can't implement wxChoices construction here, many problems would accure. Memory leaks, Unable to interact with it...
	
	for (int i = 0; i < 8; i++) {
		dc.DrawLine(wxPoint(x, y + i * 60 + (i + 1) % 2 * 10), wxPoint(x + 100, y + i * 60 + (i + 1) % 2 * 10)); //Lefty lines
		if (i % 2 == 0) {
			int y1 = y + i * 60 + (i + 1) % 2 * 10;
			int y2 = y + (i + 1) * 60 + (i + 2) % 2 * 10;
			dc.DrawLine(wxPoint(x + 100, y1), wxPoint(x + 100, y2)); //going down 1
			dc.DrawLine(wxPoint(x + 100, (y1 + y2) / 2), wxPoint(x + 130, (y1 + y2) / 2)); // going in to wxChoices1
			//m_choices1[(int) i / 2] = new wxChoice(this, wxID_ANY, wxPoint(x + 130, (y1 + y2) / 2 - 10));
			dc.DrawLine(wxPoint(x + 230, (y1 + y2) / 2), wxPoint(x + 280, (y1 + y2) / 2)); //coming out from wxChoices1
			int j = i;
			if (j % 4 == 0) {
				int y11 = y + (i + 1) * 60 + (i + 2) % 2 * 10;
				int y22 = y + (i + 4) * 60 + (i + 5) % 2 * 10;
				dc.DrawLine(wxPoint(x + 280, (y1 + y2) / 2), wxPoint(x + 280, (y11 + y22) / 2)); // going down 2
				dc.DrawLine(wxPoint(x + 280, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2), wxPoint(x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2)); //going in to wxChoices2
				//m_choices2[j / 4] = new wxChoice(this, wxID_ANY, wxPoint(x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 - 10));
				dc.DrawLine(wxPoint(x + 410, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2), wxPoint(x + 460, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2)); //coming out from wxChoices2
				if (j % 8 == 0) {
					int y33 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2;
					int y44 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 + 240;
					dc.DrawLine(wxPoint(x + 460, y33), wxPoint(x + 460, y44)); //going down 3
					dc.DrawLine(wxPoint(x + 460, (y33 + y44) / 2), wxPoint(x + 490, (y33 + y44) / 2)); //going in to wxChoices3
					
					dc.DrawLine(wxPoint(x + 590, (y33 + y44) / 2), wxPoint(x + 810, (y33 + y44) / 2)); //coming out from wxChoices3
					
					dc.DrawLine(wxPoint( ( (x+ 590) + (x + 810) ) / 2, (y33 + y44) / 2), wxPoint(((x + 590) + (x + 810)) / 2, (y33 + y44) / 2 + 100)); //going in to wxChoices3

					//m_choices3 = new wxChoice(this, wxID_ANY, wxPoint(x + 490, (y33 + y44) / 2 - 10));
				}
			}
		}
		//m_choices[i] = new wxChoice(this, wxID_ANY, wxPoint(x-100, y + i * 60 + (i + 1) % 2 * 10 - 10));
	}
	int xx = 1688;
	for (int i = 0; i < 8; i++) {
		dc.DrawLine(wxPoint(xx - x, y + i * 60 + (i + 1) % 2 * 10), wxPoint(xx - (x + 100), y + i * 60 + (i + 1) % 2 * 10)); //Lefty lines
		if (i % 2 == 0) {
			int y1 = y + i * 60 + (i + 1) % 2 * 10;
			int y2 = y + (i + 1) * 60 + (i + 2) % 2 * 10;
			dc.DrawLine(wxPoint(xx - (x + 100), y1), wxPoint( xx - (x + 100), y2)); //going down 1
			dc.DrawLine(wxPoint(xx - (x + 100), (y1 + y2) / 2), wxPoint(xx - (x + 130), (y1 + y2) / 2)); // going in to wxChoices1
			//m_choices1[(int) i / 2] = new wxChoice(this, wxID_ANY, wxPoint(xx - (x + 130), (y1 + y2) / 2 - 10));
			dc.DrawLine(wxPoint(xx - (x + 230), (y1 + y2) / 2), wxPoint(xx - (x + 280), (y1 + y2) / 2)); //coming out from wxChoices1
			int j = i;
			if (j % 4 == 0) {
				int y11 = y + (i + 1) * 60 + (i + 2) % 2 * 10;
				int y22 = y + (i + 4) * 60 + (i + 5) % 2 * 10;
				dc.DrawLine(wxPoint(xx - (x + 280), (y1 + y2) / 2), wxPoint(xx - (x + 280), (y11 + y22) / 2)); // going down 2
				dc.DrawLine(wxPoint(xx - (x + 280), ((y1 + y2) / 2 + (y11 + y22) / 2) / 2), wxPoint(xx - (x + 310), ((y1 + y2) / 2 + (y11 + y22) / 2) / 2)); //going in to wxChoices2
				//m_choices2[j / 4] = new wxChoice(this, wxID_ANY, wxPoint(xx - x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 - 10));
				dc.DrawLine(wxPoint(xx - (x + 410), ((y1 + y2) / 2 + (y11 + y22) / 2) / 2), wxPoint(xx - (x + 460), ((y1 + y2) / 2 + (y11 + y22) / 2) / 2)); //coming out from wxChoices2
				if (j % 8 == 0) {
					int y33 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2;
					int y44 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 + 240;
					dc.DrawLine(wxPoint(xx - (x + 460), y33), wxPoint(xx - (x + 460), y44)); //going down 3
					dc.DrawLine(wxPoint(xx - (x + 460), (y33 + y44) / 2), wxPoint(xx - (x + 490), (y33 + y44) / 2)); //going in to wxChoices3
					//m_choices3 = new wxChoice(this, wxID_ANY, wxPoint(xx - x + 490, (y33 + y44) / 2 - 10));
				}
			}
		}
		//m_choices[i] = new wxChoice(this, wxID_ANY, wxPoint(xx - (x-100) - 100, y + i * 60 + (i + 1) % 2 * 10 - 10));
	}
	evt.Skip();
}

void cKnockout::onm_match(wxCommandEvent& evt) {
	int Id = evt.GetId();
	//need to refill the choiceboxes with the remaining teams.
	real_id = Id;
	
	wxString team1, team2;
	if (Id / 100 == 1) {
		Id -= 100;
		m_choices[2 * Id]->Enable(false);
		m_choices[2 * Id + 1]->Enable(false);
		team1 = m_choices[2 * Id]->GetStringSelection();
		team2 = m_choices[2 * Id + 1]->GetStringSelection();
	}
	else if (Id / 100 == 2) {
		Id -= 200;
		m_choices4[2 * Id]->Enable(false);
		m_choices4[2 * Id + 1]->Enable(false);
		team1 = m_choices4[2 * Id]->GetStringSelection();
		team2 = m_choices4[2 * Id + 1]->GetStringSelection();
	}
	else if (Id / 100 == 3) {
		Id -= 300;
		if (Id == 1) Id++;
		team1 = m_winners1[Id]->GetLabel();
		team2 = m_winners1[Id + 1]->GetLabel();
	}
	else if (Id / 100 == 4) {
		Id -= 400;
		if (Id == 1) Id++;
		team1 = m_winners3[Id]->GetLabel();
		team2 = m_winners3[Id + 1]->GetLabel();
	}
	else if (Id / 100 == 5) {
		Id -= 500;
		if (Id == 0) {
			team1 = m_winners2[Id]->GetLabel();
			team2 = m_winners2[Id + 1]->GetLabel();
		}
		else {
			team1 = m_winners4[Id]->GetLabel();
			team2 = m_winners4[Id + 1]->GetLabel();
		}
	}
	else if (Id / 100 == 6) {
		Id -= 600;
		team1 = m_12text[Id]->GetLabel();
		team2 = m_12text[Id + 1]->GetLabel();
		finaaal = true;
	}
	m_playerselection_frame = new cPlayerselection(team1, team2, this);
	m_playerselection_frame->Show();
	evt.Skip();
}

void cKnockout::onchoiceselsection(wxCommandEvent& evt) {
	int Id = evt.GetId();
	if ( (int) Id / 200 == 1) {
		Id -= 200;
		if (Id % 2 ==0) if (m_choices[Id]->GetStringSelection() != "" && m_choices[Id + 1]->GetStringSelection() != "") m_match1[Id / 2]->Enable(true);
		if (Id % 2 !=0) if (m_choices[Id]->GetStringSelection() != "" && m_choices[Id - 1]->GetStringSelection() != "") m_match1[Id / 2]->Enable(true);
		int ok = 1;
		for (int j = 0; j < 8; j++) {
			if ((m_choices[Id]->GetStringSelection() == m_choices[j]->GetStringSelection() && j!=Id) || m_choices[Id]->GetStringSelection() == m_choices4[j]->GetStringSelection()) {
				ok = 0;
			}
		}
		int ans;
		if (Id % 2 == 0) ans = teamisselected(0, Id + 1);
		else ans = teamisselected(0, Id - 1);

		if (!ok) wxMessageBox("Choose another team please");
		ok = ok && ans;
		if (m_match1[Id / 2]->IsEnabled() && ok) {
			wxMessageBox("You may now start the match !");
			m_auto->Show(true);
		}
		else m_match1[Id / 2]->Enable(false);
	}
	else {
		Id -= 400;
		if (Id % 2 == 0) if (m_choices4[Id]->GetStringSelection() != "" && m_choices4[Id + 1]->GetStringSelection() != "") m_match3[Id / 2]->Enable(true);
		if (Id % 2 != 0) if (m_choices4[Id]->GetStringSelection() != "" && m_choices4[Id - 1]->GetStringSelection() != "") m_match3[Id / 2]->Enable(true);
		int ok = 1;
		for (int j = 0; j < 8; j++) {
			if ( (m_choices4[Id]->GetStringSelection() == m_choices4[j]->GetStringSelection() && j!=Id) || m_choices4[Id]->GetStringSelection() == m_choices[j]->GetStringSelection()) {
				ok = 0;
			}
		}
		int ans;
		if (Id % 2 == 0) ans = teamisselected(1, Id + 1);
		else ans = teamisselected(1, Id - 1);

		if (!ok) wxMessageBox("Choose another team please");
		ok = ok & ans;
		if (m_match3[Id / 2]->IsEnabled() && ok) wxMessageBox("You may now start the match !");
		else m_match3[Id / 2]->Enable(false);
	}
	//verify that both teams are not selected anywhere else -- DONE
	
	evt.Skip();
}

int cKnockout::teamisselected(int which, int Id) {
	int ans = 1;
	if (which == 0) {
		for (int j = 0; j < 8; j++) {
			if ((m_choices[Id]->GetStringSelection() == m_choices[j]->GetStringSelection() && j != Id) || m_choices[Id]->GetStringSelection() == m_choices4[j]->GetStringSelection()) {
				ans = 0;
			}
		}
	}
	else {
		for (int j = 0; j < 8; j++) {
			if ((m_choices4[Id]->GetStringSelection() == m_choices4[j]->GetStringSelection() && j != Id) || m_choices4[Id]->GetStringSelection() == m_choices[j]->GetStringSelection()) {
				ans = 0;
			}
		}
	}

	return ans;
}

void cKnockout::displaywinners(wxString winner) {
	wxFont myfont = wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	if (real_id / 100 == 1) {
		real_id -= 100;

		m_choices[2 * real_id]->Show(false);
		m_choices[2 * real_id + 1]->Show(false);
		
		m_choice_text1[2 * real_id] = new wxStaticText(this, wxID_ANY, m_choices[2 * real_id]->GetStringSelection(), m_choices[2 * real_id]->GetPosition());
		m_choice_text1[2 * real_id]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
		//m_choice_text1[2 * real_id]->SetForegroundColour(wxColor(61, 164, 224));

		m_choice_text1[2 * real_id + 1] = new wxStaticText(this, wxID_ANY, m_choices[2 * real_id + 1]->GetStringSelection(), m_choices[2 * real_id + 1]->GetPosition());
		m_choice_text1[2 * real_id + 1]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		m_winners1[real_id] = new wxStaticText(this, wxID_ANY, winner, m_match1[real_id]->GetPosition());
		m_winners1[real_id]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		m_match1[real_id]->Show(false);
	}
	else if (real_id / 100 == 2) {
		real_id -= 200;
		m_choices4[2 * real_id]->Show(false);
		m_choices4[2 * real_id + 1]->Show(false);

		m_winners3[real_id] = new wxStaticText(this, wxID_ANY, winner, m_match3[real_id]->GetPosition());
		m_winners3[real_id]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		m_choice_text1[2 * real_id] = new wxStaticText(this, wxID_ANY, m_choices4[2 * real_id]->GetStringSelection(), m_choices4[2 * real_id]->GetPosition());
		m_choice_text1[2 * real_id]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		m_choice_text1[2 * real_id + 1] = new wxStaticText(this, wxID_ANY, m_choices4[2 * real_id + 1]->GetStringSelection(), m_choices4[2 * real_id + 1]->GetPosition());
		m_choice_text1[2 * real_id + 1]->SetFont(myfont);

		m_match3[real_id]->Show(false);
	}
	else if (real_id / 100 == 3) {
		real_id -= 300;
		m_match2[real_id]->Show(false);
		m_winners2[real_id] = new wxStaticText(this, wxID_ANY, winner, m_match2[real_id]->GetPosition());
		m_winners2[real_id]->SetFont(myfont);

	}
	else if (real_id / 100 == 4) {
		real_id -= 400;
		m_match4[real_id]->Show(false);
		m_winners4[real_id] = new wxStaticText(this, wxID_ANY, winner, m_match4[real_id]->GetPosition());
		m_winners4[real_id]->SetFont(myfont);
	}
	else if (real_id / 100 == 5) {
		real_id -= 500;
		m_12winner[real_id]->Show(false);
		m_12text[real_id] = new wxStaticText(this, wxID_ANY, winner, m_12winner[real_id]->GetPosition());
		m_12text[real_id]->SetFont(myfont);

	}
	else if (real_id / 100 == 6) {
		real_id -= 600;
		m_finalwinner->Show(false);
		m_finalwinner_text = new wxStaticText(this, wxID_ANY, winner, m_finalwinner->GetPosition());
		m_finalwinner_text->SetFont(myfont);
		cWinner* cwinnerframe = new cWinner(winner);
		cwinnerframe->Show();
	}
	enablematchbutton();
	save_team_stats_knockout(winner.ToStdString());
}

void cKnockout::enablematchbutton() {
	bool ishown1 = !m_match1[0]->IsShown() && !m_match1[1]->IsShown();
	bool ishown2 = !m_match3[0]->IsShown() && !m_match3[1]->IsShown();

	bool ishown3 = !m_match1[2]->IsShown() && !m_match1[3]->IsShown();
	bool ishown4 = !m_match3[2]->IsShown() && !m_match3[3]->IsShown();

	bool ishown5 = !m_match2[0]->IsShown() && !m_match2[1]->IsShown();
	bool ishown6 = !m_match4[0]->IsShown() && !m_match4[1]->IsShown();

	bool ishown7 = !m_12winner[0]->IsShown() && !m_12winner[1]->IsShown();
	if (ishown1) {
		m_match2[0]->Enable(true);
	}
	if (ishown2) {
		m_match4[0]->Enable(true);
	}
	if (ishown3) {
		m_match2[1]->Enable(true);
	}
	if (ishown4) {
		m_match4[1]->Enable(true);
	}
	if (ishown5) {
		m_12winner[0]->Enable(true);
	}
	if (ishown6) {
		m_12winner[1]->Enable(true);
	}
	if (ishown7) {
		m_finalwinner->Enable(true);
	}
}

void cKnockout::onback(wxCommandEvent& evt) {
	m_nextcreate_frame = new cNextcreate();
	m_nextcreate_frame->Show();
	this->Close();
	evt.Skip();
}

void cKnockout::onauto(wxCommandEvent& evt) {
	if (firstauto) {
		for (int i = 0; i < 8; i++) {
			m_choices[i]->SetSelection(i);
			m_choices4[i]->SetSelection(i + 1);
		}
		m_choices4[7]->SetSelection(0);
		for (int i = 0; i < 4; i++) {
			m_match1[i]->Enable(true);
			m_match3[i]->Enable(true);
		}
		firstauto = false;
	}
	else {
		for (int i = 0; i < 2; i++) {
			if (m_12winner[i]->IsEnabled() && m_12winner[i]->IsShown()) {
				real_id = 500 + i;
				displaywinners(m_winners2[2 * i]->GetLabel());
				//save_team_stats_knockout(m_winners2[2 * i]->GetLabel().ToStdString());
			}
		}
		for (int i = 0; i < 2; i++) {
			if (m_match2[i]->IsEnabled() && m_match2[i]->IsShown()) {
				real_id = 300 + i;
				displaywinners(m_winners1[2 * i]->GetLabel());
				//save_team_stats_knockout(m_winners1[2 * i]->GetLabel().ToStdString());
			}
			if (m_match4[i]->IsEnabled() && m_match4[i]->IsShown()) {
				real_id = 400 + i;
				displaywinners(m_winners3[2 * i]->GetLabel());
				//save_team_stats_knockout(m_winners3[2 * i]->GetLabel().ToStdString());
			}
		}
		for (int i = 0; i < 4; i++) {
			if (m_match1[i]->IsEnabled() && m_match1[i]->IsShown()) {
				real_id = 100 + i;
				displaywinners(m_choices[ 2 * i ]->GetStringSelection());
				//save_team_stats_knockout(m_choices[2 * i]->GetStringSelection().ToStdString());

			}
			if (m_match3[i]->IsEnabled() && m_match3[i]->IsShown()) {
				real_id = 200 + i;
				displaywinners(m_choices4[2 * i ]->GetStringSelection());
				//save_team_stats_knockout(m_choices4[2 * i]->GetStringSelection().ToStdString());
			}

		}
	}
	evt.Skip();
}

void cKnockout::save_team_stats_knockout(string winner) {
	bool exists = false;
	ifstream input("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/teamstats.txt", ios::in);
	string s;
	vector<string> teams;
	int score;
	while (input >> s)
	{
		if (!(winner == separate(s)[0])) {
			teams.push_back(s);
		}
		else {
			score = wxAtoi(separate(s)[1]) + 1;
			wxString ss;
			ss << score;
			teams.push_back(winner + ";" + ss.ToStdString());
		}
	}
	input.close();

	if (!exists) {
		ofstream output("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/teamstats.txt", ios::out);
		for(int i=0; i<teams.size(); i++) output << teams[i] << endl;
		output.close();
	}
}