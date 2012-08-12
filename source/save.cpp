#include "save.h"
//#include "inicio.hpp"
#include "Librerias.h"

extern int money, city, aux, mision, sobornos, blacklist, droga, socio, electro, food, textil,rich,prima;
extern char name; 

SaveDialog::SaveDialog()
       : wxDialog(NULL, wxID_ANY, wxT("Casa"), wxPoint(-1,-1), wxSize(400,400))
{
	wxInitAllImageHandlers();
        wxPanel* panelSave=new wxPanel(this);
	wxBitmap estacion("/opt/extras.ubuntu.com/azpazeta/media/save.png",wxBITMAP_TYPE_PNG);
	wxStaticBitmap* fondo_estacion=new wxStaticBitmap(panelSave, wxID_ANY, estacion, wxPoint(-1,-1));
        guardar_std=new wxButton(panelSave,ID_SAVE1,wxT("Guardar"),wxPoint(100,50));
        cargar_std=new wxButton(panelSave,ID_SAVE2,wxT("Cargar"),wxPoint(100,100));
        guardar_copy=new wxButton(panelSave,ID_SAVE3,wxT("Guardar copia"),wxPoint(100,150));
        guardar_std=new wxButton(panelSave,ID_SAVE4,wxT("Cargar copia"),wxPoint(100,200));

	Connect(ID_SAVE1, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SaveDialog::OnBotonGuardarStd));
	Connect(ID_SAVE2, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SaveDialog::OnBotonCargarStd));
	Connect(ID_SAVE3, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SaveDialog::OnBotonGuardarCopy));
	Connect(ID_SAVE4, wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SaveDialog::OnBotonCargarCopy));


}


