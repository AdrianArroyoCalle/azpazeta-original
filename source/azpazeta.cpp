#include "Librerias.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;
	SetAppName(wxT("Visual Divel Start"));
	SetVendorName(wxT("Adrian Arroyo Calle para Divel"));

    // create the main application window
    MyFrame *frame = new MyFrame("Visual Divel Start");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);
	
	

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}
