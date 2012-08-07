//Police.cpp
#include "Librerias.h"
#include "police.h"

Police::Police()
       : wxDialog(NULL, wxID_ANY, wxT("Police Station"), wxPoint(-1,-1), wxSize(400,400))
{
	//wxInitAllImageHandlers();
        wxPanel* panelPolice=new wxPanel(this);
	wxStaticText* info_police=new wxStaticText(panelPolice,wxID_ANY,POLICE_101);
	wxButton* reporte=new wxButton(panelPolice, ID_POLICE1,POLICE_102,wxPoint(100,200));
	wxButton* soborno=new wxButton(panelPolice, ID_POLICE2,POLICE_103,wxPoint(100,300));
        //guardar_std=new wxButton(panelSave,ID_SAVE4,wxT("Cargar copia"),wxPoint(100,200));

	//Connect(ID_SAVE1, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SaveDialog::OnBotonGuardarStd));


}
