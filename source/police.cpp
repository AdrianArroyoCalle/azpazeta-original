//Police.cpp
#include "Librerias.h"
#include "police.h"

extern int sobornos, blacklist, money, droga;

Police::Police()
       : wxDialog(NULL, wxID_ANY, wxT("Police Station"), wxPoint(-1,-1), wxSize(400,400))
{
	//wxInitAllImageHandlers();
        wxPanel* panelPolice=new wxPanel(this);
	wxStaticText* info_police=new wxStaticText(panelPolice,wxID_ANY,POLICE_101);
	wxButton* reporte=new wxButton(panelPolice, ID_POLICE1,POLICE_102,wxPoint(100,200));
	wxButton* soborno=new wxButton(panelPolice, ID_POLICE2,POLICE_103,wxPoint(100,300));
        //guardar_std=new wxButton(panelSave,ID_SAVE4,wxT("Cargar copia"),wxPoint(100,200));

	Connect(ID_POLICE1, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Police::Reportar));


}

void Police::Reportar(wxCommandEvent& event)
{
	if(droga>0){
	srand(time(NULL));
	int suerte=rand()%10+1;
	switch(suerte){
		case 1: wxMessageBox("La burocracia te aplasta\nTe quedas con ello y sin recibir nada","Policia");break;
		case 2: wxMessageBox("Te toca un poli cabreado\nTe pregunta de donde lo has sacado\ny te acusa de complice\nPierdes el objeto, debes pagar 100 $ de fianza y estas en la lista negra","Policia"); money=money-100; droga--; blacklist++;break;
		case 3: wxMessageBox("El poli es un primo tuyo\nTe da mas dinero de lo normal (400 $) y te borra de la lista negra","Policia"); money+=400; droga--; blacklist=0;break;
		case 4:{ time_t tSac = time(NULL);       // instante actual
   			struct tm* tmP = localtime(&tSac);
			int hora=tmP->tm_hour;
			int minutos=tmP->tm_min;
			int segundos=tmP->tm_sec;
			wxMessageBox(wxString::Format("Son las %d:%d:%d, como quieres que esten despiertos unos policias que se hechan la siesta y se comen los donuts",hora,minutos,segundos),"Policia");}
			break;
		default: wxMessageBox("Recibes la recompensa tan merecida por reportar el contenido ilegal (200 $)");money+=200; droga--;break;





	}}else{wxMessageBox("Deja de perder el tiempo");}
}
