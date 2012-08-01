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
#include "inicio.hpp"
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
	EVT_MENU(ID_INSTRUCCIONES, MyFrame::OnInstrucciones)
	EVT_KEY_DOWN(MyFrame::OnTecla)	
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
extern int x, y, adrx, adry, mision, city;
extern char name;
extern wxString newname;
int fachada;
// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	ChrTaskBarIcon* icon = new ChrTaskBarIcon(); 
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
	//if(city==4){MyFrame::Stage4();}
	
        
        }else{	MyFrame *frame = new MyFrame("Azpazeta");
	frame->Show(true);}
        
        
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
	FILE* PointMash;
	PointMash=fopen("/usr/share/Azpazeta/Res.cfg","r");
	if(PointMash){
	fscanf(PointMash,"RES=%d:%d",&x,&y);
	SetSize(x,y);
	adrx=x/2;
	adry=y/2;
	fclose(PointMash);
	}else{wxMessageBox(wxT("No se ha encontrado archivo de resolución PointMash en: /usr/share/Azpazeta/Res.cfg"),wxT("Error 201"),wxICON_ERROR|wxOK);SetSize(800,600); x=800; y=600;}
	panel = new wxPanel(this);
	wxInitAllImageHandlers();
	/*wxImage portada("/usr/share/Azpazeta/media/Portada.png", wxBITMAP_TYPE_PNG);
	wxImage portadaSize;
	portadaSize=portada.Scale(x/2,y/2);
	portadaSize.SaveFile("/usr/share/Azpazeta/media/newres/Portada.png",wxBITMAP_TYPE_PNG);
	wxBitmap portadaBMP("/usr/share/Azpazeta/media/newres/Portada.png", wxBITMAP_TYPE_PNG);*/
	wxBitmap portadaBMP("/usr/share/Azpazeta/media/Portada4.png", wxBITMAP_TYPE_PNG);
	Portada = new wxStaticBitmap(panel, ID_DIBUJO, portadaBMP, wxPoint(-1,-1));
	if(fachada!=1){
	actualizar=new wxButton(panel, ID_ACTUALIZAR, wxT("Actualizar juego"), wxPoint(100,500));
	jugar=new wxButton(panel, ID_JUGAR, wxT("Cargar partida"), wxPoint(250,500));
	instrucciones=new wxButton(panel, ID_INSTRUCCIONES, wxT("Instrucciones"), wxPoint(400,500));}

	Connect(ID_JUGAR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnJugar));
	Connect(ID_USER, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnInstrucciones));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(ID_INSTRUCCIONES, "&Instrucciones", "Instrucciones sobre Azpazeta");
    helpMenu->Append(Minimal_About, "A&cerca\tF1", "Acerca de Azpazeta");
	fileMenu->Append(ID_ACTUALIZAR, "A&ctualizar", "Actualizar Azpazeta");
	fileMenu->Append(ID_NET, "&Mas productos de Divel", "Mas productos de Divel");	
    fileMenu->Append(Minimal_Quit, "&Salir\tAlt-X", "Salir sin guardar");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&Archivo");
    menuBar->Append(helpMenu, "A&yuda");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Azpazeta 1.0 Sin comprobar actualizaciones");
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
	wxBitmap bocadillo("/usr/share/Azpazeta/media/Bocadillo.png",wxBITMAP_TYPE_PNG);
	Bocadillo=new wxStaticBitmap(panel, ID_DIBUJO, bocadillo, wxPoint(600,450));
	cap1mis1=new wxStaticText(panel, ID_DIBUJO, wxT(CAP1MIS1TEX1), wxPoint(625, 470));
	Stage3();
	mision=15;
}
void MyFrame::OnActualizar(wxCommandEvent& WXUNUSED(event))
{

}
void MyFrame::OnInstrucciones(wxCommandEvent& WXUNUSED(event))
{

}
void MyFrame::OnJugar(wxCommandEvent& WXUNUSED(event))
{
	//wxSound("/usr/share/Azpazeta/audio/Hip-hop.wav").Play(wxSOUND_ASYNC|wxSOUND_LOOP);
	FILE* partida;
	wxString archivo=wxT("/usr/share/Azpazeta/save/save.azp");
	partida=fopen("/usr/share/Azpazeta/save/save.azp","r");
	if(partida){
	fclose(partida);
	SaveDialog* extrasavedlg=new SaveDialog();
        extrasavedlg->Cargar(archivo);
        extrasavedlg->Destroy();
	actualizar->Destroy();
	jugar->Destroy();
	instrucciones->Destroy();
	Load();
	}else if(city!=0){	
	}else{
	wxMessageBox(wxT("Empezando nueva partida"), wxT("Azpazeta"),wxICON_INFORMATION|wxOK);
	newname=wxGetTextFromUser(wxT("Introduce tu nombre para la partida"),wxT("Azpazeta"),wxT(""));
	city=1;
	actualizar->Destroy();
	jugar->Destroy();
	instrucciones->Destroy();
	MyFrame::Stage1();
	}
}

