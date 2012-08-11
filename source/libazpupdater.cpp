#include "azpupdater.h"
#include <wx/wx.h>
#include <wx/progdlg.h>

bool AZPUpdater::CheckUpdates()
{
	float newversion;
	float actualversion=1.0;
	wxProgressDialog checkupdates("Azpazeta Updater","Comprobando actualizaciones",5);
	//Web de actualizacion https://launchpadlibrarian.net/113495996/AZPUpdater.txt
	system("mkdir -p /opt/extras.ubuntu.com/azpazeta/updates");
	checkupdates.Update(1);
	system("wget https://launchpadlibrarian.net/113495996/AZPUpdater.txt -o /opt/extras.ubuntu.com/azpazeta/updates/AZPUpdater.txt");
	checkupdates.Update(2);
	FILE* fileupdate;
	fileupdate=fopen("/opt/extras.ubuntu.com/azpazeta/updates/AZPUpdater.txt","r");
	if(fileupdate){
	checkupdates.Update(3);
	fscanf(fileupdate,"AZPUpdaterFile:%f",&newversion);
	fclose(fileupdate);
	checkupdates.Update(4);
	if(newversion<=actualversion){checkupdates.Update(5);wxMessageBox("No hay actualizaciones","AZPUpdater",wxOK|wxICON_INFORMATION);}
	if(newversion>actualversion){checkupdates.Update(5);wxMessageBox("Hay actualizaciones disponibles","AZPUpdater",wxOK|wxICON_INFORMATION);}
	
	
	}else{wxMessageBox("Error while AZPUpdater check updates","AZPUpdater",wxOK|wxICON_ERROR);}
}
