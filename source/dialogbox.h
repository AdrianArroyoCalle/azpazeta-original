#ifndef DIAGBOX_H_
#define DIAGBOX_H_
#include "Librerias.h"

class DialogBox : public wxDialog {
public:
	DialogBox();
	void Next(wxCommandEvent& event);
	wxStaticText* line1;
	wxStaticText* line2;
	wxStaticText* line3;
	wxStaticText* line4;
	wxStaticText* line5;
	wxStaticText* line6;
	wxStaticText* line7;
	wxStaticText* line8;
	wxStaticText* line9;
	wxStaticText* line10;
	wxPanel* diagpanel;
};

enum{
	ID_NEXT
};





#endif