void MyFrame::OnTecla(wxKeyEvent& event)
{
 int ascii = event.GetKeyCode();
	wxBitmap adrixdown("/usr/share/Azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixup("/usr/share/Azpazeta/media/AdrixUp.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixleft("/usr/share/Azpazeta/media/AdrixLeft.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixright("/usr/share/Azpazeta/media/AdrixRight.png", wxBITMAP_TYPE_PNG);
switch(city){
	case 1:
	switch(ascii)
	{	
	//El primer edificio está a 26 pix-------333pix y 27 piy--------------330 piy
		case WXK_LEFT:
		if(adry< 390 && adrx<330){}else{
		adrx--;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixleft, wxPoint(adrx,adry));
		wxPrintf("X= %d, Y= %d", adrx, adry);
		if(adrx==1 && mision>=6){Stage2();}
		}
		break;
		case WXK_UP:
		if(adry< 390 && adrx<330){}else{
		adry--;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixup, wxPoint(adrx,adry));}
		break;
		case WXK_RIGHT:
		//if(){}else{
		adrx++;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixright, wxPoint(adrx,adry));//}
		break;
		case WXK_DOWN:
		//if(/*adry< 330 && adrx<334*/){}else{
		adry++;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(adrx,adry));//}
		break;
		case WXK_RETURN:
		if(adry<=400 && adrx<180)
		{if(adrx>=140){
		switch(mision){
		case 0:{
		wxBitmap bocadillo("/usr/share/Azpazeta/media/Bocadillo.png",wxBITMAP_TYPE_PNG);
		Bocadillo=new wxStaticBitmap(panel, ID_DIBUJO, bocadillo, wxPoint(600,450));
		cap1mis1=new wxStaticText(panel, ID_DIBUJO, wxT("Quien eres?\nNo te conozco.\nEres el nuevo?\nPresiona ENTER"), wxPoint(625, 470));
		mision++;
		break;}
		case 1:
		cap1mis1->SetLabel(wxT("Bueno, me presento\nSoy Alfredo\nEl alcalde de Azpazeta\nPresiona ENTER"));
		mision++;
		break;
		case 2:{
		wxString completo=wxT("Como te llamas?\n")+newname+wxT("\nBonito nombre\nPresiona ENTER");
		cap1mis1->SetLabel(completo);
		mision++;
		break;}
		case 3:
		cap1mis1->SetLabel(wxT("Te has perdido?\nSupongo que querras casa\nPero no va ser gratis\nPresiona ENTER"));
		mision++;
		break;
		case 4:
		cap1mis1->SetLabel(wxT("Necesitaras un trabajo\nNo se de que\nEso lo dejo a tu eleccion\nPresiona ENTER"));
		mision++;
		break;
		case 5:
		cap1mis1->SetLabel(wxT("[Objetivo anadido:\nEncontrar trabajo]\nPista: El pueblo esta a la izquierda"));
		mision++;
		break;
		}}}
		break;
		case WXK_ESCAPE:
		wxMessageBox(wxT("Intentando salir eh"));
		break;
		case WXK_TAB:
		wxMessageBox(wxT("TAB"));
		break;
		case WXK_SHIFT:
		wxString cheat=wxGetTextFromUser(wxT("Introduce el Cheat Code"), wxT("Debug Mode"),wxT(""));
		if(cheat==wxT("2")){Stage1();Stage2();}
		break;
		}break;
	case 2:
	switch(ascii)
	{	
	//El primer edificio está a 26 pix-------333pix y 27 piy--------------330 piy
		case WXK_LEFT:
		if(adry< 470){}else{
		adrx--;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixleft, wxPoint(adrx,adry));
		if(adrx==1 && mision==15){Adrix->Destroy();Stage3();}
		}
		break;
		case WXK_UP:
		if(adry< 470){}else{
		adry--;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixup, wxPoint(adrx,adry));}
		break;
		case WXK_RIGHT:
		//if(){}else{
		adrx++;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixright, wxPoint(adrx,adry));//}
		break;
		case WXK_DOWN:
		//if(/*adry< 330 && adrx<334*/){}else{
		adry++;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(adrx,adry));//}
		break;
		case WXK_RETURN:
		if(adry<=480)
		{if(adrx>=108 && adrx<=170){
		switch(mision){
		case 6:
		cap1mis1->SetLabel(wxT("\"El INEM\nSeguro que aqui habra trabajo\nVoy a ver\"\nPresiona ENTER"));
		mision++;
		break;
		case 7:
		cap1mis1->SetLabel(wxT("Siguiente...\n-Venia a por trabajo\n-Tenemos en la panificadora\nPresiona ENTER"));
		mision++;
		break;
		case 8:
		cap1mis1->SetLabel(wxT("-Creo que me valdra\n-Siguiente...\n\nPresiona ENTER"));
		mision++;
		break;
		case 9:
		cap1mis1->SetLabel(wxT("[Objetivo anadido:\nIr a la panificadora]"));
		mision++;
		break;
		default:
		cap1mis1->SetLabel(wxT("Otra vez tu\nAnda vete para fuera\n"));
		}}
		if(adrx>=474 && adrx<=542){
		switch(mision){
		case 10:
		cap1mis1->SetLabel(wxT("(Ruidos)\nPUES SI, IMPORTA\nAnda, vete a...\nPresiona ENTER"));
		mision++;
		break;
		case 11:
		cap1mis1->SetLabel(wxT("-Y tu quien eres?\n-Vengo por el puesto\n-Ah, sí.\nPresiona ENTER"));
		mision++;
		break;
		case 12:
		cap1mis1->SetLabel(wxT("Trabajaras de comerciante\nambulante.\nIras por los pueblos\nPresiona ENTER"));
		mision++;
		break;
		case 13:
		cap1mis1->SetLabel(wxT("Vamos a ver como lo haces\nVe a la plaza de Gorguez\nLleva estos panes\nPresiona ENTER"));
		mision++;
		break;
		case 14:
		cap1mis1->SetLabel(wxT("[Objetivo anadido:\nVender los panes en Gorguez]\nPista: La estacion de tren\ntiene trenes locales"));
		mision++;
		break; 
		default:
		cap1mis1->SetLabel(wxT("(Esta cerrado)"));
		break;
		}}}

		break;
		case WXK_ESCAPE:
		wxMessageBox(wxT("Intentando salir eh"));
		break;
		case WXK_TAB:
		wxMessageBox(wxT("TAB"));
		break;
		case WXK_SHIFT:
		wxString cheat=wxGetTextFromUser(wxT("Introduce el Cheat Code"), wxT("Debug Mode"),wxT(""));
		if(cheat==wxT("2")){Stage1();Stage2();}
		break;
		}break;
	case 3:
	switch(ascii)
	{	
	//El primer edificio está a 26 pix-------333pix y 27 piy--------------330 piy
		case WXK_LEFT:
		if((adry<156 && adrx<307) || ((adry<383 && adry>200) && adrx<307) || (adry<383 && adrx>503)){if(adrx==504){adrx--; Adrix->Destroy();Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixleft, wxPoint(adrx,adry)); }}else{
		if(adrx<=1){Stage4();Adrix->Destroy();}else{
		adrx--;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixleft, wxPoint(adrx,adry));}
		//if(adrx==1 && mision>=6){Stage2();}
		}
		break;
		case WXK_UP:
		if((adry<156 && adrx<307) || ((adry<383 && adry>200) && adrx<307) || (adry<383 && adrx>503)){printf("Valor X=%d Y=%d",adrx, adry);if(adry==199){adry--; Adrix->Destroy();Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixup, wxPoint(adrx,adry)); }}else{
		adry--;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixup, wxPoint(adrx,adry));}
		break;
		case WXK_RIGHT:
		if((adry<156 && adrx<307) || ((adry<383 && adry>200) && adrx<307) || (adry<383 && adrx>503)){if(adrx==306){adrx++; Adrix->Destroy();Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixright, wxPoint(adrx,adry)); }}else{
		if(adrx>=746){Adrix->Destroy();Stage2();}
		adrx++;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixright, wxPoint(adrx,adry));}
		break;
		case WXK_DOWN:
		if((adry<156 && adrx<307) || ((adry<383 && adry>200) && adrx<307) || (adry<383 && adrx>503)){if(adry==382 || adry==155){adry++; Adrix->Destroy();Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(adrx,adry)); }}else{
		adry++;
		Adrix->Destroy();
		Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(adrx,adry));}
		break;
		case WXK_RETURN:
                //Trenes
		if(adry<=427 && (adrx>=633 && adrx<=670)){
		switch(mision){
		case 15:
		cap1mis1->SetLabel(wxT("-Supongo que es la estacion\nVamos a ver como es\nGorguez\nPresiona ENTER"));
		mision++;
		break;
		default:
		wxPrintf("Cargando...");
		TrenDialog* trendlg=new TrenDialog();
		wxPrintf("Mostrando...");
		trendlg->ShowModal();
		trendlg->Destroy();
		break;
		}}
                //Piso franco
                if(adry<=196 && (adrx>=156 && adrx<=182)){
		SaveDialog* savedlg;
                savedlg=new SaveDialog();
                savedlg->ShowModal();
                savedlg->Destroy();
		Adrix->Destroy();
		Load();
                }
		break;
		case WXK_ESCAPE:
		wxMessageBox(wxT("Intentando salir eh"));
		break;
		case WXK_TAB:
		wxMessageBox(wxT("TAB"));
		break;
		case WXK_SHIFT:
		wxString cheat=wxGetTextFromUser(wxT("Introduce el Cheat Code"), wxT("Debug Mode"),wxT(""));
		break;
		}break;
	case 4:
	switch(ascii)
	{	
	//366-222
		case WXK_LEFT:
			if(adrx<=283){}else{
			adrx--;
			Adrix->Destroy();
			Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixleft, wxPoint(adrx, adry));}
		break;
		case WXK_UP:
			if(adry<=204 && adrx>=474){}else{
			adry--;
			Adrix->Destroy();
			Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixup, wxPoint(adrx,adry));}
		break;
		case WXK_RIGHT:
			if((adry<=204 && adrx>=475) || (adry>=366 && adrx>=474)){}else{
			adrx++;
			Adrix->Destroy();
			Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixright, wxPoint(adrx, adry));}
		break;
		case WXK_DOWN:
			if(adry>=366 && adrx>=474){}else{
			adry++;
			Adrix->Destroy();
			Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(adrx, adry));}
		break;
		case WXK_RETURN:{
		DivelKey* keydlg=new DivelKey();
		keydlg->ShowModal();
		keydlg->Destroy();}
		break;
		case WXK_ESCAPE:
		
		break;
		case WXK_TAB:
		
		break;
		case WXK_SHIFT:
		
		break;
		}break;

}
}

