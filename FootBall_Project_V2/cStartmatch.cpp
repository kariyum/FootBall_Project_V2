#include "cStartmatch.h"

wxBEGIN_EVENT_TABLE(cStartmatch, wxFrame)
EVT_BUTTON(1001, onendmatch)
EVT_BUTTON(1002, onaddnote)
EVT_BUTTON(1003, onstartstoptime)
EVT_BUTTON(1004, ontakebreak)
EVT_TIMER(1111, addsecond)
wxEND_EVENT_TABLE()

cStartmatch::cStartmatch() : wxFrame(nullptr, wxID_ANY, "Match", wxPoint(300, 150), wxSize(1200, 800)) {
    windowtitle = new wxStaticText(this, wxID_ANY, "MATCH", wxPoint(10, 10));
    windowtitle->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true));

    int x1 = 370;


    teams_title[0] = new wxStaticText(this, wxID_ANY, "Team 1", wxPoint(x1, 50));
    teams_title[1] = new wxStaticText(this, wxID_ANY, "Team 2", wxPoint(x1 + 300, 50));

    for (int i = 0; i < 2; i++) teams_title[i]->SetFont(wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    m_vs_title = new wxStaticText(this, wxID_ANY, "----", wxPoint(x1 + 190, 50));
    m_vs_title->SetFont(wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    m_goals[0] = new wxStaticText(this, wxID_ANY, "0", wxPoint(x1 + 150, 50));
    m_goals[1] = new wxStaticText(this, wxID_ANY, "0", wxPoint(x1 + 250, 50));
    for (int i = 0; i < 2; i++) m_goals[i]->SetFont(wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    m_add_goals[0] = new wxButton(this, 10, "Add goal", wxPoint(x1, 90), wxSize(107, -1));
    m_add_goals[1] = new wxButton(this, 11, "Add goal", wxPoint(x1 + 300, 90), wxSize(107, -1));
    for (int i = 0; i < 2; i++) m_add_goals[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cStartmatch::onaddgoals, this);
    
    int dx = 1030;
    int dy = 50;

    int x = 100;
    int y = 150;

    redcards = new wxButton * [22];
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 11; i++) {
            redcards[i + j * 11] = new wxButton(this, wxID_ANY, "0", wxPoint(x + j * dx, y + i * dy), wxSize(30, 30), wxBORDER_NONE);
            redcards[i + j * 11]->SetBackgroundColour(wxColor(255, 47, 52));
            redcards[i + j * 11]->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

            add_r1[i + j * 11] = new wxButton(this, i + j * 11, "+", wxPoint(x - 20 + j * dx, y + i * dy), wxSize(15, 15));
            add_r1[i + j * 11]->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            add_r1[i + j * 11]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cStartmatch::onplus, this);

            sub_r1[i + j * 11] = new wxButton(this, 100 + i + j * 11, "-", wxPoint(x - 20 + j * dx, y + 15 + i * dy), wxSize(15, 15));
            sub_r1[i + j * 11]->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            sub_r1[i + j * 11]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cStartmatch::onminus, this);

            wxString s;
            s << (i + j * 11) % 11 + 1;
            if (i + j * 11 < 11) playersname[i + j * 11] = new wxStaticText(this, wxID_ANY, wxT("Player ") + s, wxPoint(x + j * dx + 70, y + i * dy));
            else playersname[i + j * 11] = new wxStaticText(this, wxID_ANY, wxT("Player ") + s, wxPoint(x + j * dx - 230, y + i * dy));
            playersname[i + j * 11]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            //=====================================================================================================

            yellowcards[i + j * 11] = new wxButton(this, wxID_ANY, "0", wxPoint(x - 70 + j * dx, y + i * dy), wxSize(30, 30), wxBORDER_NONE);
            yellowcards[i + j * 11]->SetBackgroundColour(wxColor(240, 192, 0));
            yellowcards[i + j * 11]->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

            add_y1[i + j * 11] = new wxButton(this, i + j * 11 + 2000, "+", wxPoint(x - 90 + j * dx, y + i * dy), wxSize(15, 15), wxBORDER_NONE);
            add_y1[i + j * 11]->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            add_y1[i + j * 11]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cStartmatch::onplus, this);

            sub_y1[i + j * 11] = new wxButton(this, i + j * 11 + 2100, "-", wxPoint(x - 90 + j * dx, y + 15 + i * dy), wxSize(15, 15), wxBORDER_NONE);
            sub_y1[i + j * 11]->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            sub_y1[i + j * 11]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cStartmatch::onminus, this);
        }
    }
    //wxButton* test = new wxButton(this, 1000, "delete");
    m_matchnotes = new wxStaticText(this, wxID_ANY, "Match notes", wxPoint(510, 120));
    m_matchnotes->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    m_addnote = new wxButton(this, 1002, "Add note", wxPoint(371, 624)); //x=540 y=120
    m_note = new wxListBox(this, wxID_ANY, wxPoint(370, 150), wxSize(405, 470));
    m_notetext = new wxTextCtrl(this, wxID_ANY, "", wxPoint(370, 650), wxSize(405, 30));
    m_notetext->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    m_note->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    //====================================================================================================
    m_endmatch = new wxButton(this, 1001, "End match", wxPoint(540, 700));

    chornotime = new wxStaticText(this, wxID_ANY, inttotime(0), wxPoint(10, 50));
    chornotime->SetFont(wxFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    m_startstoptime = new wxButton(this, 1003, "", wxPoint(10, 110));
    m_startstoptime->SetLabel("Start time");
    datetime = new wxTimer(this, 1111);

    created[0] = 0;
    created[1] = 0;

    m_takebreak = new wxButton(this, 1004, "Take break", wxPoint(110, 110));
}


