#include "cPlayerstats.h"
#include "cStatsteam.h"

wxBEGIN_EVENT_TABLE(cPlayerstats, wxFrame)
EVT_PAINT(cPlayerstats::OnPaint)
EVT_BUTTON(6008, cPlayerstats::OnBackBtnClick)
EVT_TIMER(1111, addsecond)
wxEND_EVENT_TABLE()


void cPlayerstats::addsecond(wxTimerEvent& evt) {
	if (gif->Tell() < gif->Length()) {
		gif->Play();
	}
	else {
		gif->Seek(1000);
		gif->Play();
	}
}

cPlayerstats::cPlayerstats(wxString name, cStatsteam* ptr ) : wxFrame(nullptr, wxID_ANY, "Player", wxPoint(300, 50), wxSize(800 * 1.25, 600 * 1.25))
{
	pointer = ptr;
	vector<string> resultats;
	string filename = "C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/playerstats.txt";
	resultats = load_players(filename);

	pair<string, int[3]> duo;
	vector < pair<string, int[3]>> map;
	vector<string> aux;
	int index = 0, i = 0;
	for (auto res : resultats) {
		aux = separate_sus(res);
		duo.first = aux[0];
		int redcards, yellowcards, goals;
		goals = wxAtoi(aux[1]);
		redcards = wxAtoi(aux[2]);
		yellowcards = wxAtoi(aux[3]);
		duo.second[0] = redcards;
		duo.second[1] = yellowcards;
		duo.second[2] = goals;
		map.push_back(duo);
		if (duo.first == name) index = i;
		i++;
	}

	gif = new wxMediaCtrl();
	//int ok = gif->Create(this, wxID_ANY, wxT("giphy.gif"), wxDefaultPosition, wxSize(1000 * 1.92, 700*1.44));
	int ok = gif->Create(this, wxID_ANY, wxT("avatar5.mp4"), wxPoint(40, 25), wxSize(250, 250));
	if (!ok) wxMessageBox("Couldn't load file.");
	datetime = new wxTimer(this, 1111);
	datetime->Start(30);

	//PlayerImg = new wxStaticBitmap(this, 6020, wxBitmap("avatar2.png", wxBITMAP_TYPE_PNG), wxPoint(25, 25));
	DescriptionText = new wxStaticText(this, wxID_ANY, "Description:", wxPoint(40, 225 * 1.25));
	DescriptionText->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	Description = new wxListBox(this, wxID_ANY, wxPoint(40, 250* 1.25), wxSize(500, 150));
	Description->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	string phrase = name.ToStdString() + " was born on 24 June 1987 in Rosario, the third of four children of Jorge Messi, a steel factory manager, and his wife Celia Cuccittini, who worked in a magnet manufacturing workshop. On his father's side, he is of Italian and Spanish descent, the great-grandson of immigrants from the northcentral Adriatic Marche region of Italy and Catalonia, and on his mother's side, he has primarily Italian ancestry.[5][13] Growing up in a tight-knit, football-loving family, developed a passion for the sport from an early age, playing constantly with his older brothers, Rodrigo and Matías, and his cousins, Maximiliano and Emanuel Biancucchi, both of whom became professional footballers.[14] At the age of four he joined local club Grandoli, where he was coached by his father, though his earliest influence as a player came from his maternal grandmother, Celia, who accompanied him to training and matches.[15] He was greatly affected by her death, shortly before his eleventh birthday; since then, as a devout Catholic, he has celebrated his goals by looking up and pointing to the sky in tribute to his grandmother";
	vector<string> vec = separate(phrase, 39);
	for (auto v : vec) {
		Description->AppendString(v);
	}
	//double pow[5] = { p.TWK,p.ATK,p.DEF,p.SPD,p.TEC };

	srand(time(0));
	int fullpow = 0;
	for (int i = 0; i < 5; i++) {
		pow[i] = rand() % 18 + 1;
		fullpow += pow[i];
	}
	string position[3] = { "Attacker", "Defender", "Goal keeper" };
	int pos_index = rand() % 3;
	int weight = rand() % 40 + 70;
	int height = rand() % 20 + 170;
	string info[6] = { name.ToStdString(), separate_space(name.ToStdString())[0], position[pos_index], separate_space(name.ToStdString())[0], to_string(weight) + " kg" , to_string(height)  + " cm"};

	for (int i = 0; i < 6; i++)
	{
		PlayerInfo[i] = new wxStaticText(this, 6015 + i, PlayerInfoText[i] + info[i], wxPoint(250 * 1.25, (30 + i * 32) * 1.25));
		PlayerInfo[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	}

	for (int i = 0; i < 5; i++)
	{
		PowerStatText[i] = new wxStaticText(this, 6009 + i, PowersText[i], wxPoint(520 * 1.25, (250 + i * 30) * 1.25));
		PowerStatText[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		PowerGauge[i] = new wxGauge(this, 6001 + i, 20, wxPoint(570 * 1.25, (253 + i * 30) * 1.25));
		PowerGauge[i]->SetValue(pow[i]);
	}
	Strength = new wxStaticText(this, 6006, "Stength:", wxPoint(570 * 1.25, 400 * 1.25 + 3 ), wxSize(-1, -1));
	Strength->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));


	StrengthVal = new wxStaticText(this, 6007, to_string(fullpow), wxPoint(650 * 1.25, 400 * 1.25), wxSize(-1, -1));
	StrengthVal->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	Back = new wxButton(this, 6008, "Back", wxPoint(900 , 670), wxSize(-1, -1));

	wxStaticText *text[3];
	text[0] = new wxStaticText(this, wxID_ANY, "Goals = " + to_string(map[index].second[2]), wxPoint(40, 500));
	text[1] = new wxStaticText(this, wxID_ANY, "Red Cards = " + to_string(map[index].second[0]), wxPoint(40, 550));
	text[2] = new wxStaticText(this, wxID_ANY, "Yellow Cards = " + to_string(map[index].second[1]), wxPoint(40, 600));
	for (int i = 0; i < 3; i++) {
		text[i]->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	}
	text[1]->SetForegroundColour(wxColour(219, 68, 55));
	text[2]->SetForegroundColour(wxColour(228, 202, 14));
		


}


