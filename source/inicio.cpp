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
//
//
static char *Id="$Id$";
static char *Author="$Author$";
int AZPServer;
extern int money, level, city, mision, aux, droga, blacklist, sobornos, socio, electro, food, textil,rich, prima;
typedef struct AZPServerData{int level;int money;int city;char* name;int mision;int aux; int droga;int blacklist;int sobornos;int socio;int electro;int food;int textil;int rich;} AZPServerData;
typedef struct MyEstado{bool bien;int moneyotro;} MyEstado;
#include "inicio.hpp"



#define ARRIBA 1
#define ABAJO 2
#define DERECHA 3
#define IZQUIERDA 4
#define GOLEFT adrx-=5;RenderLeft(dc);
#define GORIGHT adrx+=5;RenderRight(dc);
#define GOUP adry-=5;RenderUp(dc);
#define GODOWN adry+=5;RenderDown(dc);
// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------
// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_MENU(ID_ACTUALIZAR, MyFrame::OnActualizar)
	EVT_MENU(ID_NET, MyFrame::OnNet)
	EVT_MENU(ID_AZPCLIENTE, MyFrame::AZPCliente)
	EVT_MENU(ID_INSTRUCCIONES, MyFrame::OnInstrucciones)
	EVT_MENU(ID_NEWGAME, MyFrame::NewGame)
	EVT_MENU(ID_MODS, MyFrame::CheckearMods)
	EVT_KEY_DOWN(MyFrame::OnTecla)	
	EVT_TIMER(TIMER_ID, MyFrame::ComprobarMulti)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------
extern int x, y, adrx, adry, mision, city,aux;
extern char name;
extern wxString newname;
int fachada, menu;
// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	wxBitmap splashbitmap;
  	if (splashbitmap.LoadFile("/opt/extras.ubuntu.com/azpazeta/media/splash.png", wxBITMAP_TYPE_PNG))
  	{
      	wxSplashScreen* splash = new wxSplashScreen(splashbitmap,
          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
          6000, NULL, -1, wxDefaultPosition, wxSize(400,400),
          wxSIMPLE_BORDER|wxSTAY_ON_TOP);
  	}
  	wxYield();
	//ChrTaskBarIcon* icon = new ChrTaskBarIcon(); 
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;
	SetAppName(wxT("Azpazeta"));
	SetVendorName(wxT("Adrian Arroyo Calle para Divel"));
        if(wxApp::argc>=2){
	fachada=1;
        wxString archivo=wxApp::argv[1].mb_str();
        //int* newsavedlg=new SaveDialog::Cargar(wxString archivo);
        SaveDialog* newsavedlg=new SaveDialog();
        newsavedlg->Cargar(archivo);
	newsavedlg->Destroy();
	MyFrame *frame = new MyFrame("Azpazeta");
	frame->Show(true);
	frame->Load();
	frame->Paint();
	//if(city==4){MyFrame::Stage4();}
	
        
        }else{	MyFrame *frame = new MyFrame("Azpazeta");
	frame->Show(true);
	frame->OnJugar();
	frame->Paint();}
        
        
    // create the main application window

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    
	
	

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(Icono64));
	/*FILE* PointMash;
	PointMash=fopen("/usr/share/Azpazeta/Res.cfg","r");
	if(PointMash){
	fscanf(PointMash,"RES=%d:%d",&x,&y);
	SetSize(x,y);
	adrx=x/2;
	adry=y/2;
	fclose(PointMash);
	}else{wxMessageBox(wxT("No se ha encontrado archivo de resolución PointMash en: /usr/share/Azpazeta/Res.cfg"),wxT("Error 201"),wxICON_ERROR|wxOK);SetSize(800,600); x=800; y=600;}*/
	SetSize(800, 600); x=800; y=600;
	dcpanel=new wxPanel(this,-1,-1,800,600);
	wxInitAllImageHandlers();
	/*wxImage portada("/usr/share/Azpazeta/media/Portada.png", wxBITMAP_TYPE_PNG);
	wxImage portadaSize;
	portadaSize=portada.Scale(x/2,y/2);
	portadaSize.SaveFile("/usr/share/Azpazeta/media/newres/Portada.png",wxBITMAP_TYPE_PNG);
	wxBitmap portadaBMP("/usr/share/Azpazeta/media/newres/Portada.png", wxBITMAP_TYPE_PNG);*/
	/*wxBitmap portadaBMP("/opt/extras.ubuntu.com/azpazeta/media/inicio.png", wxBITMAP_TYPE_PNG);
	Portada = new wxStaticBitmap(panel, ID_DIBUJO, portadaBMP, wxPoint(-1,-1));
	if(fachada!=1){
	actualizar=new wxButton(panel, ID_ACTUALIZAR, wxT("Actualizar juego"), wxPoint(100,500));
	jugar=new wxButton(panel, ID_JUGAR, wxT("Cargar partida"), wxPoint(250,500));
	instrucciones=new wxButton(panel, ID_INSTRUCCIONES, wxT("Instrucciones"), wxPoint(400,500));}

	Connect(ID_JUGAR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnJugar));
	Connect(ID_USER, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnInstrucciones));
	Connect(ID_ACTUALIZAR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnActualizar));*/
	//dcpanel->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MyFrame::OnTecla),NULL, this);
	//dcpanel->Connect(wxEVT_CHAR, wxKeyEventHandler(MyFrame::OnTecla),NULL, this);

