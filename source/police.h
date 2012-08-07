//Police.h
#ifndef POLICE_H_
#define POLICE_H_
#include "Librerias.h"
class Police : public wxDialog
{
public:
	Police();
	void OnQuit(wxCommandEvent& event);
	void OnPrimero(wxCommandEvent& event);
	wxStaticText* ultimahora;
	wxButton* primero;


};

enum{
	ID_POLICE1 = 1224,
	ID_POLICE2 = 1225,
	ID_POLICE3 = 1226,
	ID_POLICE4 = 1227,
	ID_POLICE5 = 1228
};








#endif
