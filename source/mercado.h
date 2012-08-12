//Mercado Central Estándar
#ifndef MERCADO_H_
#define MERCADO_H_
#include "Librerias.h"

class Mercado : public wxDialog{
public:
	Mercado();
	void Comprar(wxCommandEvent& event);
	void Vender(wxCommandEvent& event);
	void TransformarMateria(wxCommandEvent& event);
	void VenderMateria(wxCommandEvent& event);
	wxButton* Mcomprar;
	wxButton* Mvender;
	wxButton* Mtransformarmateria;
	wxButton* Mvendermateria;
	wxStaticText* info_mercado;
private:
	int precioproc[4];



};

enum{
	ID_MERCADO1,
	ID_MERCADO2,
	ID_MERCADO3,
	ID_MERCADO4


};




#endif
