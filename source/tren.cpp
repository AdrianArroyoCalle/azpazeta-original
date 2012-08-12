#ifndef TREN_H_
#define TREN_H_
#include "wx/wxprec.h"
#include <wx/event.h>
#include <wx/sound.h>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <iostream>
#include "VarGlobal.h"
#include <time.h>
#include <wx/progdlg.h>
#include "Idiomas.h"
using namespace std;

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

	static wxString viajarcity[5]={"Gorguez","Centralia","Obscura","Wellville","Orlan\t"};
	static int viajarprecio[5]={300,40,1000,500,120};
	int bucle=0;
	wxString linea1[5];
	int anterior;
	int viajarint;
	int viajarintprecio;
	wxString ciudadOrden[5];
	int CiudadOrden=0;
	int precioOrden[5];
	int PrecioOrden=0;
	extern int money, city;

class TrenDialog : public wxDialog
{
public:
	TrenDialog();
	void OnQuit(wxCommandEvent& event);
	void OnPrimero(wxCommandEvent& event);
void OnSegundo(wxCommandEvent& event);
void OnTercero(wxCommandEvent& event);
void OnCuarto(wxCommandEvent& event);
void OnQuinto(wxCommandEvent& event);
	void ProcesarViajes(wxString destino, int precio);
	wxStaticText* ciudad;
	wxStaticText* salida;
	wxStaticText* precio;
	wxStaticText* ciudad1;
	wxStaticText* salida1;
	wxStaticText* precio1;
	wxStaticText* ultimaHora;
	wxStaticText* ultimahora;
	wxButton* primero;
	wxButton* segundo;
	wxButton* tercero;
	wxButton* cuarto;
	wxButton* quinto;
	wxButton* salir;
	wxButton* noHayOtro;


};
enum{
	ID_TREN1 = 1024,
	ID_TREN2 = 1025,
	ID_TREN3 = 1026,
	ID_TREN4 = 1027,
	ID_TREN5 = 1028
};

TrenDialog::TrenDialog()
       : wxDialog(NULL, wxID_ANY, wxT("Estacion de trenes central"), wxPoint(-1,-1), wxSize(400,400))
{	
	wxProgressDialog randomizar("Brinnwell Transport","Espera mientras se cargan los viajes",5);
	wxPrintf("Empieza el problema");
	while(bucle<5){
	wxPrintf("No es igual a 5");
	srand(time(NULL));
	viajarint=rand()%5;
	//wxPrintf("Todavia no violado");
	//srand(time(NULL));
	//viajarintprecio=rand()%5;
	if(anterior!=viajarint){
	wxPrintf("Todavia no violado");
	linea1[bucle]=wxString::Format("%s\t\t\tInmediato\t\t\t%d",viajarcity[viajarintprecio],viajarprecio[viajarint]);
	ciudadOrden[CiudadOrden]=viajarcity[viajarintprecio];
	precioOrden[PrecioOrden]=viajarprecio[viajarint];
	CiudadOrden++;
	PrecioOrden++;
	//wxMessageBox(linea1[bucle]);
	bucle++;
	randomizar.Update(bucle);
	viajarintprecio++;
	anterior=viajarint;
	wxPrintf("Todavia no violado");
	}else{wxPrintf("Es igual a 5");}
	}
	wxPrintf("Cargado");
	wxPanel* panelTren=new wxPanel(this);
	wxPrintf("Final");
	wxInitAllImageHandlers();
	wxBitmap estacion("/opt/extras.ubuntu.com/azpazeta/media/tren.png",wxBITMAP_TYPE_PNG);
	wxStaticBitmap* fondo_estacion=new wxStaticBitmap(panelTren, wxID_ANY, estacion, wxPoint(-1,-1));
	wxStaticText* cuantomoney=new wxStaticText(panelTren, wxID_ANY, wxString::Format(wxT("Dinero actual: %d"),money));
	ciudad=new wxStaticText(panelTren, wxID_ANY, wxT("Destino\t\t\tHora salida\t\t\tPrecio"),wxPoint(2, 100));

ciudad1=new wxStaticText(panelTren, wxID_ANY, linea1[0],wxPoint(2, 150));
salida1=new wxStaticText(panelTren, wxID_ANY, linea1[1],wxPoint(2, 175));
precio1=new wxStaticText(panelTren, wxID_ANY, linea1[2],wxPoint(2, 200));
ultimaHora=new wxStaticText(panelTren, wxID_ANY, linea1[3],wxPoint(2, 225));
ultimahora=new wxStaticText(panelTren, wxID_ANY, linea1[4],wxPoint(2, 250));
primero=new wxButton(panelTren, ID_TREN1, GO, wxPoint(300, 150));
segundo=new wxButton(panelTren, ID_TREN2, GO, wxPoint(300, 175));
tercero=new wxButton(panelTren, ID_TREN3, GO, wxPoint(300, 200));
cuarto=new wxButton(panelTren, ID_TREN4, GO, wxPoint(300, 225));
quinto=new wxButton(panelTren, ID_TREN5, GO, wxPoint(300, 250));

Connect(ID_TREN1, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(TrenDialog::OnPrimero));
Connect(ID_TREN2, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(TrenDialog::OnSegundo));
Connect(ID_TREN3, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(TrenDialog::OnTercero));
Connect(ID_TREN4, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(TrenDialog::OnCuarto));
Connect(ID_TREN5, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(TrenDialog::OnQuinto));

	
}
void TrenDialog::OnQuit(wxCommandEvent& event)
{
	this->Destroy();
}
void TrenDialog::OnPrimero(wxCommandEvent& event)
{
	ProcesarViajes(ciudadOrden[0],precioOrden[0]);
}
void TrenDialog::OnSegundo(wxCommandEvent& event)
{
	ProcesarViajes(ciudadOrden[1],precioOrden[1]);
}
void TrenDialog::OnTercero(wxCommandEvent& event)
{
	ProcesarViajes(ciudadOrden[2],precioOrden[2]);
}
void TrenDialog::OnCuarto(wxCommandEvent& event)
{
	ProcesarViajes(ciudadOrden[3],precioOrden[3]);
}
void TrenDialog::OnQuinto(wxCommandEvent& event)
{
	ProcesarViajes(ciudadOrden[4],precioOrden[4]);
}
void TrenDialog::ProcesarViajes(wxString destino, int precio)
{
	int realdestino;
	if(destino=="Gorguez"){city=11;money=money-precio;}
	if(destino=="Centralia"){city=12;money=money-precio;}
	if(destino=="Obscura"){wxMessageBox("No está disponible el tren");}
	if(destino=="Wellville"){wxMessageBox("No está disponible el tren");}
	if(destino=="Orlan\t"){wxMessageBox("No está disponible el tren");}
	
	this->Destroy();
	
}
#endif
