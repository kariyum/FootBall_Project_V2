#include "cStartmatch.h"
#include "cPlayerselection.h"

wxBEGIN_EVENT_TABLE(cStartmatch, wxFrame)
EVT_BUTTON(1001, onendmatch)
EVT_BUTTON(1002, onaddnote)
EVT_BUTTON(1003, onstartstoptime)
EVT_BUTTON(1004, ontakebreak)
EVT_TIMER(1111, addsecond)
wxEND_EVENT_TABLE()

cStartmatch::cStartmatch(wxString team1, wxString team2, vector<string> players1, cNextcreate* parent_ptr ) : wxFrame(nullptr, wxID_ANY, "Match", wxPoint(300, 150), wxSize(1200, 800)) {
    players = players1;
    parent_pointer = parent_ptr;

    windowtitle = new wxStaticText(this, wxID_ANY, "MATCH", wxPoint(10, 10));
    windowtitle->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true));

    int x1 = 370;


    teams_title[0] = new wxStaticText(this, wxID_ANY, team1, wxPoint(x1, 50));
    teams_title[1] = new wxStaticText(this, wxID_ANY, team2, wxPoint(x1 + 300, 50));

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

            /*
            wxString s;
            s << (i + j * 11) % 11 + 1;
            */
            if (i + j * 11 < 11) playersname[i + j * 11] = new wxStaticText(this, wxID_ANY, players1[i + j * 11], wxPoint(x + j * dx + 50, y + i * dy));
            else playersname[i + j * 11] = new wxStaticText(this, wxID_ANY, players1[i + j * 11], wxPoint(x + j * dx - 300, y + i * dy));
            
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
    initialize();
    commentary = new wxMediaCtrl();
    int ok = commentary->Create(this, wxID_ANY, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/commentary.wav", wxDefaultPosition);
    if (!ok) wxMessageBox("Couldn't load file.");
    goalcommentary = new wxMediaCtrl();

    ok = goalcommentary->Create(this, wxID_ANY, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/goaaal.wav", wxDefaultPosition);
    if (!ok) wxMessageBox("Couldn't load file.");

}
cStartmatch::cStartmatch(wxString team1, wxString team2, vector<string> players1, cPlayerselection* parent_ptr ) : wxFrame(nullptr, wxID_ANY, "Match", wxPoint(300, 150), wxSize(1200, 800)) {
    /*
    //iscnextcreate = false;
    players = players1;
    parent_pointer1 = parent_ptr;

    windowtitle = new wxStaticText(this, wxID_ANY, "MATCH", wxPoint(10, 10));
    windowtitle->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true));

    int x1 = 370;


    teams_title[0] = new wxStaticText(this, wxID_ANY, team1, wxPoint(x1, 50));
    teams_title[1] = new wxStaticText(this, wxID_ANY, team2, wxPoint(x1 + 300, 50));

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

            /*
            wxString s;
            s << (i + j * 11) % 11 + 1;
            */
            /*

            if (i + j * 11 < 11) playersname[i + j * 11] = new wxStaticText(this, wxID_ANY, players1[i + j * 11], wxPoint(x + j * dx + 50, y + i * dy));
            else playersname[i + j * 11] = new wxStaticText(this, wxID_ANY, players1[i + j * 11], wxPoint(x + j * dx - 300, y + i * dy));
            
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
    initialize();
    commentary = new wxMediaCtrl();
    int ok = commentary->Create(this, wxID_ANY, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/commentary.wav", wxDefaultPosition);
    if (!ok) wxMessageBox("Couldn't load file.");
    goalcommentary = new wxMediaCtrl();
    ok = goalcommentary->Create(this, wxID_ANY, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/goaaal.wav", wxDefaultPosition);
    */
}

cStartmatch::cStartmatch(wxString team1, wxString team2, vector<string> players1, cKnockout* parent_ptr ) : wxFrame(nullptr, wxID_ANY, "Match", wxPoint(300, 150), wxSize(1200, 800)) {
    iscnextcreate = false;
    players = players1;
    parent_pointer2 = parent_ptr;

    windowtitle = new wxStaticText(this, wxID_ANY, "MATCH", wxPoint(10, 10));
    windowtitle->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true));

    int x1 = 370;


    teams_title[0] = new wxStaticText(this, wxID_ANY, team1, wxPoint(x1, 50));
    teams_title[1] = new wxStaticText(this, wxID_ANY, team2, wxPoint(x1 + 300, 50));

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

            /*
            wxString s;
            s << (i + j * 11) % 11 + 1;
            */
            if (i + j * 11 < 11) playersname[i + j * 11] = new wxStaticText(this, wxID_ANY, players1[i + j * 11], wxPoint(x + j * dx + 50, y + i * dy));
            else playersname[i + j * 11] = new wxStaticText(this, wxID_ANY, players1[i + j * 11], wxPoint(x + j * dx - 300, y + i * dy));
            
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
    initialize();
    commentary = new wxMediaCtrl();
    int ok = commentary->Create(this, wxID_ANY, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/commentary.wav", wxDefaultPosition);
    if (!ok) wxMessageBox("Couldn't load file.");
    goalcommentary = new wxMediaCtrl();
    ok = goalcommentary->Create(this, wxID_ANY, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/goaaal.wav", wxDefaultPosition);
    if (!ok) wxMessageBox("Couldn't load file.");
    finalcommentary = new wxMediaCtrl();
    ok = finalcommentary->Create(this, wxID_ANY, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/final.wav", wxDefaultPosition);
    if (!ok) wxMessageBox("Couldn't load file.");
    if (parent_pointer2->finaaal) {
        wxMessageBox("Final match is about to begin !");
        finalcommentary->Play();
    }
}

cStartmatch::cStartmatch(wxPanel* p1, wxString team1, wxString team2, vector<string>& players1, string tab[22][3], vector<string> n_notes) : wxFrame(nullptr, wxID_ANY, "", wxPoint(0, 0), wxSize(20, 20)) {
    windowtitle = new wxStaticText(p1, wxID_ANY, "MATCH", wxPoint(10, 10));
    windowtitle->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true));

    int x1 = 370;


    teams_title[0] = new wxStaticText(p1, wxID_ANY, team1, wxPoint(x1, 50));
    teams_title[1] = new wxStaticText(p1, wxID_ANY, team2, wxPoint(x1 + 300, 50));

    for (int i = 0; i < 2; i++) teams_title[i]->SetFont(wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    m_vs_title = new wxStaticText(p1, wxID_ANY, "----", wxPoint(x1 + 190, 50));
    m_vs_title->SetFont(wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    m_goals[0] = new wxStaticText(p1, wxID_ANY, "0", wxPoint(x1 + 150, 50));
    m_goals[1] = new wxStaticText(p1, wxID_ANY, "0", wxPoint(x1 + 250, 50));
    for (int i = 0; i < 2; i++) m_goals[i]->SetFont(wxFont(21, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    
    int dx = 1030;
    int dy = 50;

    int x = 100;
    int y = 150;

    redcards = new wxButton * [22];
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 11; i++) {
            redcards[i + j * 11] = new wxButton(p1, wxID_ANY, tab[i + j *11][1], wxPoint(x + j * dx, y + i * dy), wxSize(30, 30), wxBORDER_NONE);
            redcards[i + j * 11]->SetBackgroundColour(wxColor(255, 47, 52));
            redcards[i + j * 11]->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            if (i + j * 11 < 11) playersname[i + j * 11] = new wxStaticText(p1, wxID_ANY, players1[i + j * 11].c_str(), wxPoint(x + j * dx + 50, y + i * dy));
            else playersname[i + j * 11] = new wxStaticText(p1, wxID_ANY, players1[i + j * 11], wxPoint(x + j * dx - 300, y + i * dy));

            playersname[i + j * 11]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

            yellowcards[i + j * 11] = new wxButton(p1, wxID_ANY, tab[i + j * 11][2], wxPoint(x - 70 + j * dx, y + i * dy), wxSize(30, 30), wxBORDER_NONE);
            yellowcards[i + j * 11]->SetBackgroundColour(wxColor(240, 192, 0));
            yellowcards[i + j * 11]->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        }
    }
    //wxButton* test = new wxButton(this, 1000, "delete");
    m_matchnotes = new wxStaticText(p1, wxID_ANY, "Match notes", wxPoint(510, 120));
    m_matchnotes->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    //m_addnote = new wxButton(p1, 1002, "Add note", wxPoint(371, 624)); //x=540 y=120
    m_note = new wxListBox(p1, wxID_ANY, wxPoint(370, 150), wxSize(405, 540));
    //m_notetext = new wxTextCtrl(p1, wxID_ANY, "", wxPoint(370, 650), wxSize(405, 30));
    //m_notetext->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    m_note->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    //====================================================================================================
    //m_endmatch = new wxButton(p1, 1001, "End match", wxPoint(540, 700));
    wxVector<wxString> ans;
    for (auto note : n_notes) {
        ans = separate(note, 38);
        for (int i = 0; i < ans.size(); i++) {
            m_note->AppendString(ans[i]);
        }
    }
    m_goals[0]->SetLabel(separate_sus(ans[0].ToStdString())[0]);
    m_goals[1]->SetLabel(separate_sus(ans[0].ToStdString())[1]);
    m_note->Delete(m_note->GetCount()-1);
}


cStartmatch::~cStartmatch() {
    //datetime->Stop();
}

void cStartmatch::onendmatch(wxCommandEvent& evt) {
    //create file matchresults
    //add match resulsts
    string filename_results = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + (teams_title[0]->GetLabel() + ";" + teams_title[1]->GetLabel() + ";" + "results.txt").ToStdString();
    //goals red yellow
    string line;
    vector<string> suspended_players1;
    vector<string> suspended_players;
    suspended_players1 = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/suspended.txt");
    for (int i = 0; i < suspended_players1.size(); i++) {
        vector<string> line;
        line = separate_sus(suspended_players1[i], 0);
        if (line[1] == teams_title[0]->GetLabel().ToStdString() || line[1] == teams_title[1]->GetLabel().ToStdString()) {
            //wxMessageBox("Removed");
        }
        else {
            suspended_players.push_back(suspended_players1[i]);
        }
    }
    string line2; //for player results file.
    vector<string> vector_player_result_same_file;
    for (int i = 0; i < 22; i++) {
        wxString s1, s2, s3;
        s1 << player_results[i][0];
        s2 << player_results[i][1];
        s3 << player_results[i][2];
        line = s1.ToStdString() + ";" + s2.ToStdString() + ";" + s3.ToStdString() + ";";
        vector_player_resulsts.push_back(line);
        
        line2 = players[i] + ";" + line;
        vector_player_result_same_file.push_back(line2);

        if (player_results[i][1] > 0 || player_results[i][2] > 1) {
            string team_name;
            if (i < 11) team_name = teams_title[0]->GetLabel().ToStdString();
            else team_name = teams_title[1]->GetLabel().ToStdString();
            suspended_players.push_back(playersname[i]->GetLabel().ToStdString() + ";" + team_name);
        }
    }
    
    save_groups(vector_player_resulsts, filename_results);
    save_groups(suspended_players, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/suspended.txt");
    save_playerstats(vector_player_result_same_file);

    //save_groups(vector_player_result_same_file, "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/playerstats.txt");

    //create file matchnotes
    string filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + (teams_title[0]->GetLabel() + ";" + teams_title[1]->GetLabel() + ";" + "notes.txt").ToStdString();
    wxString s1 = m_goals[0]->GetLabel() + ";" + m_goals[1]->GetLabel();

    notes.push_back(s1.ToStdString());
    save_groups(notes, filename);
    
    //create winner file
    string filename_winners = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/winners.txt";
    int goals1 = wxAtoi(m_goals[0]->GetLabel());
    int goals2 = wxAtoi(m_goals[1]->GetLabel());
    vector<string> winner;
    string winner_line;
    winner_line = teams_title[0]->GetLabel().ToStdString() + ";" + teams_title[1]->GetLabel().ToStdString() +";";
    if (goals1 < goals2) winner_line += "1";
    else winner_line += "0";
    winner.push_back(winner_line);
    save_winners(winner, filename_winners);

    //need to look at it again!!!!!!!!!!!!!!!!!! probably not
    if (iscnextcreate) {
        parent_pointer->displaywinners();
        parent_pointer->playerslistdelete();
        this->Close();
        parent_pointer->notification_done_matchs();
    }
    else {
        wxString m_winner_to_display;
        if (goals1 < goals2) m_winner_to_display = teams_title[1]->GetLabel();
        else m_winner_to_display=teams_title[0]->GetLabel();
        
        parent_pointer2->displaywinners(m_winner_to_display);
        if (parent_pointer2->finaaal) parent_pointer2->Close();
        this->Close();
    }
    datetime->Stop();

    evt.Skip();
}
void cStartmatch::save_playerstats(vector<string> vec) {

    bool exists = false;
    ifstream input("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/playerstats.txt", ios::in);
    string s;
    vector<string> teams;
    int score[3];
    while (getline(input, s))
    {
        int i;
        exists = false;
        int index;
        for (i = 0; i < vec.size(); i++) {
            if (separate_sus(vec[i])[0] == separate_sus(s)[0]) {
                exists = true;
                index = i;
                break;
            }
        }
        if (exists) {
            score[0] = wxAtoi(separate_sus(s)[1]) + wxAtoi(separate_sus(vec[index])[1]);
            score[1] = wxAtoi(separate_sus(s)[2]) + wxAtoi(separate_sus(vec[index])[2]);
            score[2] = wxAtoi(separate_sus(s)[3]) + wxAtoi(separate_sus(vec[index])[3]);
            wxString ss;
            ss << score[0] << ";";
            ss << score[1] << ";";
            ss << score[2] << ";";
            vec[index] = separate_sus(vec[index])[0] + ";" + ss.ToStdString();
            //teams.push_back(separate_sus(vec[i])[0] + ";" + ss.ToStdString());
        }
        else {
            vec.push_back(s);
        }
    }
    input.close();
    
    ofstream output("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/playerstats.txt", ios::out);
    for (int i = 0; i < vec.size(); i++) output << vec[i] << endl;
    output.close();
}

void cStartmatch::onaddnote(wxCommandEvent& evt) {
    if (m_notetext->GetValue() != "") {
        wxString s;
        s = inttotime(time1111);
        wxString stringvalue = m_notetext->GetValue();

        notes.push_back(stringvalue.ToStdString()); //

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
        commentary->Play();
        if (finalcommentary != nullptr ) finalcommentary->Stop();
    }
    else {
        datetime->Stop();
        m_startstoptime->SetLabel("Resume time");
        commentary->Pause();
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
        //m_choices[evt.GetId()-10]->AppendString(wxT("Player " + s));
        m_choices[evt.GetId()-10]->AppendString(players[j + (evt.GetId() - 10) * 11]);

    }
    
    m_choices[evt.GetId() - 10]->Select(0);
    created[evt.GetId() - 10] = 1;
    evt.Skip();
}

void cStartmatch::onchoiceselection(wxCommandEvent& evt) {
    int Id = evt.GetId() - 100;
    wxMessageBox(m_choices[Id]->GetStringSelection() + " has scored a goal !");
    
    int player_index = m_choices[Id]->GetSelection();
    player_results[player_index][0]++;

    int num = wxAtoi(m_goals[Id]->GetLabel());
    num++;
    wxString ss;
    ss << num;
    m_goals[Id]->SetLabel(ss);
    m_choices[Id]->Hide();

    wxString s;
    s = inttotime(time1111);
    //wxString stringvalue = teams_title[Id]->GetLabel() + " " + m_choices[Id]->GetStringSelection() + " has scored a goal !";
    wxString stringvalue = m_choices[Id]->GetStringSelection() + " has scored a goal !";

    notes.push_back(stringvalue.ToStdString());

    wxVector<wxString> ans;

    ans = separate(s + " : " + stringvalue, 38);
    for (int i = 0; i < ans.size(); i++) {
        m_note->AppendString(ans[i]);
    }
    m_note->PageDown();
    commentary->Pause();
    goalcommentary->Play();
    wxSleep(11);
    commentary->Play();
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

        notes.push_back(time_string.ToStdString() + ": " + "A yellowcard has been added to " + playersname[Id]->GetLabel().ToStdString());
        player_results[Id][2]++;

        ans = separate(time_string + ": " + "A yellowcard has been added to " + playersname[Id]->GetLabel(), 38);
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

        notes.push_back(time_string.ToStdString() + ": " + "A redcard has been added to " + playersname[Id]->GetLabel().ToStdString());
        player_results[Id][1]++;

        ans = separate(time_string + ": " + "A redcard has been added to " + playersname[Id]->GetLabel(), 38);
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

            notes.push_back(time_string.ToStdString() + ": " + "A yellowcard has been removed from " + playersname[Id]->GetLabel().ToStdString());
            player_results[Id][2]--;

            ans = separate(time_string + ": " + "A yellowcard has been removed from " + playersname[Id]->GetLabel(), 38);
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
            //team_name << Id / 11 + 1;
            team_name = teams_title[Id]->GetLabel();

            wxVector<wxString> ans;

            notes.push_back(time_string.ToStdString() + ": " + "A redcard has been removed from " + playersname[Id]->GetLabel().ToStdString());
            player_results[Id][1]--;

            ans = separate(time_string + ": " + "A redcard has been removed from " + playersname[Id]->GetLabel(), 38);
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

        notes.push_back(stringvalue.ToStdString());

        wxVector<wxString> ans;

        ans = separate(s + " : " + stringvalue, 38);
        for (int i = 0; i < ans.size(); i++) {
            m_note->AppendString(ans[i]);
        }
        m_startstoptime->SetLabel("Resume time");
        datetime->Stop();
        commentary->Play();
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

        notes.push_back(s.ToStdString() + " : " + stringvalue.ToStdString());

        ans = separate(s + " : " + stringvalue, 38);
        for (int i = 0; i < ans.size(); i++) {
            m_note->AppendString(ans[i]);
        }
        recenttime = time1111;
        datetime->Start();
        m_startstoptime->SetLabel("Stop time");
        commentary->Pause();
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

void cStartmatch::initialize() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 3; j++) {
            player_results[i][j] = 0;
        }
    }
}

