//Hipermercado

#ifndef HIPER_H_
#define HIPER_H_
#include "Librerias.h"

class Hiper : public wxDialog{
	public:
		Hiper();
		void Comprar(wxCommandEvent& event);
		void Tour(wxCommandEvent& event);
		void Trabajar(wxCommandEvent& event);
		void Suscribirse(wxCommandEvent& event);



};

enum{

	ID_HIPER1=1301,
	ID_HIPER2=1302,
	ID_HIPER3=1303,
	ID_HIPER4=1304
};




#endif
