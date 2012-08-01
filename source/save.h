//Sistema de guardado y cargado de archivos
#ifndef SAVE_H_
#define SAVE_H_
/*#include "wx/wxprec.h"
#include <wx/event.h>
#include <wx/sound.h>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <iostream>
#include "VarGlobal.h"
#include <time.h>
#include <wx/progdlg.h>
#include "Idiomas.h"*/
#include "inicio.hpp"
using namespace std;
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
class SaveDialog : public wxDialog
{
public:
	SaveDialog();
	void OnQuit(wxCommandEvent& event);
	void OnBotonGuardarStd(wxCommandEvent& event);
        void OnBotonCargarStd(wxCommandEvent& event);
	void OnBotonGuardarCopy(wxCommandEvent& event);
        void OnBotonCargarCopy(wxCommandEvent& event);
        void Guardar(wxString archivo);
        void Cargar(wxString archivo);
	wxStaticText* instrucciones;
	wxStaticText* salida;
	wxStaticText* precio;
	wxStaticText* ciudad1;
	wxStaticText* salida1;
	wxStaticText* precio1;
	wxStaticText* ultimaHora;
	wxStaticText* ultimahora;
	wxButton* guardar_std;
	wxButton* guardar_copy;
	wxButton* cargar_copy;
	wxButton* cargar_std;

};

enum{
	ID_SAVE1 = 1029,
	ID_SAVE2 = 1030,
	ID_SAVE3 = 1031,
	ID_SAVE4 = 1032,
	ID_SAVE5 = 1033
};


#endif

