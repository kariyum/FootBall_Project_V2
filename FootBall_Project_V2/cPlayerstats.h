#pragma once
#include "wx/wx.h"
#include "api.h"
#include <wx/listctrl.h>
#include "wx/mediactrl.h"
class cStatsteam;
class cPlayerstats : public wxFrame
{
private:
	wxStaticText* Strength = nullptr;
	wxStaticText* StrengthVal = nullptr;
	wxGauge* PowerGauge[5];
	wxButton* Back = nullptr;
	const char* PowersText[5] = { "TWK" , "ATK" ,"DEF" , "SPD" ,"TEC" };
	const char* PlayerInfoText[6] = { "Name: ","Nationality: ", "Position: ", "Height: ", "Weight: ", "Height : " };
	wxStaticText* PlayerInfo[6];
	wxStaticText* PowerStatText[5];
	wxStaticBitmap* PlayerImg;

	wxStaticText* DescriptionText;
	wxListBox* Description;
	wxListCtrl *list;
	int pow[5] = { 10, 10, 10, 10, 10 };
	vector < pair<string, int>> map;
	wxTimer* datetime;
	int time1111 = 0;
	wxMediaCtrl* gif;

	cStatsteam* pointer;
public:

	cPlayerstats(wxString name, cStatsteam* ptr);
	~cPlayerstats();

	//event handlers
	void OnBackBtnClick(wxCommandEvent& evt);
	void OnPaint(wxPaintEvent& evt);
	void addsecond(wxTimerEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

