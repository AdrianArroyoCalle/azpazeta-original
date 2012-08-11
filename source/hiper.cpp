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


	Connect(ID_HIPER1,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Comprar));
	Connect(ID_HIPER2,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Tour));
	Connect(ID_HIPER3,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Trabajar));
	Connect(ID_HIPER4,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Hiper::Suscribirse));
}
/*Hiper::ComprarDlg() : wxDialog(NULL, wxID_ANY, wxT("Buy and buy and ..."), wxPoint(-1,-1), wxSize(400,400))
{
	wxString compraOrden[6];
	int PRECIOOrden[6];
	int CompraOrden;
	int precioORDEN;
	int viajarint;
	int anterior;
	int bucle;
	static wxString viajarcity[6]={"Camiseta","Smartphone Android","...","Pato a la naranja","Chandal",""};
	static int viajarprecio[6]={300,40,1000,500,120};
	wxString bText[6];
	wxProgressDialog comprar("Cadena Inc.","Buscando las mejores ofertas",6);
	//Modo aleatorio
	while(bucle<6){
	srand(time(NULL));
	viajarint=rand()%6+1;
	if(anterior!=viajarint){
	bText[bucle]=wxString::Format("%s %d",viajarcity[viajarintprecio],viajarprecio[viajarint]);
	compraOrden[CompraOrden]=viajarcity[viajarintprecio];
	PRECIOOrden[precioORDEN]=viajarprecio[viajarint];
	CompraOrden++;
	precioORDEN++;
	bucle++;
	randomizar.Update(bucle);
	viajarintprecio++;
	anterior=viajarint;
	wxPrintf("Todavia no violado");
	}else{wxPrintf("Es igual a 5");}
	}






	
	wxPanel* comprarpanel=new wxPanel(this);
	wxStaticText* info_comprar=new wxStaticText(comprarpanel, wxID_ANY, COMPRAR_101);
	wxButton* b1=new wxButton(comprarpanel,ID_COMPRAR1, bText[0], wxPoint(50, 100)); 
	wxButton* b2=new wxButton(comprarpanel,ID_COMPRAR2, bText[1], wxPoint(250, 100)); 
	wxButton* b3=new wxButton(comprarpanel,ID_COMPRAR3, bText[2], wxPoint(50, 150)); 
	wxButton* b4=new wxButton(comprarpanel,ID_COMPRAR4, bText[3], wxPoint(250, 150)); 
	wxButton* b5=new wxButton(comprarpanel,ID_COMPRAR5, bText[4], wxPoint(50, 200)); 
	wxButton* b6=new wxButton(comprarpanel,ID_COMPRAR6, bText[5], wxPoint(2500, 200)); 

}*/
void Hiper::Comprar(wxCommandEvent& event)
{

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