cStartmatch::~cStartmatch() {
    datetime->Stop();
    delete datetime;
}

void cStartmatch::onendmatch(wxCommandEvent& evt) {
    this->Close();
    evt.Skip();
}

void cStartmatch::onaddnote(wxCommandEvent& evt) {
    if (m_notetext->GetValue() != "") {
        wxString s;
        s = inttotime(time1111);
        wxString stringvalue = m_notetext->GetValue();

        wxVector<wxString> ans;

        ans = separate(s + " : " + stringvalue, 38);
        for (int i = 0; i < ans.size(); i++) {
            m_note->AppendString(ans[i]);
        }
    }
    m_notetext->Clear();
    m_note->PageDown();
    evt.Skip();
}

void cStartmatch::onstartstoptime(wxCommandEvent& evt) {
    if (m_startstoptime->GetLabel() == "Start time" || m_startstoptime->GetLabel() == "Resume time") {
        datetime->Start(100);
        m_startstoptime->SetLabel("Stop time");
    }
    else {
        datetime->Stop();
        m_startstoptime->SetLabel("Resume time");
    }
    evt.Skip();
}

void cStartmatch::addsecond(wxTimerEvent& evt) {
    wxString s;
    s = inttotime(time1111);
    time1111++;
    if (minuteriestatus) {
        s = inttotime(900 + recenttime - time1111);
        minuterie->SetLabel(s);
        breakperiod++;
    }
    else {
        chornotime->SetLabelText(s);
        breakperiod = 0;
    }
    //wxMessageBox("CALLED");
    evt.Skip();
}

void cStartmatch::onaddgoals(wxCommandEvent& evt) {
    int x1 = 370;
    if (created[evt.GetId() -10 ] == 1) delete m_choices[evt.GetId()- 10];
    if (evt.GetId() - 10 == 0) m_choices[0] = new wxChoice(this, 100, wxPoint(x1 - 1, 120));
    else if (evt.GetId() - 10 == 1) m_choices[1] = new wxChoice(this, 101, wxPoint(x1 + 300 - 1, 120));
    m_choices[evt.GetId() - 10]->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &cStartmatch::onchoiceselection, this);
    for (int j = 0; j < 11; j++) {
        wxString s;
        s << j + 1;
        m_choices[evt.GetId()-10]->AppendString(wxT("Player " + s));
    }
    
    m_choices[evt.GetId() - 10]->Select(0);
    created[evt.GetId() - 10] = 1;
    evt.Skip();
}

void cStartmatch::onchoiceselection(wxCommandEvent& evt) {
    int Id = evt.GetId() - 100;
    wxMessageBox(m_choices[Id]->GetStringSelection() + " has scored a goal !");
    int num = wxAtoi(m_goals[Id]->GetLabel());
    num++;
    wxString ss;
    ss << num;
    m_goals[Id]->SetLabel(ss);
    m_choices[Id]->Hide();

    wxString s;
    s = inttotime(time1111);
    wxString stringvalue = teams_title[Id]->GetLabel() + " " + m_choices[Id]->GetStringSelection() + " has scored a goal !";

    wxVector<wxString> ans;

    ans = separate(s + " : " + stringvalue, 38);
    for (int i = 0; i < ans.size(); i++) {
        m_note->AppendString(ans[i]);
    }
    m_note->PageDown();
    evt.Skip();
}

void cStartmatch::onplus(wxCommandEvent& evt) {
    
    int Id = evt.GetId();
    if (Id / 1000 != 0) {
        Id -= 2000;
        int num;
        num = wxAtoi(yellowcards[Id]->GetLabel());
        num++;
        wxString s;
        s << num;
        yellowcards[Id]->SetLabel(s);
        wxString time_string;
        time_string = inttotime(time1111);
        wxString team_name;
        team_name << Id / 11 + 1;

        wxVector<wxString> ans;

        ans = separate(time_string + ": " + "A yellowcard has been added to team" + team_name + " " + playersname[Id]->GetLabel(), 38);
        for (int i = 0; i < ans.size(); i++) {
            m_note->AppendString(ans[i]);
        }
    }
    else {
        int num;
        num = wxAtoi(redcards[Id]->GetLabel());
        num++;
        wxString s;
        s << num;
        redcards[Id]->SetLabel(s);
        wxString time_string;
        time_string = inttotime(time1111);
        wxString team_name;
        team_name << Id / 11 + 1;

        wxVector<wxString> ans;

        ans = separate(time_string + ": " + "A redcard has been added to team" + team_name + " " + playersname[Id]->GetLabel(), 38);
        for (int i = 0; i < ans.size(); i++) {
            m_note->AppendString(ans[i]);
        }
    }
    m_note->PageDown();
    evt.Skip();
}

