//Hipermercado

#ifndef HIPER_H_
#define HIPER_H_
#include "Librerias.h"

class Hiper : public wxDialog{
	public:
		Hiper();
		//ComprarDlg();
		void Comprar(wxCommandEvent& event);
		void Tour(wxCommandEvent& event);
		void Trabajar(wxCommandEvent& event);
		void Suscribirse(wxCommandEvent& event);
		wxButton* socios;
		wxButton* trabajar;
		wxButton* tour;
		wxButton* comprar;
		wxStaticText* info_hiper;
	private:
		int precioproc[4];
};

enum{

	ID_HIPER1=1301,
	ID_HIPER2=1302,
	ID_HIPER3=1303,
	ID_HIPER4=1304,
	ID_COMPRAR1,
ID_COMPRAR2,
ID_COMPRAR3,
ID_COMPRAR4,
ID_COMPRAR5,
ID_COMPRAR6
	
};




#endif
