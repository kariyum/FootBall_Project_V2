#include "cKnockout.h"
#include "cMenu1.h"
wxBEGIN_EVENT_TABLE(cKnockout, wxFrame)
EVT_BUTTON(12, oncancel)
EVT_PAINT(cKnockout::onpaint)
wxEND_EVENT_TABLE()

cKnockout::cKnockout() : wxFrame(nullptr, wxID_ANY, "Overview", wxPoint(300, 150), wxSize(1000, 600)) {
	m_title = new wxStaticText(this, wxID_ANY, wxT("OVERVIEW"), wxPoint(10, 10), wxSize(-1, -1));
	m_title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));

	m_cancel = new wxButton(this, 12, "Cancel", wxPoint(880, 530), wxDefaultSize);

	// wxchoices construction
	int x = 150;
	int y = 100;
	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			int y1 = y + i * 60 + (i + 1) % 2 * 10;
			int y2 = y + (i + 1) * 60 + (i + 2) % 2 * 10;
			//m_choices1[(int)i / 2] = new wxChoice(this, wxID_ANY, wxPoint(x + 130, (y1 + y2) / 2 - 10));
			//m_choices1[(int)i / 2]->AppendString(wxT("1/4 Round"));
			m_match1[(int)i / 2] = new wxButton(this, (int)i / 2 + 100, "Match", wxPoint(x + 130, (y1 + y2) / 2 - 10), wxSize(100,-1));
			m_match1[(int)i / 2]->Enable(false);
			m_match1[(int)i / 2]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);

			int j = i;
			if (j % 4 == 0) {
				int y11 = y + (i + 1) * 60 + (i + 2) % 2 * 10;
				int y22 = y + (i + 4) * 60 + (i + 5) % 2 * 10;
				//m_choices2[j / 4] = new wxChoice(this, wxID_ANY, wxPoint(x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 - 10));
				//m_choices2[j / 4]->AppendString(wxT("1/2 Round"));
				m_match2[j / 4] = new wxButton(this, wxID_ANY, "Match" ,wxPoint(x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 - 10), wxSize(100, -1));
				m_match2[j / 4]->Enable(false);
				m_match2[j / 4]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cKnockout::onm_match, this);

				if (j % 8 == 0) {
					int y33 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2;
					int y44 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 + 240;
					m_choices3 = new wxChoice(this, wxID_ANY, wxPoint(x + 490, (y33 + y44) / 2 - 10));
					m_choices3->AppendString(wxT("Winner!!"));
					m_choices3->Select(0);
				}
			}
		}
		m_choices[i] = new wxChoice(this, 200 + i, wxPoint(x - 100, y + i * 60 + (i + 1) % 2 * 10 - 10));
		for (int j = 0; j < 16; j++) {
			wxString s;
			s << j + 1;
			m_choices[i]->AppendString(wxT("1/8 Team " + s)); //Only these should be manually chosen.
		}
		m_choices[i]->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &cKnockout::onchoiceselsection, this);
	}

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
				int y11 = y + (i+1) * 60 + (i + 2) % 2 * 10;
				int y22 = y + (i + 4) * 60 + (i + 5) % 2 * 10;
				dc.DrawLine(wxPoint(x + 280, (y1 + y2) / 2), wxPoint(x + 280, (y11 + y22) / 2)); // going down 2
				dc.DrawLine(wxPoint(x + 280, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2), wxPoint(x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2)/2 )); //going in to wxChoices2
				//m_choices2[j / 4] = new wxChoice(this, wxID_ANY, wxPoint(x + 310, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 - 10));
				dc.DrawLine(wxPoint(x + 410, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2), wxPoint(x + 460, ((y1 + y2) / 2 + (y11 + y22) / 2) / 2)); //coming out from wxChoices2
				if (j % 8 == 0) {
					int y33 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2;
					int y44 = ((y1 + y2) / 2 + (y11 + y22) / 2) / 2 + 240; 
					dc.DrawLine(wxPoint(x + 460, y33), wxPoint(x + 460, y44)); //going down 3
					dc.DrawLine(wxPoint(x + 460, (y33 + y44) / 2), wxPoint(x + 490, (y33 + y44) / 2)); //going in to wxChoices3
					//m_choices3 = new wxChoice(this, wxID_ANY, wxPoint(x + 490, (y33 + y44) / 2 - 10));
				}
			}
		}
		//m_choices[i] = new wxChoice(this, wxID_ANY, wxPoint(x-100, y + i * 60 + (i + 1) % 2 * 10 - 10));
	}
	
	evt.Skip();
}

void cKnockout::onm_match(wxCommandEvent& evt) {
	int Id = evt.GetId() - 100;
	evt.Skip();
}

void cKnockout::onchoiceselsection(wxCommandEvent& evt) {
	int Id = evt.GetId() - 200;
	if (Id % 2 ==0) if (m_choices[Id]->GetStringSelection() != "" && m_choices[Id + 1]->GetStringSelection() != "") m_match1[Id / 2]->Enable(true);
	if (Id % 2 !=0) if (m_choices[Id]->GetStringSelection() != "" && m_choices[Id - 1]->GetStringSelection() != "") m_match1[Id / 2]->Enable(true);
	int ok = 1;
	for (int j = 0; j < 16 && j != Id && ok; j++) {
		if (m_choices[Id]->GetStringSelection() == m_choices[j]->GetStringSelection()) {
			wxMessageBox("Choose another team please");
			ok = 0;
		}
	}
	if (m_match1[Id / 2]->IsEnabled() && ok) wxMessageBox("You may now start the match !");
	evt.Skip();
}