#if wxUSE_MENUS
    // create a menu bar
    fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    helpMenu = new wxMenu;
	helpMenu->Append(ID_INSTRUCCIONES, "&Instrucciones", "Instrucciones sobre Azpazeta");
    helpMenu->Append(Minimal_About, "A&cerca\tF1", "Acerca de Azpazeta");
	fileMenu->Append(ID_AZPCLIENTE, "&Conectar con server", "Jugar multijugador");
	fileMenu->Append(ID_NEWGAME, "&Nuevo juego","Nueva partida");
	fileMenu->Append(ID_MODS, "C&heckear mods","Comprueba los mods instalados");
	fileMenu->Append(ID_ACTUALIZAR, "A&ctualizar", "Actualizar Azpazeta");
	fileMenu->Append(ID_NET, "&Mas productos de Divel", "Mas productos de Divel");	
    fileMenu->Append(Minimal_Quit, "&Salir\tAlt-X", "Salir sin guardar");

    // now append the freshly created menu to the menu bar...
    menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&Archivo");
    menuBar->Append(helpMenu, "A&yuda");

    // ... and attach this menu bar to the frame
    //SetMenuBar(menuBar); //Hacer funcionar con tecla ALT-Estilo Windows 7
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Azpazeta 1.0 Sin comprobar actualizaciones");
	//Pantalla Completa, implementar en futuras versiones//ShowFullScreen(true, wxFULLSCREEN_ALL);
#endif // wxUSE_STATUSBAR

}


// event handlers



void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    /*wxMessageBox(wxString::Format
                 (
                    "Bienvenido a Azpazeta!\n"
                    "\n"
                    "El juego de estrategia comercial\n"
                    "funcionando sobre %s.\n\n"
					"Para mas juegos y productos visite:\n sites.google.com/site/divelmedia\n"
			"Este juego ha sido disenado por Adrian Arroyo Calle",
                    wxGetOsDescription()
                 ),
                 "Acerca de Azpazeta",
                 wxOK | wxICON_INFORMATION,
                 this);*/
        wxAboutDialogInfo aboutInfo;
        aboutInfo.SetName("Azpazeta");
        aboutInfo.SetVersion("1.0");
        aboutInfo.SetDescription(_("The game of strategy and economics by Divel"));
        aboutInfo.SetCopyright("(C) 2012");
        aboutInfo.SetWebSite("http://sites.google.com/site/divelmedia");
        aboutInfo.AddDeveloper("Adrián Arroyo Calle");
        aboutInfo.AddTranslator("Adrián Arroyo Calle and Google Translate");
        aboutInfo.AddArtist("Adrián Arroyo Calle and GIMP");

        wxAboutBox(aboutInfo);
}

void MyFrame::OnNet(wxCommandEvent& WXUNUSED(event))
{
	//DEBUG MODE
	wxShell("firefox http://sites.google.com/site/divelstore");
}
void MyFrame::OnActualizar(wxCommandEvent& WXUNUSED(event))
{
	wxShell("update-manager -d");//Solo Ubuntu
	/*
	AZPUpdater* azpupdater;
	azpupdater=new AZPUpdater();
	azpupdater->CheckUpdates();*/
}
void MyFrame::OnInstrucciones(wxCommandEvent& WXUNUSED(event))
{
		wxShell("firefox http://sites.google.com/site/divelmedia");	//meter un pdf
}
void MyFrame::OnJugar()
{
SetMenuBar(menuBar);
	srand(time(NULL));
	int tip=rand()%5+1;
	switch(tip){
case 1: wxMessageBox(/*"Do you know that you can press ALT and access to the menus?"*/"Sabes que puedes acceder a los menus presionando ALT?","Today's tip", wxICON_INFORMATION|wxOK);break;
	case 2: wxMessageBox(/*"Do you know that you can access to a Azpazeta Server and play with one friend?"*/"Sabes que puedes acceder a un server de Azpazeta y jugar con un amigo?","Today's tip", wxICON_INFORMATION|wxOK);break;
	case 3: wxMessageBox(/*"Do you know that you can execute AZPServer and you have a Azpazeta Server?"*/"Sabes que si ejecutas AZPServer.exe, tienes un server de Azpazeta?","Today's tip", wxICON_INFORMATION|wxOK);break;
	case 4: wxMessageBox(/*"Do you know that you can play also in Windows"*/"Sabes que puedes jugar tambien en Linux?","Today's tip", wxICON_INFORMATION|wxOK);break;
	case 5: wxMessageBox(/*"Do you know that you can colaborate in launchpad.net/azpazeta"*/"Sabes que puedes colaborar en launchpad.net/azpazeta","Today's tip", wxICON_INFORMATION|wxOK);break;
	}
	//wxSound("/usr/share/Azpazeta/audio/Hip-hop.wav").Play(wxSOUND_ASYNC|wxSOUND_LOOP);
	/*FILE* partida;
	wxString archivo=wxT("/usr/share/Azpazeta/save/save.azp");
	partida=fopen("/usr/share/Azpazeta/save/save.azp","r");
	if(partida){
	fclose(partida);*/
	char *home;
	home=getenv("HOME");
	wxString pathgeneral=wxString::Format("mkdir -p %s/.azpazeta",home);
	system(pathgeneral.c_str());
	wxString pathguardar=wxString::Format("%s/.azpazeta/save.azp",home);
	FILE* partida;
	partida=fopen(pathguardar.c_str(),"r");
	if(partida){
	fclose(partida);
	SaveDialog* extrasavedlg=new SaveDialog();
        extrasavedlg->Cargar(pathguardar);
        extrasavedlg->Destroy();
	Load();
	}else if(city!=0){	
	}else{
	wxMessageBox(wxT("Empezando nueva partida"), wxT("Azpazeta"),wxICON_INFORMATION|wxOK);
	newname=wxGetTextFromUser(wxT("Introduce tu nombre para la partida"),wxT("Azpazeta"),wxT(""));
	city=1;
	MyFrame::Stage1();
	}
}

