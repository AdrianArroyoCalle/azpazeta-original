//LIBMODLOADER --- Usa este esquema para crear tus mods
#include <wx/wx.h>
#include "libmodloader.h"

bool ModLoader::CheckMod()
{
	wxMessageBox("Ningun mod instalado","Mod Loader for Azpazeta",wxOK|wxICON_INFORMATION);
	return true;

}
