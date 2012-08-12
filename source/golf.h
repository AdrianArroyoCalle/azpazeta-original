#ifndef GOLF_H_
#define GOLF_H_
#include "Librerias.h"
class Golf : public wxDialog
{
public:
	Golf();
	void VenderLujo(wxCommandEvent& event);
	void ComprarLujo(wxCommandEvent& event);
	void VenderDroga(wxCommandEvent& event);
	void Valladolid(wxCommandEvent& event);

};

enum{
	ID_VENDERLUJO,
	ID_COMPRARLUJO,
	ID_VENDERDROGA,
	ID_VALLADOLID

};


#endif