void MyFrame::OnTecla(wxKeyEvent& event)
{
 int ascii = event.GetKeyCode();
	/*wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixup("/opt/extras.ubuntu.com/azpazeta/media/AdrixUp.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixleft("/opt/extras.ubuntu.com/azpazeta/media/AdrixLeft.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixright("/opt/extras.ubuntu.com/azpazeta/media/AdrixRight.png", wxBITMAP_TYPE_PNG);*/
wxClientDC dc(dcpanel);
switch(city){
	case 1:{
	switch(ascii)
	{	
	//El primer edificio está a 26 pix-------333pix y 27 piy--------------330 piy
		
		case WXK_LEFT: //Left
		if(adry< 390 && adrx<330){}else{
		adrx-=5;
		RenderLeft(dc);
		if(adrx<=1 && mision>=6){Stage2();}
		}
		break;
		case WXK_UP: //UP
		if(adry< 390 && adrx<330){}else{
		adry-=5;
		RenderUp(dc);}
		break;
		case WXK_RIGHT: //Right
		//if(){}else{
		adrx+=5;
		RenderRight(dc);
		break;
		case WXK_DOWN: //Down
		//if(/*adry< 330 && adrx<334*/){}else{
		adry+=5;
		RenderDown(dc);
		break;
		case WXK_RETURN:
		if(adry<=400 && adrx<180)
		{if(adrx>=140){
		switch(mision){
		case 0:{
		RenderUp(dc);
		dc.DrawText("Quien eres?\nNo te conozco.\nEres el nuevo?\nPresiona ENTER", wxPoint(625, 470));
		mision++;
		break;}
		case 1:
		RenderUp(dc);
		dc.DrawText("Bueno, me presento\nSoy Alfredo\nEl alcalde de Azpazeta\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 2:{
		RenderUp(dc);
		wxString completo=wxT("Como te llamas?\n")+newname+wxT("\nBonito nombre\nPresiona ENTER");
		dc.DrawText(completo,wxPoint(625,470));
		mision++;
		break;}
		case 3:
		RenderUp(dc);
		dc.DrawText("Te has perdido?\nSupongo que querras casa\nPero no va ser gratis\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 4:
		RenderUp(dc);
		dc.DrawText("Necesitaras un trabajo\nNo se de que\nEso lo dejo a tu eleccion\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 5:
		RenderUp(dc);
		dc.DrawText("[Objetivo anadido:\nEncontrar trabajo]\nPista: El pueblo esta a la izquierda",wxPoint(625,470));
		mision++;
		break;
		}}}
		break;
		case WXK_ESCAPE:
		if(aux==1){SaveDialog* savedlg;savedlg=new SaveDialog();savedlg->ShowModal();savedlg->Destroy();Adrix->Destroy();Load();}
		break;
		case WXK_TAB:
		wxMessageBox(wxT("TAB"));
		break;
		case WXK_SHIFT:{
		wxString cheat=wxGetTextFromUser(wxT("Introduce el Cheat Code"), wxT("Debug Mode"),wxT(""));
		if(cheat==wxT("2")){Stage1();Stage2();}}
		break;
		case WXK_ALT:
		SetMenuBar(menuBar);
		break;
	}break;}
	case 2:
	switch(ascii)
	{	
	//El primer edificio está a 26 pix-------333pix y 27 piy--------------330 piy
		case WXK_LEFT:
		if(adry< 470){}else{
		adrx-=5;
		RenderLeft(dc);
		if(adrx<=1 && mision==15){Stage3();}
		}
		break;
		case WXK_UP:
		if(adry< 470){}else{
		adry-=5;
		RenderUp(dc);}
		break;
		case WXK_RIGHT:
		//if(){}else{
		adrx+=5;
		RenderRight(dc);//}
		break;
		case WXK_DOWN:
		//if(/*adry< 330 && adrx<334*/){}else{
		adry+=5;
		RenderDown(dc);
		//}
		break;
		case WXK_RETURN:
		if(adry<=480)
		{if(adrx>=108 && adrx<=170){
		switch(mision){
		case 6:
		RenderUp(dc);
		dc.DrawText("\"El INEM\nSeguro que aqui habra trabajo\nVoy a ver\"\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 7:
		RenderUp(dc);
		dc.DrawText("Siguiente...\n-Venia a por trabajo\n-Tenemos en la panificadora\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 8:
		RenderUp(dc);
		dc.DrawText("-Creo que me valdra\n-Siguiente...\n\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 9:
		RenderUp(dc);
		dc.DrawText("[Objetivo anadido:\nIr a la panificadora]",wxPoint(625,470));
		mision++;
		break;
		default:
		RenderUp(dc);
		dc.DrawText("Otra vez tu\nAnda vete para fuera\n",wxPoint(625,470));
		}}
		if(adrx>=474 && adrx<=542){
		switch(mision){
		case 10:
		RenderUp(dc);
		dc.DrawText("(Ruidos)\nPUES SI, IMPORTA\nAnda, vete a...\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 11:
		RenderUp(dc);
		dc.DrawText("-Y tu quien eres?\n-Vengo por el puesto\n-Ah, sí.\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 12:
		RenderUp(dc);
		dc.DrawText("Trabajaras de comerciante\nambulante.\nIras por los pueblos\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 13:
		RenderUp(dc);
		dc.DrawText("Vamos a ver como lo haces\nVe a la plaza de Gorguez\nLleva estos panes\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		case 14:
		RenderUp(dc);
		dc.DrawText("[Objetivo anadido:\nVender los panes en Gorguez]\nPista: La estacion de tren\ntiene trenes locales",wxPoint(625,470));
		mision++;
		break; 
		default:
		RenderUp(dc);
		dc.DrawText("(Esta cerrado)",wxPoint(625,470));
		break;
		}}}

		break;
		case WXK_ESCAPE:
		if(aux==1){SaveDialog* savedlg;savedlg=new SaveDialog();savedlg->ShowModal();savedlg->Destroy();Load();}
		break;
		case WXK_TAB:
		SetMenuBar(menuBar);
		break;
		case WXK_SHIFT:{
		wxString cheat=wxGetTextFromUser(wxT("Introduce el Cheat Code"), wxT("Debug Mode"),wxT(""));
		if(cheat==wxT("2")){Stage1();Stage2();}}
		break;
		case WXK_ALT:
		SetMenuBar(menuBar);
		break;
		}break;
	case 3:
	switch(ascii)
	{	
	//El primer edificio está a 26 pix-------333pix y 27 piy--------------330 piy
		case WXK_LEFT:
		if((adry<156 && adrx<307) || ((adry<383 && adry>200) && adrx<307) || (adry<383 && adrx>503)){if(adrx==504){adrx--; RenderLeft(dc); }}else{
		if(adrx<=1){Stage4();}else{
		GOLEFT}
		//if(adrx==1 && mision>=6){Stage2();}
		}
		break;
		case WXK_UP:
		if((adry<156 && adrx<307) || ((adry<383 && adry>200) && adrx<307) || (adry<383 && adrx>503)){printf("Valor X=%d Y=%d",adrx, adry);if(adry==199){adry--; RenderUp(dc);}}else{
		if(adry<=5){Stage7();}
GOUP}
		break;
		case WXK_RIGHT:
		if((adry<156 && adrx<307) || ((adry<383 && adry>200) && adrx<307) || (adry<383 && adrx>503)){if(adrx==306){adrx++; RenderRight(dc); }}else{
		if(adrx>=746){Stage2();}
GORIGHT}
		break;
		case WXK_DOWN:
		if((adry<156 && adrx<307) || ((adry<383 && adry>200) && adrx<307) || (adry<383 && adrx>503)){if(adry==382 || adry==155){adry++; RenderDown(dc);}}else{
GODOWN}
		break;
		case WXK_RETURN:
                //Trenes
		if(adry<=427 && (adrx>=633 && adrx<=670)){
		switch(mision){
		case 15:
		RenderUp(dc);
		dc.DrawText("-Supongo que es la estacion\nVamos a ver como es\nGorguez\nPresiona ENTER",wxPoint(625,470));
		mision++;
		break;
		default:
		wxPrintf("Cargando...");
		TrenDialog* trendlg=new TrenDialog();
		wxPrintf("Mostrando...");
		trendlg->ShowModal();
		trendlg->Destroy();
		Load();
		break;
		}}
                //Piso franco
                if(adry<=196 && (adrx>=156 && adrx<=182)){
		SaveDialog* savedlg;
                savedlg=new SaveDialog();
                savedlg->ShowModal();
                savedlg->Destroy();
		Load();
                }
		break;
		case WXK_ESCAPE:
		if(aux==1){SaveDialog* savedlg;savedlg=new SaveDialog();savedlg->ShowModal();savedlg->Destroy();Load();}
		break;
		case WXK_TAB:
		wxMessageBox(wxT("TAB"));
		break;
		case WXK_SHIFT:
		break;
		case WXK_ALT:
		SetMenuBar(menuBar);
		break;
		}break;
	case 4:
	switch(ascii)
	{	
	//366-222
		case WXK_LEFT:
			if(adrx<=283){}else{
			GOLEFT}
		break;
		case WXK_UP:
			if(adry<=204 && adrx>=474){}else{
			if(adry<=10){Stage5();}
GOUP}
		break;
		case WXK_RIGHT:
			if((adry<=204 && adrx>=475) || (adry>=366 && adrx>=474)){}else{
			if(adrx>=746){Stage3();}
	GORIGHT}
		break;
		case WXK_DOWN:
			if(adry>=366 && adrx>=474){}else{
			GODOWN}
		break;
		case WXK_RETURN:
		if((adrx>=616 || adrx<=688) && adry>=360){
		DivelKey* keydlg=new DivelKey();
		keydlg->ShowModal();
		keydlg->Destroy();}
		break;
		case WXK_ESCAPE:
		if(aux==1){SaveDialog* savedlg;savedlg=new SaveDialog();savedlg->ShowModal();savedlg->Destroy();Load();}
		break;
		case WXK_TAB:
		
		break;
		case WXK_SHIFT:
		
		break;
		case WXK_ALT:
		SetMenuBar(menuBar);
		break;
		}break;
	case 5:
	switch(ascii)
	{	
	//366-222
		case WXK_LEFT:
		if(adrx<=362 && (adry<=226 || adry>=399)){}else{
		GOLEFT

		}
		break;
		case WXK_UP:
		if(adrx<=362 && adry<=226){}else{
		if(adry<=5){Stage6();}
		GOUP
		}		//226-362
		break;
		case WXK_RIGHT:
		if(adrx>=545){}else{
		GORIGHT
		}
		break;
		case WXK_DOWN:
		if(adrx<=362 && adry>=399){}else{
		if(adry>=540){Stage4();}
		GODOWN
		}//399-362
		break;
		case WXK_RETURN:
		if((adrx>=154 && adrx<=222) && adry<=230){
		switch(mision){
		default: Police* poldlg=new Police();
		poldlg->ShowModal();
		poldlg->Destroy();
			}		
			}
		break;
		case WXK_ESCAPE:
		if(aux==1){SaveDialog* savedlg;savedlg=new SaveDialog();savedlg->ShowModal();savedlg->Destroy();Load();}
		break;
		case WXK_TAB:
		
		break;
		case WXK_SHIFT:
		
		break;
		case WXK_ALT:
		SetMenuBar(menuBar);
		break;
		}break;
	case 6:
	switch(ascii)
	{	
	//366-222
		case WXK_LEFT:
		GOLEFT
		break;
		case WXK_UP:
		if(adry<=300){}else{
		GOUP
		}
		break;
		case WXK_RIGHT:
		GORIGHT
		break;
		case WXK_DOWN:
		if(adry>=540){ Stage5();}
		GODOWN
		break;
		case WXK_RETURN:
		//Entrar en Hipermercado
		if(adry<=320 && (adrx>=407 && adrx<=470)){Hiper* hiperdlg; hiperdlg=new Hiper(); hiperdlg->ShowModal();hiperdlg->Destroy();}
		break;
		case WXK_ESCAPE:
		if(aux==1){SaveDialog* savedlg;savedlg=new SaveDialog();savedlg->ShowModal();savedlg->Destroy();Load();}
		break;
		case WXK_TAB:
		
		break;
		case WXK_SHIFT:
		
		break;
		case WXK_ALT:
		SetMenuBar(menuBar);
		break;
		}break;
	case 7:
	switch(ascii)
	{	
	//366-222
		case WXK_LEFT:
		GOLEFT
		break;
		case WXK_UP:
		if(adry<=300){}else{
		GOUP
		}
		break;
		case WXK_RIGHT:
		GORIGHT
		break;
		case WXK_DOWN:
		if(adry>=540){Stage3();}
		GODOWN
		break;
		case WXK_RETURN:
		if(adry<=302 && (adrx>=382 && adrx<=440)){Golf* golfdlg; golfdlg=new Golf();golfdlg->ShowModal();golfdlg->Destroy();}
		break;
		case WXK_ESCAPE:
		if(aux==1){SaveDialog* savedlg;savedlg=new SaveDialog();savedlg->ShowModal();savedlg->Destroy();Load();}
		break;
		case WXK_TAB:
		
		break;
		case WXK_SHIFT:
		
		break;
		case WXK_ALT:
		SetMenuBar(menuBar);
		break;
		}break;
	case 11:
	switch(ascii)
	{	
	//366-222
		case WXK_LEFT:
		if((adrx<=405 && adry>=405) || (adrx<=150 && adry<=130)){}else{
		GOLEFT
		}
		break;
		case WXK_UP:
		if((adrx<=150 && adry<=130) || (adrx>=555 && adry<=340)){}else{
		GOUP
		}
		break;
		case WXK_RIGHT:
		if(adrx>=555 && (adry<=340 || adry>=505)){}else{
		GORIGHT
		}
		break;
		case WXK_DOWN:
		if((adrx<=405 && adry>=405) || (adrx>=555 && adry>=505)){}else{
		GODOWN
		}
		break;
		case WXK_RETURN:
		//Bread&Pan
		if(adrx<=102 && adry<=152){
		DialogBox* dlgbox;
		dlgbox=new DialogBox();
		dlgbox->ShowModal();
		dlgbox->Destroy();
		}
		//Mercado
		if((adrx>=665 && adrx<=732) && adry<=358){
		Mercado* merdlg;
		merdlg=new Mercado();
		merdlg->ShowModal();
		merdlg->Destroy();
		}
		//Estacion de Tren
		if((adrx>=665 && adrx<=732) && adry>=498){
		int iraazpazeta=wxMessageBox("Deseas ir a Azpazeta por 50 $?","Train Station",wxYES_NO|wxICON_QUESTION);
		if(iraazpazeta==wxYES){
		money-=50;
		city=3;
		Load();
		}
		}
		break;
		case WXK_ESCAPE:
		if(aux==1){SaveDialog* savedlg;savedlg=new SaveDialog();savedlg->ShowModal();savedlg->Destroy();Load();}
		break;
		case WXK_TAB:
		
		break;
		case WXK_SHIFT:
		
		break;
		case WXK_ALT:
		SetMenuBar(menuBar);
		break;
		}break;

}
}

void MyFrame::Stage1()
{	wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap cap1dib1("/opt/extras.ubuntu.com/azpazeta/media/1x1.png", wxBITMAP_TYPE_PNG);
	wxClientDC maindc(dcpanel);
	maindc.DrawBitmap(cap1dib1,wxPoint(-1,-1),true);
	maindc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true);
	city=1;
	wxPrintf("Bienvenido a Azpazeta!\nAutor: Adrian Arroyo Calle\nAno: 2012\nJuego certficado por: Divel Games\n");
}

void MyFrame::Stage2()
{
	wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap inem("/opt/extras.ubuntu.com/azpazeta/media/INEM.png", wxBITMAP_TYPE_PNG);
	wxClientDC maindc(dcpanel);
	maindc.DrawBitmap(inem,wxPoint(-1,-1),true);
	maindc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true);
	city=2;
}
void MyFrame::Stage3()
{
	wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap centro1("/opt/extras.ubuntu.com/azpazeta/media/Centro1.png", wxBITMAP_TYPE_PNG);
	wxClientDC maindc(dcpanel);
	maindc.DrawBitmap(centro1,wxPoint(-1,-1),true);
	maindc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true);
	city=3;
}
void MyFrame::Stage4()
{
	wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap centro2("/opt/extras.ubuntu.com/azpazeta/media/Centro2.png",wxBITMAP_TYPE_PNG);
	wxClientDC maindc(dcpanel);
	maindc.DrawBitmap(centro2,wxPoint(-1,-1),true);
	maindc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true);
	city=4;
}
void MyFrame::Stage5()
{
	wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap centro3("/opt/extras.ubuntu.com/azpazeta/media/Centro3.png", wxBITMAP_TYPE_PNG);
	wxClientDC maindc(dcpanel);
	maindc.DrawBitmap(centro3,wxPoint(-1,-1),true);
	maindc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true);
	city=5;
}
void MyFrame::Stage6()
{
		wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap hiper("/opt/extras.ubuntu.com/azpazeta/media/Hiper.png", wxBITMAP_TYPE_PNG);
	wxClientDC maindc(dcpanel);
	maindc.DrawBitmap(hiper,wxPoint(-1,-1),true);
	maindc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true);
	city=6;
}
void MyFrame::Stage7()
{
	wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap golf("/opt/extras.ubuntu.com/azpazeta/media/Golf.png", wxBITMAP_TYPE_PNG);
	wxClientDC maindc(dcpanel);
	maindc.DrawBitmap(golf,wxPoint(-1,-1),true);
	maindc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true);
	city=7;
}
void MyFrame::Stage11()
{
	wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap gorguez("/opt/extras.ubuntu.com/azpazeta/media/Gorguez.png", wxBITMAP_TYPE_PNG);
	wxClientDC maindc(dcpanel);
	maindc.DrawBitmap(gorguez,wxPoint(-1,-1),true);
	maindc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true);
	city=11;
}
void MyFrame::Stage12()
{
	int granja=wxMessageBox("Quieres comprar materia prima a 50 $?","Granjas Nacionales",wxYES_NO|wxICON_QUESTION);
	if(granja==wxYES){
	money-=50;
	prima++;
	city=3;
	Load();
	}else{
	city=3;
	Load();
	}
}
void MyFrame::Load()
{
	/*actualizar->Destroy();
	jugar->Destroy();
	instrucciones->Destroy();*/
	NotifyNotification *n;
    	notify_init("Azpazeta");
    	n = notify_notification_new ("Azpazeta", "Se ha cargado correctamente la partida", NULL);
    	notify_notification_set_timeout(n, 3000);
	if (!notify_notification_show (n, NULL)) {
        wxPrintf("Error al enviar notificación.\n");        
    	}
	switch(city){
	case 1: Stage1(); break;
	case 2: Stage2(); break;
	case 3: Stage3(); break;
	case 4: Stage4(); break;
	case 5: Stage5(); break;
	case 6: Stage6(); break;
	case 7: Stage7(); break;
	case 11: Stage11(); break;
	case 12:Stage12(); break;
	default: Stage1(); break;

	}

}
void MyApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (wxT("-"));
}
 
