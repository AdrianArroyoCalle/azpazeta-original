///////////////////////////////////////////////////////
///AZPAZETA 1.0
//////////////////////////////////////////////////////////
//Azpazeta es el juego de comerciantes medievales de Divel Games
/////////////////////////////////////////////////////////////
//Versión en Español
///////////////////////////////////////////////////////////
//Versión adaptada especialmente para Ubuntu
/////////////////////////////////////////////////////////////
//Menú de juego
/////////////////////////////////////////////////////////////
#ifndef INICIO_HPP_
#define INICIO_HPP_
#include "wx/wxprec.h"
#include <wx/event.h>
#include <wx/sound.h>
#include <wx/aboutdlg.h>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <iostream>
#include "Icono64.xpm"
#include "tren.h"
#include "VarGlobal.h"
#include "Idiomas.h"
#include <wx/cmdline.h>
#include "save.h"
#include "Librerias.h"
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
#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

#endif