void MyFrame::Stage1()
{	wxBitmap adrixdown("/usr/share/Azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	/*wxBitmap adrixup("/usr/share/Azpazeta/media/AdrixUp.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixleft("/usr/share/Azpazeta/media/AdrixLeft.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixright("/usr/share/Azpazeta/media/AdrixRight.png", wxBITMAP_TYPE_PNG);*/
	wxBitmap cap1dib1("/usr/share/Azpazeta/media/1x1.png", wxBITMAP_TYPE_PNG);
	Portada->SetBitmap(cap1dib1);
	Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(x/2,y/2));
	actualizar->Destroy();
	jugar->Destroy();
	instrucciones->Destroy();
	wxPrintf("Bienvenido a Azpazeta!\nAutor: Adrian Arroyo Calle\nAno: 2012\nJuego certficado por: Divel Games\n");

}

void MyFrame::Stage2()
{
	wxBitmap adrixdown("/usr/share/Azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	/*wxBitmap adrixup("/usr/share/Azpazeta/media/AdrixUp.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixleft("/usr/share/Azpazeta/media/AdrixLeft.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixright("/usr/share/Azpazeta/media/AdrixRight.png", wxBITMAP_TYPE_PNG);*/
	wxBitmap inem("/usr/share/Azpazeta/media/INEM.png", wxBITMAP_TYPE_PNG);
	Portada->SetBitmap(inem);
	adrx=500;
	adry=500;
	Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(adrx,adry));
	city=2;
}
void MyFrame::Stage3()
{
		wxBitmap adrixdown("/usr/share/Azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	/*wxBitmap adrixup("/usr/share/Azpazeta/media/AdrixUp.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixleft("/usr/share/Azpazeta/media/AdrixLeft.png", wxBITMAP_TYPE_PNG);
	wxBitmap adrixright("/usr/share/Azpazeta/media/AdrixRight.png", wxBITMAP_TYPE_PNG);*/
	wxBitmap centro1("/usr/share/Azpazeta/media/Centro1.png", wxBITMAP_TYPE_PNG);
	Portada->SetBitmap(centro1);
	adrx=500;
	adry=500;
	Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(adrx, adry));
	city=3;
}
void MyFrame::Stage4()
{
	wxBitmap adrixdown("/usr/share/Azpazeta/media/Adrix.png", wxBITMAP_TYPE_PNG);
	wxBitmap centro2("/usr/share/Azpazeta/media/Centro2.png",wxBITMAP_TYPE_PNG);
	Portada->SetBitmap(centro2);
	adrx=300;
	adry=300;
	Adrix=new wxStaticBitmap(panel, ID_DIBUJO, adrixdown, wxPoint(adrx, adry));
	city=4;
}
void MyFrame::Stage5()
{

}
void MyFrame::Stage6()
{

}
void MyFrame::Stage7()
{

}
void MyFrame::Stage11()
{

}
void MyFrame::Load()
{
	wxBitmap bocadillo("/usr/share/Azpazeta/media/Bocadillo.png",wxBITMAP_TYPE_PNG);
	Bocadillo=new wxStaticBitmap(panel, ID_DIBUJO, bocadillo, wxPoint(600,450));
	cap1mis1=new wxStaticText(panel, ID_DIBUJO, wxT(CAP1MIS1TEX1), wxPoint(625, 470));
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
