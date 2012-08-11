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
	trabajar=new wxButton(hiperpanel, ID_HIPER3, "Trabajar (2 min)", wxPoint(50, 300));
	socios=new wxButton(hiperpanel, ID_HIPER4, "Hacerse socio", wxPoint(250, 300)); 


	Connect(ID_HIPER1,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Comprar));
	Connect(ID_HIPER2,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Tour));
	Connect(ID_HIPER3,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Trabajar));
	Connect(ID_HIPER4,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Suscribirse));
}
void Hiper::Comprar(wxCommandEvent& event)
{
	int precioproc[4];
	static int precioshiper[4]={100,200,300,50};
	if(estadoHiper==0){
	info_hiper->SetLabel("Compra lo que desees al precio indicado (o no)");
	wxProgressDialog esperar("Cadena Inc.","Buscando ofertas...",4);

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
	esperar.Update(4);estadoHiper=1;}else{
	//Comprar Android
	srand(time(NULL));
	int lazar=rand()%10+1;
	switch(lazar){
	case 1:wxMessageBox("En la caja no habia un movil, habia droga, creo que es ilegal...");money-=precioshiper[precioproc[0]]; droga++;break;
	case 2:{if(droga!=0){wxMessageBox("Tenias droga y la policía te ha visto. Pierdes la droga y debes pagar 2000 $");money-=2000;droga=0;}}break;
	default:wxMessageBox("Felicidades, comprado correctamente");money-=precioshiper[precioproc[0]]; electro++;
	}
	//Poner viejos botones
	comprar->SetLabel("Comprar por catalogo");
	tour->SetLabel("Tour completo");
	trabajar->SetLabel("Trabajar (2 min)");
	socios->SetLabel("Hacerse socio");
	estadoHiper=0;}

}
void Hiper::Tour(wxCommandEvent& event)
{
	if(estadoHiper==0){
	time_t tSac = time(NULL);       // instante actual
   	struct tm* tmP = localtime(&tSac);
	int hora=tmP->tm_hour;
	int minutos=tmP->tm_min;
	int segundos=tmP->tm_sec;
	wxMessageBox(wxString::Format("Son las %d:%d:%d!! Como quieres que esten despiertos",hora,minutos,segundos));}
}
void Hiper::Trabajar(wxCommandEvent& event)
{
	if(estadoHiper==0){
	wxProgressDialog trabajando("Cadena Inc.","Trabajando durante 2 minutos por 200 $",4);
	int trabajo;
	for(trabajo=0;trabajo!=4;trabajo++){
	trabajando.Update(trabajo);
	sleep(30);
	}
	money+=200;

	}
}
void Hiper::Suscribirse(wxCommandEvent& event)
{
	if(estadoHiper==0 && socio==1){
	int dalalai=wxMessageBox("Quieres hacerte socio por 300 $","Cadena Inc.",wxYES_NO|wxICON_QUESTION);
	if(dalalai==wxYES){
	socio=1;money-=300;
	}
	}
}
