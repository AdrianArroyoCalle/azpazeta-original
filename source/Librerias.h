#ifndef LIBRERIAS_H
#define LIBRERIAS_H
#include "wx/wxprec.h"
#include <wx/event.h>
#include <wx/sound.h>
#include <wx/aboutdlg.h>
#include <fstream>
#include <iostream>
//#include "libmodloader.h"
#include <assert.h>
//#include "gortren.h"
#include <iostream>
#include "tren.h"
#include "VarGlobal.h"
#include "Idiomas.h"
#include <wx/cmdline.h>
#include "save.h"
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
#include "police.h"
#include <time.h>
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <wx/filesys.h>
#include <wx/splash.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <memory>
#include "hiper.h"
#include <wx/mediactrl.h>
//#include "azpupdater.h"
#include "golf.h"
#include "dialogbox.h"
#include <wx/glcanvas.h>
#include <wx/gdicmn.h>
#include <math.h>
#include "mercado.h"
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
	void OnJugar();
	void OnBorrar(wxCommandEvent& event);
	void OnTaskKiller(wxCommandEvent& event);
	void OnCorreos(wxCommandEvent& event);
	void OnUpdater(wxCommandEvent& event);
	void OnTecla(wxKeyEvent& event);
	void AZPCliente(wxCommandEvent& event);
	void Stage1();
	void Stage2();
	void Stage3();
	void Stage4();
	void Stage5();
	void Stage6();
	void Stage7();
	void Stage11();
	void Stage12();
	void Load();
	void CheckearMods(wxCommandEvent& event);
	void ComprobarMulti(wxTimerEvent& event);
	void NewGame(wxCommandEvent& event);
	int Lee_Socket (int fd, char *Datos, int Longitud);
	int Escribe_Socket (int fd, char *Datos, int Longitud);
	void Paint();
	void RenderDown(wxDC& dc);
	void RenderUp(wxDC& dc);
	void RenderRight(wxDC& dc);
	void RenderLeft(wxDC& dc);
	wxImage Play;
	wxButton* jugar;
	wxButton* actualizar;
	wxButton* instrucciones;
	wxStaticBitmap* Portada;
	wxStaticBitmap* Adrix;
	wxStaticBitmap* Bocadillo;
	wxStaticText* cap1mis1;
	wxPanel* panel;
	wxMenuBar* menuBar;
	wxMenu *fileMenu;
        wxMenu *helpMenu;
	wxPanel* dcpanel;
	
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
	ID_AZPCLIENTE = 1024,
	TIMER_ID,
	ID_NEWGAME,
	ID_MODS,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};









#endif
