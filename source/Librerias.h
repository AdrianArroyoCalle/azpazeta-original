#ifndef LIBRERIAS_H
#define LIBRERIAS_H
#include "wx/wxprec.h"
#include <wx/event.h>
#include <wx/sound.h>
#include <wx/aboutdlg.h>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <iostream>
#include "tren.h"
#include "VarGlobal.h"
#include "Idiomas.h"
#include <wx/cmdline.h>
#include "save.h"
#include <libnotify/notify.h>
#include <wx/taskbar.h>
#include "chr_taskbar.h"
#include <string>
#include <algorithm>
#include <stdexcept>
#include "dkey.h"
#include <wx/filedlg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------


// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
    //virtual void OnRun(); //Hacer comprobaciones
    virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);


 
};

static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{
     { wxCMD_LINE_SWITCH, "h", "help", "displays help on the command line parameters"},
        {wxCMD_LINE_PARAM, NULL, NULL,"save file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},
 
     { wxCMD_LINE_NONE }
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnNet(wxCommandEvent& event);
	void OnInstrucciones(wxCommandEvent& event);
	void OnActualizar(wxCommandEvent& event);
	void OnJugar(wxCommandEvent& event);
	void OnBorrar(wxCommandEvent& event);
	void OnTaskKiller(wxCommandEvent& event);
	void OnCorreos(wxCommandEvent& event);
	void OnUpdater(wxCommandEvent& event);
	void OnTecla(wxKeyEvent& event);
	void Stage1();
	void Stage2();
	void Stage3();
	void Stage4();
	void Stage5();
	void Stage6();
	void Stage7();
	void Stage11();
	void Load();
	wxImage Play;
	wxButton* jugar;
	wxButton* actualizar;
	wxButton* instrucciones;
	wxStaticBitmap* Portada;
	wxStaticBitmap* Adrix;
	wxStaticBitmap* Bocadillo;
	wxStaticText* cap1mis1;
	wxPanel* panel;
private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
private:  
	//Añadir botones

};
// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,
	ID_ACTUALIZAR = 1001,
	ID_NET = 1002,
	ID_INSTRUCCIONES = 1003,
	ID_WRITE = 1004,
	ID_TASKKILLER = 1005,
	ID_OPCIONES = 1006,
	ID_JUGAR = 1007,
	ID_INSTALADOS = 1008,
	ID_ARCHIVOS = 1009,
	ID_CERRAR = 1010,
	ID_APAGAR = 1011,
	ID_USER = 1012,
	ID_WINUNIX = 1013,
	ID_UPDATER = 1014,
	ID_PLAY = 1015,
	ID_EXECUTE = 1016,
	ID_COMPRIMIR = 1017,
	ID_DIBUJO = 1018,
	ID_TEXT = 1019,
	ID_TECLA = 1020,
	ID_VIAJAR = 1021,
	ID_OFERTAS = 1022,
	ID_REGALOS = 1023,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};









#endif