void SaveDialog::OnBotonGuardarStd(wxCommandEvent& event)
{
	//FILE* partida_guardar;
	//partida_guardar=fopen("/usr/share/Azpazeta/save/save.azp","w");
	/*fprintf(partida_guardar,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:\n",money, city, mision, aux, droga, sobornos, blacklist);
	fclose(partida_guardar);*/
	//Nuevo sistema de partidas
	char *home;
	home=getenv("HOME");
	wxString pathgeneral=wxString::Format("mkdir -p %s/.azpazeta",home);
	system(pathgeneral.c_str());
	wxString pathguardar=wxString::Format("%s/.azpazeta/save.azp",home);

	wxFFileOutputStream out(pathguardar);
	wxZipOutputStream zip(out);
	wxTextOutputStream txt(zip);
	wxString sep(wxFileName::GetPathSeparator());
	char datosparaguardar[2048];
	zip.PutNextEntry(wxT("AZPGeneral.txt"));
	sprintf(datosparaguardar,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:SOCIO=%d:ELECTRO=%d:FOOD=%d:TEXTIL=%d:RICH=%d:PRIMA=%d:\n",money, city, mision, aux, droga, sobornos, blacklist, socio, electro, food, textil,rich,prima);
	txt << datosparaguardar;
	zip.PutNextEntry(wxT("SERVER-DATA")+ sep+ wxT("lastservers.txt"));
	zip.PutNextEntry(wxT("META-DATA") + sep + wxT("INFO.txt"));
	txt << wxT("Hi, this is the user information\n");


	
	this->Destroy();
}
void SaveDialog::OnBotonCargarStd(wxCommandEvent& event)
{	
	//FILE* partida_cargar;
	//partida_cargar=fopen("/usr/share/Azpazeta/save/save.azp","r");
	/*fscanf(partida_cargar,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:\n",&money, &city, &mision, &aux, &droga, &sobornos, &blacklist);
	fclose(partida_cargar);*/
	//Nuevo sistema de partidas
	char *home;
	home=getenv("HOME");
	wxString pathgeneral=wxString::Format("mkdir -p %s/.azpazeta",home);
	system(pathgeneral.c_str());
	wxString pathguardar=wxString::Format("%s/.azpazeta/save.azp",home);
	char mybuffer[2048];
	 std::auto_ptr<wxZipEntry> entry;
	wxFFileInputStream in(pathguardar);
	wxZipInputStream zip(in);
	int archivo=1;

	while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)  {                 
      		while (!zip.Eof()) {
         		zip.Read(mybuffer, 2048);
			if(archivo==1){
				sscanf(mybuffer,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:SOCIO=%d:ELECTRO=%d:FOOD=%d:TEXTIL=%d:RICH=%d:PRIMA=%d:\n",&money, &city, &mision, &aux, &droga, &sobornos, &blacklist, &socio, &electro, &food, &textil,&rich,&prima);//Los datos importantes de juego están aquí

			}
			archivo++;
         		if (zip.LastRead() > 0) {
           // do something with read data here, buffer contains zip.LastRead() valid bytes
         }
     	 }
	}
	




	
	this->Destroy();
}
void SaveDialog::OnBotonGuardarCopy(wxCommandEvent& event)
{
	wxFileDialog* openfile = new wxFileDialog(this,wxT("Guardar partida"),wxT(""),wxT(""),wxT("Azpazeta Save Files|*.azp"),wxFD_SAVE);

        openfile->ShowModal();
    // the user changed idea...
        
        // save the current contents in the file;
        // this can be done with e.g. wxWidgets output streams:
	/*FILE* partida_guardar;
	partida_guardar=fopen(openfile->GetPath().c_str(),"w");
	fprintf(partida_guardar,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:\n",money, city, mision, aux, droga, sobornos, blacklist);
	fclose(partida_guardar);*/
	//wxFileSystem::AddHandler(new wxZipFSHandler);
	wxFFileOutputStream out(openfile->GetPath()+".azp");
	wxZipOutputStream zip(out);
	wxTextOutputStream txt(zip);
	wxString sep(wxFileName::GetPathSeparator());
	char datosparaguardar[2048];
	zip.PutNextEntry(wxT("AZPGeneral.txt"));
	sprintf(datosparaguardar,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:SOCIO=%d:ELECTRO=%d:FOOD=%d:TEXTIL=%d:RICH=%d:PRIMA=%d:\n",money, city, mision, aux, droga, sobornos, blacklist, socio, electro, food, textil,rich,prima);
	txt << datosparaguardar;
	zip.PutNextEntry(wxT("SERVER-DATA")+ sep+ wxT("lastservers.txt"));
	zip.PutNextEntry(wxT("META-DATA") + sep + wxT("INFO.txt"));
	txt << wxT("Hi, this is the user information\n");
	this->Destroy();
}
void SaveDialog::OnBotonCargarCopy(wxCommandEvent& event)
{
	wxFileDialog* openfile = new wxFileDialog(this,wxT("Cargar partida"),wxT(""),wxT(""),wxT("Azpazeta Save Files|*.azp"),wxFD_OPEN);
        openfile->ShowModal();
	/*FILE* partida_cargar;
	partida_cargar=fopen(openfile->GetPath().c_str(),"r");
	fscanf(partida_cargar,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:\n",&money, &city, &mision, &aux, &droga, &sobornos, &blacklist);
	fclose(partida_cargar);
	this->Destroy();*/
	char mybuffer[2048];
	 std::auto_ptr<wxZipEntry> entry;
	wxFFileInputStream in(openfile->GetPath());
	wxZipInputStream zip(in);
	int archivo=1;

	while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)  {                 
      		while (!zip.Eof()) {
         		zip.Read(mybuffer, 2048);
			if(archivo==1){
				sscanf(mybuffer,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:SOCIO=%d:ELECTRO=%d:FOOD=%d:TEXTIL=%d:RICH=%d:PRIMA=%d:\n",&money, &city, &mision, &aux, &droga, &sobornos, &blacklist, &socio, &electro, &food, &textil,&rich,&prima);//Los datos importantes de juego están aquí

			}
			archivo++;
         		if (zip.LastRead() > 0) {
           // do something with read data here, buffer contains zip.LastRead() valid bytes
         }
     	 }
	}
	
	/*while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
	{
    // access meta-data
    	wxString zipname = wxT("AZPGeneral.txt");
	//if (entry->IsDir())
         //       {
                    //int perm = entry->GetMode();
                    //wxFileName::Mkdir(name, perm, wxPATH_MKDIR_FULL);
                //}
                //else // it is a file
                //{
                    zip.OpenEntry(*entry.get());
                    if (!zip.CanRead())
                    {
                        wxLogError("Can not read zip entry");
                        break;
                    }
                    wxFileOutputStream file(zipname);
                    if (!file)
                    {
                         wxLogError("Can not create file ");
                         
                    }
			wxPrintf("Good");
                    zip.Read(file);
			wxMessageBox(file);
			wxPrintf("Good");
    // read 'zip' to access the entry's data
	//}
}zip.CloseEntry();
*/
}
void SaveDialog::Guardar(wxString archivo)
{

}
void SaveDialog::Cargar(wxString archivo)
{
        wxPrintf("Cargando %s ...",archivo);
	wxProgressDialog cargando("Azpazeta","Cargando partida...",3);
	//FILE* partida_cargar;
	//partida_cargar=fopen(archivo.c_str(),"r");
	cargando.Update(1);
		//fscanf(partida_cargar,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:\n",&money, &city, &mision, &aux, &droga, &sobornos, &blacklist);
		cargando.Update(2);
		//fclose(partida_cargar);
		cargando.Update(3);
		
	char mybuffer[2048];
	std::auto_ptr<wxZipEntry> entry;
	wxFFileInputStream in(archivo);
	wxZipInputStream zip(in);
	int leer=1;

	while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)  {                 
      		while (!zip.Eof()) {
         		zip.Read(mybuffer, 2048);
			if(leer==1){
				sscanf(mybuffer,"Azpazeta_Save_File_v.1.0:MONEY=%d:CITY=%d:MISION=%d:AUX=%d:DROGA=%d:SOBORNO=%d:BLACKLIST=%d:SOCIO=%d:ELECTRO=%d:FOOD=%d:TEXTIL=%d:RICH=%d:PRIMA=%d:\n",&money, &city, &mision, &aux, &droga, &sobornos, &blacklist, &socio, &electro, &food, &textil,&rich,&prima);//Los datos importantes de juego están aquí

			}
			leer++;
         		if (zip.LastRead() > 0) {
           // do something with read data here, buffer contains zip.LastRead() valid bytes
         }
     	 }
	}
	
		

	
}
