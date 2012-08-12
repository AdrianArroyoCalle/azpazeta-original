//Golf.cpp

#include "Librerias.h"

extern int sobornos, blacklist, money, droga, rich, electro;
static int preciorich[5]={100,200,300,400,500};

Golf::Golf() : wxDialog(NULL, wxID_ANY, wxT("Valladolid Golf"), wxPoint(-1,-1), wxSize(400,400))
{

	wxPanel* golfpanel=new wxPanel(this);
	wxStaticText* golftext=new wxStaticText(golfpanel, wxID_ANY, GOLF_101);
	wxButton* venderlujo=new wxButton(golfpanel, ID_VENDERLUJO, "Vender lujo", wxPoint(50,200));
	wxButton* comprarlujo=new wxButton(golfpanel, ID_COMPRARLUJO, "Comprar lujo", wxPoint(250, 200));
	wxButton* venderdroga=new wxButton(golfpanel, ID_VENDERDROGA, "Vender otras cosas", wxPoint(50,300));
	wxButton* valladolid=new wxButton(golfpanel, ID_VALLADOLID, "Hablar con ancianos",wxPoint(250,300));
	Connect(ID_VENDERLUJO, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Golf::VenderLujo));
	Connect(ID_COMPRARLUJO, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Golf::ComprarLujo));
	Connect(ID_VENDERDROGA, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Golf::VenderDroga));
	Connect(ID_VALLADOLID, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Golf::Valladolid));



}

void Golf::VenderLujo(wxCommandEvent& event)
{
	srand(time(NULL));
	int randomgolf=rand()%5;
	if(rich>0){wxMessageBox(wxString::Format("Has vendido un producto de lujo por %d",preciorich[randomgolf])); rich--; money+=preciorich[randomgolf];}else{wxMessageBox("No tienes para vender");}
}

void Golf::ComprarLujo(wxCommandEvent& event)
{
	srand(time(NULL));
	int randomgolf=rand()%5;
	if(money>preciorich[randomgolf]){wxMessageBox(wxString::Format("Has comprado un producto de lujo por %d",preciorich[randomgolf]));rich++; money-=preciorich[randomgolf];}else{wxMessageBox("No tienes dinero");}
}

void Golf::VenderDroga(wxCommandEvent& event)
{
	srand(time(NULL));
	int randomgolf=rand()%5+1;
	if(droga>0){
	switch(randomgolf)
	{
	case 1: wxMessageBox("Estaba la policia, pierdes la droga"); if(blacklist>0){wxMessageBox("Pagas una gran multa (2000 $)");money-=2000; droga=0;}else{droga=0;blacklist++;}break;
	case 2: wxMessageBox("Estaba la policia, pierdes la droga y pagas una multa");droga=0;money-=1000;break;
	case 3: if(sobornos>0){wxMessageBox("El policia del soborno no te multa, pero no puedes vender");sobornos--;}else{wxMessageBox(wxString::Format("Vendes la droga a 1000 $"));money+=1000;droga--;}break;
	default: wxMessageBox("Vendes la droga a 1000 $"); money+=1000; droga--;
	}}else{wxMessageBox("No tienes nada que vender");}
}
void Golf::Valladolid(wxCommandEvent& event)
{
	wxMessageBox("\"Descubre Valladolid\" te dicen los ancianos, la tierra del creador del juego");
	wxShell("firefox http://en.wikipedia.org/wiki/Valladolid");

}
