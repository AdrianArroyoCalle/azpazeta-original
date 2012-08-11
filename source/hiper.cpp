//Hiper.cpp
#include "hiper.h"

extern int socio, money, electro, food, textil, droga, blacklist;

Hiper::Hiper() : wxDialog(NULL, wxID_ANY, wxT("Cadena Inc."), wxPoint(-1,-1), wxSize(400,400))
{
	wxPanel* hiperpanel=new wxPanel(this);
	wxStaticText* info_hiper=new wxStaticText(hiperpanel, wxID_ANY, HIPER_101);
	wxButton* comprar=new wxButton(hiperpanel, ID_HIPER1, "Comprar por catalogo", wxPoint(50,200));
	wxButton* tour=new wxButton(hiperpanel, ID_HIPER2, "Tour completo", wxPoint(250, 200));
	wxButton* trabajar=new wxButton(hiperpanel, ID_HIPER3, "Trabajar (5 min)", wxPoint(50, 300));
	wxButton* socios=new wxButton(hiperpanel, ID_HIPER4, "Hacerse socio", wxPoint(250, 300)); 
}

void Comprar(wxCommandEvent& event)
{

}
void Tour(wxCommandEvent& event)
{

}
void Trabajar(wxCommandEvent& event)
{

}
void Suscribirse(wxCommandEvent& event)
{

}
