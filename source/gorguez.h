//gorguez
#ifndef GORGUEZ_H_
#define GORGUEZ_H_
#include "Librerias.h"

class Gorguez : public wxDialog{
	public:
		Gorguez();
		void Comprar(wxCommandEvent& event);
		void Tour(wxCommandEvent& event);
		void Trabajar(wxCommandEvent& event);
		void Suscribirse(wxCommandEvent& event);
		wxButton* socios;
		wxButton* trabajar;
		wxButton* tour;
		wxButton* comprar;
		wxStaticText* info_hiper;

};

enum{
	ID_GOR1,
ID_GOR2,
ID_GOR3,
ID_GOR4,
ID_GOR5,
ID_GOR6
	
};




#endif
