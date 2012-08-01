//
//Implementación de Divel Key en Azpazeta
//
#include "dkey.h"
#include "Librerias.h"

extern int aux;

DivelKey::DivelKey()
       : wxDialog(NULL, wxID_ANY, wxT("Divel Key"), wxPoint(-1,-1), wxSize(400,400))
{
	wxPanel* dkey=new wxPanel(this);
	if(aux==0){
	wxStaticText* key_text1=new wxStaticText(dkey, wxID_ANY,DKEY_101);
	wxButton* ObtKey=new wxButton(dkey, ID_KEY1,DKEY_102, wxPoint(100,200));}else{
	wxStaticText* key_text2=new wxStaticText(dkey, wxID_ANY, DKEY_103);
	wxButton* visualizar_cheats=new wxButton(dkey, ID_KEY2, DKEY_104, wxPoint(100,200));
	}
	Connect(ID_KEY1,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(DivelKey::OnObtener));
	Connect(ID_KEY2, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DivelKey::VerTrucos));

}
void DivelKey::OnObtener(wxCommandEvent& event)
{
	wxShell("firefox http://1.divelapps.appspot.com");
	wxString mail=wxGetTextFromUser("Introduce tu correo","Divel Key","");
	wxString hex_key=wxGetTextFromUser("Introduce la clave obtenida","Divel Key","");
	//Codigo de pruebas
	/*std::string input=hex_key.c_str();
	static const char* const lut = "0123456789ABCDEF";
    	size_t len = input.length();
    	if (len & 1) throw std::invalid_argument("odd length");

    	std::string output;
    	output.reserve(len / 2);
    	for (size_t i = 0; i < len; i += 2)
    	{
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    	}*/
	/*char newmail=mail.mb_str();
	char name[2048]=newmail;
	char buffer[2048]="";
	char *pbuffer = buffer;
	int len = strlen( name );
	for( int i = 0; i < len ;i++ )
	{
		itoa (name[i],pbuffer,16);
		pbuffer +=2;
	};*/
	/*int a;
	std::string newmail="adrian.arroyocalle@gmail.com";
	newmail>>std::hex>>a;
        std::cout<<std::hex<<a;*/
	/*char* szBuf = "34932";
	char* szStop;
	strtol( szBuf, &szStop, 16 );
	wxMessageBox(wxString::Format("%s",szStop));*/
	const char *newhex_key=hex_key.mb_str();
	const char *texto =mail.mb_str();
	int i;
	char buffer[8192];
	char hexmail[8192]="";
	for (i=0; texto[i]; i++){
	sprintf(buffer,"%02x", texto[i]);
	strcat(hexmail,buffer);}
	if(strcmp(hexmail,newhex_key)==0)
	{
		wxMessageBox("Clave correcta\nYa puedes acceder a Divel House","Divel Key",wxICON_INFORMATION|wxOK);
		aux=1;
		this->Destroy();
			
	}else{
		wxMessageBox("Clave incorrecta, vuelve a intentarlo","Divel Key",wxICON_ERROR|wxOK);
		this->Destroy();
	}

	
	//wxPrintf("%s",buffer);
	//wxMessageBox(strtoul(s.c_str(), NULL, 16));
}

void DivelKey::VerTrucos(wxCommandEvent& event)
{
	wxMessageBox("-Guardar en cualquier momento (ACTIVO)\n-Dinero infinito (DESACTIVADO)\n-Teletransporte (DESACTIVADO)\n","Divel House",wxICON_INFORMATION|wxOK);
}