void cStartmatch::onminus(wxCommandEvent& evt) {
    int Id = evt.GetId() - 100;
    if (Id / 1000 != 0) {
        Id -= 2000;
        wxString s;
        s = yellowcards[Id]->GetLabel();
        int num;
        num = wxAtoi(s);
        num--;
        wxString str;
        str << num;
        if (num >= 0) {
            yellowcards[Id]->SetLabel(str);
            wxString time_string;
            time_string = inttotime(time1111);
            wxString team_name;
            team_name << Id / 11 + 1;

            wxVector<wxString> ans;

            ans = separate(time_string + ": " + "A yellowcard has been removed from team" + team_name + " " + playersname[Id]->GetLabel(), 38);
            for (int i = 0; i < ans.size(); i++) {
                m_note->AppendString(ans[i]);
            }
        }
    }
    else {
        wxString s;
        s = redcards[Id]->GetLabel();
        int num;
        num = wxAtoi(s);
        num--;
        wxString str;
        str << num;
        if (num >= 0) {
            redcards[Id]->SetLabel(str);
            wxString time_string;
            time_string = inttotime(time1111);
            wxString team_name;
            team_name << Id / 11 + 1;

            wxVector<wxString> ans;

            ans = separate(time_string + ": " + "A redcard has been removed from team" + team_name + " " + playersname[Id]->GetLabel(), 38);
            for (int i = 0; i < ans.size(); i++) {
                m_note->AppendString(ans[i]);
            }
        }
    }
    m_note->PageDown();
    evt.Skip();
}


void cStartmatch::ontakebreak(wxCommandEvent& evt) {
    //datetime->Stop();
    if (minuteriestatus) {
        m_takebreak->SetLabel("Take break");
        minuteriestatus = false;
        delete minuterie;
        chornotime->Show();
        time1111 = recenttime;

        wxString s;
        s = inttotime(time1111 + breakperiod); //check if notes should be sorted or not.
        wxString ss;
        ss = inttotime(breakperiod);
        wxString stringvalue = "Break time ended and lasted for " + ss;

        wxVector<wxString> ans;

        ans = separate(s + " : " + stringvalue, 38);
        for (int i = 0; i < ans.size(); i++) {
            m_note->AppendString(ans[i]);
        }
        m_startstoptime->SetLabel("Resume time");
        datetime->Stop();
    }
    else {
        chornotime->Hide();
        m_takebreak->SetLabel("Resume match");
        minuterie = new wxStaticText(this, wxID_ANY, inttotime(900), wxPoint(10, 50));
        minuterie->SetFont(wxFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        minuteriestatus = true;

        wxString s;
        s = inttotime(time1111);
        wxString stringvalue = "Break time started";

        wxVector<wxString> ans;

        ans = separate(s + " : " + stringvalue, 38);
        for (int i = 0; i < ans.size(); i++) {
            m_note->AppendString(ans[i]);
        }
        recenttime = time1111;
        datetime->Start();
        m_startstoptime->SetLabel("Stop time");
    }
    m_note->PageDown();
    evt.Skip();
}


wxString cStartmatch::inttotime(int x) {
    wxString h, m, s;
    int hh, mm, ss;
    ss = x % 60;
    x = x / 60;
    mm = x % 60;
    x = x / 60;
    hh = x % 60;
    h << hh;
    m << mm;
    s << ss;
    wxString res;
    if (ss < 10 && mm < 10) res = "0" + h + ":0" + m + ":0" + s;
    else if (ss < 10 && mm >= 10) res = "0" + h + ":" + m + ":0" + s;
    else if (ss >= 10 && mm < 10) res = "0" + h + ":0" + m + ":" + s;
    else res = "0" + h + ":" + m + ":" + s;
    return res;
}

wxVector<wxString> cStartmatch::separate(wxString s, int cols)
{
    wxVector<wxString> ans;
    wxVector<wxString> words;
    wxString cur = "";
    for (int i = 0; i < s.size(); i++)
        if (s[i] != ' ')
            cur += s[i];
        else
        {
            words.push_back(cur);
            cur = "";
        }
    words.push_back(cur);
    for (wxString word : words)
        if (ans.size() == 0 || word.size() + ans.back().size() > cols)
            ans.push_back(word);
        else
            ans.back() += " " + word;
    return ans;
}