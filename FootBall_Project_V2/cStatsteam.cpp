#include "cStatsteam.h"
#include "cPlayerstats.h"
#include "cCheckstats.h"

wxBEGIN_EVENT_TABLE(cStatsteam, wxFrame)
EVT_LIST_ITEM_SELECTED(100, onlistselection)
EVT_LISTBOX(200, onboxselection)
wxEND_EVENT_TABLE()

void cStatsteam::onboxselection(wxCommandEvent& evt) {
    cPlayerstats* playerstats_frame = new cPlayerstats(listbox->GetStringSelection(), this);
    playerstats_frame->Show();
    this->Enable(false);
    evt.Skip();
}
cStatsteam::cStatsteam() : wxFrame(nullptr, wxID_ANY, "Team stats", wxPoint(300, 50), wxSize(800 * 1.25 + 400, 600 * 1.25)) {
	windowtitle = new wxStaticText(this, wxID_ANY, "Teams stats", wxPoint(10, 10));
	windowtitle->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true));


    list = new wxListCtrl(this, 100, wxPoint(40,140), wxSize(900,500), wxLC_REPORT);

    // Add first column       
    wxListItem col0;
    col0.SetId(0);
    col0.SetText(_("Team Name"));
    col0.SetWidth(170);
    list->InsertColumn(0, col0);

    // Add second column
    wxListItem col1;
    col1.SetId(1);
    col1.SetText(_("Victories"));
    col1.SetWidth(170);
    list->InsertColumn(1, col1);

    // Add third column     
    wxListItem col2;
    col2.SetId(2);
    col2.SetText(_("Goals"));
    col2.SetWidth(170);
    list->InsertColumn(2, col2);

    // Add forth column     
    wxListItem col3;
    col3.SetId(3);
    col3.SetText(_("Red Cards"));
    col3.SetWidth(170);
    list->InsertColumn(3, col3);

    // Add fifth column     
    wxListItem col4;
    col4.SetId(4);
    col4.SetText(_("Yellow cards"));
    col4.SetWidth(170);
    list->InsertColumn(4, col4);

    vector<string> winners = load_winners("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/teamstats.txt");
    
    for (int i = 0; i < winners.size(); i++) {
        list->InsertItem(i,separate_sus(winners[i])[0]);
        list->SetItem(i, 1,separate_sus(winners[i])[1]);
        list->SetItem(i, 2,"0");
        list->SetItem(i, 3,"0");
    }
    vector<string> resultats;
    string filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/playerstats.txt";
    resultats = load_players(filename);

    pair<string, int[2]> duo;
    vector < pair<string, int[2]>> map;
    vector<string> aux;
    for (auto res : resultats) {
        aux = separate_sus(res);
        duo.first = aux[0];
        int redcards, yellowcards;
        //score += 5 * wxAtoi(aux[1]);
        redcards= wxAtoi(aux[2]);
        yellowcards = wxAtoi(aux[3]);
        duo.second[0] = redcards;
        duo.second[1] = yellowcards;

        map.push_back(duo);
    }

    for (int i = 0; i < winners.size(); i++) {
        int redcards = 0, yellowcards = 0;
        for (int j = 0; j < map.size(); j++) {
            if ( separate_space(map[j].first)[0] == list->GetItemText(i, 0)) {
                redcards += map[j].second[0];
                yellowcards += map[j].second[1];
            }
        }
        
        wxString s1="", s2="";
        s1 << redcards;
        s2 << yellowcards;
        list->SetItem(i, 3, s1);
        list->SetItem(i, 4, s2);
    }

    listbox = new wxListBox(this, 200, wxPoint(1000, 140), wxSize(200, 500));
    
    vector<string> players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/" + list->GetItemText(0, 0).ToStdString() +".txt");
    if (players.size() != 0) {
        for (int i = 0; i < players.size(); i++) listbox->AppendString(players[i]);

    }
    else {
        for (int i = 0; i < 22; i++) {
            wxString number;
            number << i + 1;
            listbox->AppendString(list->GetItemText(0, 0).ToStdString() + wxT(" player[") + number + "]");
        }
    }
    listbox->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));



}


cStatsteam::~cStatsteam() {
    cCheckstats* frame = new cCheckstats();
    frame->Show();
}

void cStatsteam::onlistselection(wxListEvent& evt) {
    long itemIndex = -1;
    wxString str;
    while ((itemIndex = list->GetNextItem(itemIndex,
        wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
        // Got the selected item index
        //wxLogDebug(list->GetItemText(itemIndex));
        str = list->GetItemText(itemIndex);
    }
    listbox->Clear();
    vector<string> players = load_players("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/"+ str.ToStdString() + ".txt");
    if (players.size() != 0) {
        for (int i = 0; i < players.size(); i++) listbox->AppendString(players[i]);

    }
    else {
        for (int i = 0; i < 22; i++) {
            wxString number;
            number << i + 1;
            listbox->AppendString(str + wxT(" player[") + number + "]");
        }
    }
    evt.Skip();
}