cPlayerstats::~cPlayerstats()
{
	datetime->Stop();
	pointer->Enable(true);
}

void cPlayerstats::OnBackBtnClick(wxCommandEvent& evt)
{
	this->Close();
	evt.Skip();
}

wxPoint* Pentagone(float sc1 = 1.0, float sc2 = 1.0, float sc3 = 1.0, float sc4 = 1.0, float sc5 = 1.0)
{
	float L = -13.25, c1 = -3.659, c2 = 10, s1 = -12.788, s2 = -7.714, scale = 6;

	wxPoint* point = new wxPoint[5];
	point[0] = wxPoint(0, scale * sc1 * L);
	point[1] = wxPoint(scale * sc2 * s1, scale * sc2 * c1);
	point[2] = wxPoint(scale * sc3 * s2, scale * sc3 * c2);
	point[3] = wxPoint(-scale * sc4 * s2, scale * sc4 * c2);
	point[4] = wxPoint(-scale * sc5 * s1, scale * sc5 * c1);

	return point;
}

void cPlayerstats::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(*wxBLACK, 1, wxPENSTYLE_SOLID));
	dc.SetBrush(wxBrush(wxColor(206, 206, 206), wxBRUSHSTYLE_SOLID));

	dc.DrawPolygon(5, Pentagone(), 630*1.25, 120 * 1.25);
	dc.SetBrush(wxBrush(wxColor(125, 153, 166), wxBRUSHSTYLE_SOLID));
	float sc1 = pow[0] / 20.0F;
	float sc2 = pow[1] / 20.0F;
	float sc3 = pow[2] / 20.0F;
	float sc4 = pow[3] / 20.0F;
	float sc5 = pow[4] / 20.0F;
	dc.DrawPolygon(5, Pentagone(sc1, sc2, sc3, sc4, sc5), 630 * 1.25, 120 * 1.25);



	evt.Skip();
}