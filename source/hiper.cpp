//Hiper.cpp
#include "hiper.h"
#include <wx/mediactrl.h>
extern int socio, money, electro, food, textil, droga, blacklist;
int estadoHiper=0;

Hiper::Hiper() : wxDialog(NULL, wxID_ANY, wxT("Cadena Inc."), wxPoint(-1,-1), wxSize(400,400))
{
	wxPanel* hiperpanel=new wxPanel(this);
	info_hiper=new wxStaticText(hiperpanel, wxID_ANY, HIPER_101);
	comprar=new wxButton(hiperpanel, ID_HIPER1, "Comprar por catalogo", wxPoint(50,200));
	tour=new wxButton(hiperpanel, ID_HIPER2, "Tour completo", wxPoint(250, 200));
	trabajar=new wxButton(hiperpanel, ID_HIPER3, "Trabajar (5 min)", wxPoint(50, 300));
	socios=new wxButton(hiperpanel, ID_HIPER4, "Hacerse socio", wxPoint(250, 300)); 


	Connect(ID_HIPER1,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Comprar));
	Connect(ID_HIPER2,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Tour));
	Connect(ID_HIPER3,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Trabajar));
	Connect(ID_HIPER4,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Suscribirse));
}
void Hiper::Comprar(wxCommandEvent& event)
{
	if(estadoHiper==0){
	info_hiper->SetLabel("Compra lo que desees al precio indicado (o no)");
	//wxMediaCtrl* jaiho=new wxMediaCtrl(this, wxID_ANY, "/usr/share/Azpazeta/audio/JaiHo.mp3");
	//jaiho.Play();
	wxProgressDialog esperar("Cadena Inc.","Buscando ofertas...",4);
	int precioproc[4];
	static int precioshiper[4]={100,200,300,50};
	srand(time(NULL));
	precioproc[0]=rand()%4+1;
	comprar->SetLabel(wxString::Format("Android %d", precioshiper[precioproc[0]]));
	esperar.Update(1);
	precioproc[1]=rand()%4+1;
	tour->SetLabel(wxString::Format("Paella %d", precioshiper[precioproc[1]]));
	esperar.Update(2);
	precioproc[2]=rand()%4+1;
	trabajar->SetLabel(wxString::Format("Traje %d", precioshiper[precioproc[2]]));
	esperar.Update(3);
	precioproc[3]=rand()%4+1;
	socios->SetLabel(wxString::Format("... %d",precioshiper[precioproc[3]]));
	esperar.Update(4);estadoHiper=1;}else{estadoHiper=0;}
	//esperar.Update(5);
}
void Hiper::Tour(wxCommandEvent& event)
{

}
void Hiper::Trabajar(wxCommandEvent& event)
{

}
void Hiper::Suscribirse(wxCommandEvent& event)
{

}
