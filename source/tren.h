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

#endif