bool MyApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    //silent_mode = parser.Found(wxT("s"));    
    // to get at your unnamed parameters use
    wxArrayString files;
        for (int i = 0; i < parser.GetParamCount(); i++)
    {
            files.Add(parser.GetParam(i));
    }
 
    // and other command line parameters   
 
    // then do what you need with them.
 
    return true;
}

void MyFrame::AZPCliente(wxCommandEvent& event)
{
	wxMessageBox("Modo experimental\nSe recomienda no usar hasta otras actualizaciones","Divel Network",wxICON_WARNING|wxOK);
	int siono=wxMessageBox("Quieres utilizar IPv6?\nSi no se usara IPv4","Divel Network",wxICON_QUESTION|wxYES_NO);

	if(siono==wxNO){
	
	char Cadena[1024];
	char ip[1024];
	char nombreCliente1[1024];
	char nombreCliente2[1024];
	wxString wxip=wxGetTextFromUser("Introduce la IP del server de Azpazeta","Divel Network","127.0.0.1");	
	strncpy(ip, (const char*)wxip.mb_str(wxConvUTF8), 1023);
	struct sockaddr_in Direccion;
	struct servent *Puerto;
	struct hostent *Host;
	Direccion.sin_addr.s_addr=inet_addr(ip);
	Direccion.sin_family = AF_INET;
	Direccion.sin_port = 6996;
	AZPServer = socket (AF_INET, SOCK_STREAM, 0);
	connect (AZPServer, (struct sockaddr *)&Direccion, sizeof (Direccion));
	Lee_Socket(AZPServer, Cadena,1024);
	wxMessageBox(wxString::Format("%s",Cadena),"Server informa",wxICON_INFORMATION|wxOK);
	wxString onlinename=wxGetTextFromUser("Introduce tu nombre online","Divel Network","");
	strncpy(nombreCliente1, (const char*)onlinename.mb_str(wxConvUTF8), 1023);
	Escribe_Socket(AZPServer, nombreCliente1, 1024);
	Lee_Socket(AZPServer, nombreCliente2, 1024);
	wxMessageBox(wxString::Format("El otro jugador es: %s",nombreCliente2),"Divel Network");
}else{
	//IPv6
	char Cadena[1024];
	char ip[1024];
	char nombreCliente1[1024];
	char nombreCliente2[1024];
	wxString wxip=wxGetTextFromUser("Introduce la IPv6 del server de Azpazeta","Divel Network","::1");	
	strncpy(ip, (const char*)wxip.mb_str(wxConvUTF8), 1023);
	struct sockaddr_in6 Direccion;
	struct servent *Puerto;
	struct hostent *Host;
	//Direccion.sin6_len = sizeof(Direccion);
	//unsigned char ipv6[16]="::1";
	inet_pton(PF_INET6, ip,&(Direccion.sin6_addr));
	//Direccion.sin6_addr.s6_addr=inet_pton();	
	//Direccion.sin6_addr.s6_addr=inet_addr6(ip);
	Direccion.sin6_family = AF_INET6;
	Direccion.sin6_port = 6996;
	AZPServer = socket (AF_INET6, SOCK_STREAM, 0);
	connect (AZPServer, (struct sockaddr *)&Direccion, sizeof (Direccion));
	Lee_Socket(AZPServer, Cadena,1024);
	wxMessageBox(wxString::Format("%s",Cadena),"Server informa",wxICON_INFORMATION|wxOK);
	wxString onlinename=wxGetTextFromUser("Introduce tu nombre online","Divel Network","");
	strncpy(nombreCliente1, (const char*)onlinename.mb_str(wxConvUTF8), 1023);
	Escribe_Socket(AZPServer, nombreCliente1, 1024);
	Lee_Socket(AZPServer, nombreCliente2, 1024);
	wxMessageBox(wxString::Format("El otro jugador es: %s",nombreCliente2),"Divel Network");
}
	AZPServerData datos;
	MyEstado myestado;
	datos.money=money;
	datos.level=level;
	datos.city=city;
	datos.name="A";
	datos.droga=droga;
	datos.blacklist=blacklist;
	datos.socio=socio;
	datos.electro=electro;
	datos.food=food;
	datos.textil=textil;
	datos.sobornos=sobornos;
	datos.mision=mision;
	datos.rich=rich;
	write(AZPServer, &datos, sizeof(datos));
	read(AZPServer, &myestado, sizeof(myestado));
	if(myestado.bien==true){wxMessageBox(wxString::Format("Bien, el otro tienen menos, concretamente: %d", myestado.moneyotro));}
	if(myestado.bien==false){wxMessageBox(wxString::Format("Mal, el otro tiene mas, concretamente: %d", myestado.moneyotro));}
	//close(AZPServer);
	wxTimer* timer;
	timer=new wxTimer(this, TIMER_ID);
	timer->Start(60000, false);
	wxMessageBox(wxT("Empezando nueva partida"), wxT("Azpazeta"),wxICON_INFORMATION|wxOK);
	newname=wxGetTextFromUser(wxT("Introduce tu nombre para la partida"),wxT("Azpazeta"),wxT(""));
	wxBitmap bocadillo("/opt/extras.ubuntu.com/azpazeta/media/Bocadillo.png",wxBITMAP_TYPE_PNG);
	Bocadillo=new wxStaticBitmap(panel, ID_DIBUJO, bocadillo, wxPoint(600,450));
	cap1mis1=new wxStaticText(panel, ID_DIBUJO, wxT(CAP1MIS1TEX1), wxPoint(625, 470));
	actualizar=new wxButton(panel, wxID_ANY, "...");
	jugar=new wxButton(panel, wxID_ANY, "...");
	instrucciones=new wxButton(panel, wxID_ANY, "...");
	city=1;
	Adrix->Destroy();
	money=2000;
	mision=0;
	level=0;
	MyFrame::Stage1();

}
int MyFrame::Lee_Socket (int fd, char *Datos, int Longitud)
{
	int Leido = 0;
	int Aux = 0;

	/*
	* Comprobacion de que los parametros de entrada son correctos
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Mientras no hayamos leido todos los datos solicitados
	*/
	while (Leido < Longitud)
	{
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0)
		{
			/* 
			* Si hemos conseguido leer datos, incrementamos la variable
			* que contiene los datos leidos hasta el momento
			*/
			Leido = Leido + Aux;
		}
		else
		{
			/*
			* Si read devuelve 0, es que se ha cerrado el socket. Devolvemos
			* los caracteres leidos hasta ese momento
			*/
			if (Aux == 0) 
				return Leido;
			if (Aux == -1)
			{
				/*
				* En caso de error, la variable errno nos indica el tipo
				* de error. 
				* El error EINTR se produce si ha habido alguna
				* interrupcion del sistema antes de leer ningun dato. No
				* es un error realmente.
				* El error EGAIN significa que el socket no esta disponible
				* de momento, que lo intentemos dentro de un rato.
				* Ambos errores se tratan con una espera de 100 microsegundos
				* y se vuelve a intentar.
				* El resto de los posibles errores provocan que salgamos de 
				* la funcion con error.
				*/
				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}

	/*
	* Se devuelve el total de los caracteres leidos
	*/
	return Leido;
}

/*
* Escribe dato en el socket cliente. Devuelve numero de bytes escritos,
* o -1 si hay error.
*/
int MyFrame::Escribe_Socket (int fd, char *Datos, int Longitud)
{
	int Escrito = 0;
	int Aux = 0;

	/*
	* Comprobacion de los parametros de entrada
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Bucle hasta que hayamos escrito todos los caracteres que nos han
	* indicado.
	*/
	while (Escrito < Longitud)
	{
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
		if (Aux > 0)
		{
			/*
			* Si hemos conseguido escribir caracteres, se actualiza la
			* variable Escrito
			*/
			Escrito = Escrito + Aux;
		}
		else
		{
			/*
			* Si se ha cerrado el socket, devolvemos el numero de caracteres
			* leidos.
			* Si ha habido error, devolvemos -1
			*/
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}

	/*
	* Devolvemos el total de caracteres leidos
	*/
	return Escrito;
}
void MyFrame::ComprobarMulti(wxTimerEvent& event)
{
AZPServerData datos;
	MyEstado myestado;
	datos.money=money;
	datos.level=level;
	datos.city=city;
	datos.name="A";
	datos.droga=droga;
	datos.blacklist=blacklist;
	datos.socio=socio;
	datos.electro=electro;
	datos.food=food;
	datos.textil=textil;
	datos.sobornos=sobornos;
	datos.mision=mision;
	write(AZPServer, &datos, sizeof(datos));
	read(AZPServer, &myestado, sizeof(myestado));
	if(myestado.bien==true){wxMessageBox(wxString::Format("Bien, el otro tienen menos, concretamente: %d", myestado.moneyotro));}
	if(myestado.bien==false){wxMessageBox(wxString::Format("Mal, el otro tiene mas, concretamente: %d", myestado.moneyotro));}
}

void MyFrame::NewGame(wxCommandEvent& event)
{
	wxMessageBox(wxT("Empezando nueva partida"), wxT("Azpazeta"),wxICON_INFORMATION|wxOK);
	newname=wxGetTextFromUser(wxT("Introduce tu nombre para la partida"),wxT("Azpazeta"),wxT(""));

	city=1;
	money=2000;
	mision=0;
	level=0;
	MyFrame::Stage1();
}
void MyFrame::CheckearMods(wxCommandEvent& event)
{
	/*ModLoader* modsystem;
	modsystem=new ModLoader();
	modsystem->CheckMod();*/
	wxMessageBox("No hay mods instalados");
}
void MyFrame::Paint()
{
	wxClientDC dc(dcpanel);
    RenderDown(dc);
}
void MyFrame::RenderDown(wxDC& dc)
{
	wxBitmap adrixdown("/opt/extras.ubuntu.com/azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	dc.DrawText("No se ha renderizado bien",wxPoint(-1,-1));
	//Dibujar fondo
	switch(city){
	case 0:{dc.DrawBitmap(adrixdown, wxPoint(adrx,adry),true);}
	case 1:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 2:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/INEM.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 3:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 4:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro2.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 5:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro3.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 6:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Hiper.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 7:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Golf.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 8:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 9:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}

	case 10:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 11:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Gorguez.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	}
	
}
void MyFrame::RenderUp(wxDC& dc)
{
#define adrixdown adrixup
	wxBitmap adrixup("/opt/extras.ubuntu.com/azpazeta/media/AdrixUp.png", wxBITMAP_TYPE_PNG);
	dc.DrawText("No se ha renderizado bien",wxPoint(-1,-1));
	//Dibujar fondo
	switch(city){
	case 0:{dc.DrawBitmap(adrixdown, wxPoint(adrx,adry),true);}
	case 1:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 2:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/INEM.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 3:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 4:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro2.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 5:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro3.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 6:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Hiper.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 7:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Golf.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 8:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 9:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}

	case 10:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 11:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Gorguez.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	}
	
}
void MyFrame::RenderLeft(wxDC& dc)
{
	wxBitmap adrixleft("/opt/extras.ubuntu.com/azpazeta/media/AdrixLeft.png", wxBITMAP_TYPE_PNG);
	dc.DrawText("No se ha renderizado bien",wxPoint(-1,-1));
#define adrixdown adrixleft
	//Dibujar fondo
	switch(city){
	case 0:{dc.DrawBitmap(adrixdown, wxPoint(adrx,adry),true);}
	case 1:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 2:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/INEM.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 3:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 4:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro2.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 5:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro3.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 6:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Hiper.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 7:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Golf.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 8:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 9:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}

	case 10:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 11:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Gorguez.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	}
	
}
void MyFrame::RenderRight(wxDC& dc)
{

	wxBitmap adrixright("/opt/extras.ubuntu.com/azpazeta/media/AdrixRight.png", wxBITMAP_TYPE_PNG);
#define adrixdown adrixright
	dc.DrawText("No se ha renderizado bien",wxPoint(-1,-1));
	//Dibujar fondo
	switch(city){
	case 0:{dc.DrawBitmap(adrixdown, wxPoint(adrx,adry),true);}
	case 1:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 2:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/INEM.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 3:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 4:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro2.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 5:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Centro3.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 6:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Hiper.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 7:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Golf.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 8:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 9:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}

	case 10:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/1x1.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	case 11:{ wxBitmap general("/opt/extras.ubuntu.com/azpazeta/media/Gorguez.png",wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(general,wxPoint(-1,-1),true); dc.DrawBitmap(adrixdown,wxPoint(adrx,adry),true); break;}
	}
	
}
