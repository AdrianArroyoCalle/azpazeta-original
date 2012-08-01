#include "save.h"
//#include "inicio.hpp"
#include "Librerias.h"

extern int money, city, aux, mision;
extern char name; 

SaveDialog::SaveDialog()
       : wxDialog(NULL, wxID_ANY, wxT("Casa"), wxPoint(-1,-1), wxSize(400,400))
{
        wxPanel* panelSave=new wxPanel(this);
        guardar_std=new wxButton(panelSave,ID_SAVE1,wxT("Guardar"),wxPoint(100,50));
        cargar_std=new wxButton(panelSave,ID_SAVE1,wxT("Cargar"),wxPoint(100,100));
        guardar_copy=new wxButton(panelSave,ID_SAVE1,wxT("Guardar copia"),wxPoint(100,150));
        guardar_std=new wxButton(panelSave,ID_SAVE1,wxT("Cargar copia"),wxPoint(100,200));
        
}


void SaveDialog::OnBotonGuardarStd(wxCommandEvent& event)
{

}
void SaveDialog::OnBotonCargarStd(wxCommandEvent& event)
{

}
void SaveDialog::OnBotonGuardarCopy(wxCommandEvent& event)
{

}
void SaveDialog::OnBotonCargarCopy(wxCommandEvent& event)
{

}
void SaveDialog::Guardar(wxString archivo)
{

}
void SaveDialog::Cargar(wxString archivo)
{
        wxPrintf("Cargando %s ...",archivo);
	wxProgressDialog cargando("Azpazeta","Cargando partida...",3);
	FILE* partida_cargar;
	partida_cargar=fopen(archivo.c_str(),"r");
	if(partida_cargar)
	{
		cargando.Update(1);
		fscanf(partida_cargar,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:NOMBRE=%s:AUX=%d\n",&money, &city, &mision, &name,&aux);
		cargando.Update(2);
		fclose(partida_cargar);
		cargando.Update(3);
		/*switch(city){
		case 1: myframe->Stage1(); break;
		case 2: myframe->Stage2(); break;
		case 3: myframe->Stage3(); break;
		default: wxMessageBox(ERROR_101,"Azpazeta",wxICON_ERROR|wxOK); cargando.Destroy(); break;
		}*/
		/*wxMessageBox("Todavia no violado 5");
		cargando.Update(4);
		wxBitmap bocadillo("/usr/share/Azpazeta/media/Bocadillo.png",wxBITMAP_TYPE_PNG);
		cargando.Update(5);
		myframe->Bocadillo=new wxStaticBitmap(myframe->panel, ID_DIBUJO, bocadillo, wxPoint(600,450));
		cargando.Update(6);
		myframe->cap1mis1=new wxStaticText(myframe->panel, ID_DIBUJO, wxT(CAP1MIS1TEX1), wxPoint(625, 470));
		cargando.Update(7);
		cargando.Update(8);*/
		
	}else{wxMessageBox(ERROR_101,"Azpazeta",wxICON_ERROR|wxOK); cargando.Destroy();}
	
}
