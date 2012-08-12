//Mercado.cpp

#include "mercado.h"

extern int socio, money, electro, food, textil, droga, blacklist, rich,prima;
int estadoMercado=0;

static int precioshiper[4]={100,200,300,50};

Mercado::Mercado() : wxDialog(NULL, wxID_ANY, wxT("Cadena Inc."), wxPoint(-1,-1), wxSize(400,400))
{
	wxPanel* Mpanel=new wxPanel(this);
	info_mercado=new wxStaticText(Mpanel, wxID_ANY, MERCADO_101);
	Mcomprar=new wxButton(Mpanel, ID_MERCADO1, "Comprar productos", wxPoint(50,200));
	Mvender=new wxButton(Mpanel, ID_MERCADO2, "Vender productos", wxPoint(250, 200));
	Mtransformarmateria=new wxButton(Mpanel, ID_MERCADO3, "Transformar m.prima", wxPoint(50, 300));
	Mvendermateria=new wxButton(Mpanel, ID_MERCADO4, "Vender m.prima", wxPoint(250, 300)); 


	Connect(ID_MERCADO1,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Mercado::Comprar));
	Connect(ID_MERCADO2,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Mercado::Vender));
	Connect(ID_MERCADO3,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Mercado::TransformarMateria));
	Connect(ID_MERCADO4,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Mercado::VenderMateria));
}

void Mercado::Comprar(wxCommandEvent& event)
{

	if(estadoMercado==0){
	info_mercado->SetLabel("Compra lo que desees al precio indicado (o no)");
	wxProgressDialog esperar("Mercado Central de Gorguez","Buscando ofertas...",4);

	srand(time(NULL));
	precioproc[0]=rand()%4+1;
	Mcomprar->SetLabel(wxString::Format("Android %d", precioshiper[precioproc[0]]));
	esperar.Update(1);
	precioproc[1]=rand()%4+1;
	Mvender->SetLabel(wxString::Format("Paella %d", precioshiper[precioproc[1]]));
	esperar.Update(2);
	precioproc[2]=rand()%4+1;
	Mtransformarmateria->SetLabel(wxString::Format("Traje %d", precioshiper[precioproc[2]]));
	esperar.Update(3);
	precioproc[3]=rand()%4+1;
	Mvendermateria->SetLabel(wxString::Format("... %d",precioshiper[precioproc[3]]));
	esperar.Update(4);estadoMercado=1;}else if(estadoMercado==1){
	//Comprar Android
	srand(time(NULL));
	int lazar=rand()%10+1;
	switch(lazar){
	case 1:wxMessageBox("En la caja no habia un movil, habia droga, creo que es ilegal...");money-=precioshiper[precioproc[0]]; droga++;break;
	case 2:{if(droga!=0){wxMessageBox("Tenias droga y la policía te ha visto. Pierdes la droga y debes pagar 2000 $");money-=2000;droga=0;}}break;
	default:wxMessageBox("Felicidades, comprado correctamente");money-=precioshiper[precioproc[0]]; electro++;
	}
	//Poner viejos botones
	Mcomprar->SetLabel("Comprar productos");
	Mvender->SetLabel("Vender productos");
	Mtransformarmateria->SetLabel("Transformar m.prima");
	Mvendermateria->SetLabel("Vender m.prima");
	estadoMercado=0;}else{
	if(electro>0){wxMessageBox("Has vendido correctamente"); money+=precioshiper[precioproc[0]]; electro--;}
	Mcomprar->SetLabel("Comprar productos");
	Mvender->SetLabel("Vender productos");
	Mtransformarmateria->SetLabel("Transformar m.prima");
	Mvendermateria->SetLabel("Vender m.prima");
	estadoMercado=0;




	}

}
void Mercado::Vender(wxCommandEvent& event)
{
	if(estadoMercado==0){
	info_mercado->SetLabel("Vende lo que desees al precio indicado (o no)");
	wxProgressDialog esperar("Mercado Central de Gorguez","Buscando ofertas...",4);

	srand(time(NULL));
	precioproc[0]=rand()%4+1;
	Mcomprar->SetLabel(wxString::Format("Android %d", precioshiper[precioproc[0]]));
	esperar.Update(1);
	precioproc[1]=rand()%4+1;
	Mvender->SetLabel(wxString::Format("Paella %d", precioshiper[precioproc[1]]));
	esperar.Update(2);
	precioproc[2]=rand()%4+1;
	Mtransformarmateria->SetLabel(wxString::Format("Traje %d", precioshiper[precioproc[2]]));
	esperar.Update(3);
	precioproc[3]=rand()%4+1;
	Mvendermateria->SetLabel(wxString::Format("... %d",precioshiper[precioproc[3]]));
	esperar.Update(4);estadoMercado=2;

	}else if(estadoMercado==1){
	srand(time(NULL));
	int lazar=rand()%10+1;
	switch(lazar){
	case 1:wxMessageBox("La paella sabe extrana, hay droga, creo que es ilegal...");money-=precioshiper[precioproc[0]]; droga++;break;
	case 2:{if(droga!=0){wxMessageBox("Tenias droga y la policía te ha visto. Pierdes la droga y debes pagar 2000 $");money-=2000;droga=0;}}break;
	default:wxMessageBox("Felicidades, comprado correctamente");money-=precioshiper[precioproc[0]]; food++;
	}
	//Poner viejos botones
	Mcomprar->SetLabel("Comprar productos");
	Mvender->SetLabel("Vender productos");
	Mtransformarmateria->SetLabel("Transformar m.prima");
	Mvendermateria->SetLabel("Vender m.prima");
	estadoMercado=0;}else{
	if(food>0){wxMessageBox("Has vendido correctamente"); money+=precioshiper[precioproc[0]]; food--;}
	Mcomprar->SetLabel("Comprar productos");
	Mvender->SetLabel("Vender productos");
	Mtransformarmateria->SetLabel("Transformar m.prima");
	Mvendermateria->SetLabel("Vender m.prima");
	estadoMercado=0;

	}
}

void Mercado::TransformarMateria(wxCommandEvent& event)
{
	if(estadoMercado==0){
	if(prima>0){
	srand(time(NULL));
	int lazar=rand()%4+1;
	switch(lazar){
	case 1: wxMessageBox("Se ha convertido en un movil Android por 400 $"); prima--; money-=400; electro++;break;
	case 2: wxMessageBox("Se ha convertido en comida por 400 $"); prima--; money-=400; food++;break;
	case 3: wxMessageBox("Se ha convertido en ropa por 400 $"); prima--; money-=400; textil++; break;
	case 4: wxMessageBox("La materia prima no ha dado nada, lo pierdes y pagas 400 $"); prima--;money-=400; break;


	}


	}else{wxMessageBox("No tienes Materia prima. debes de ir a una granja o mina");}







	}else if(estadoMercado==1){
	srand(time(NULL));
	int lazar=rand()%10+1;
	switch(lazar){
	case 1:wxMessageBox("La ropa tiene algo, es droga, creo que es ilegal...");money-=precioshiper[precioproc[0]]; droga++;break;
	case 2:{if(droga!=0){wxMessageBox("Tenias droga y la policía te ha visto. Pierdes la droga y debes pagar 2000 $");money-=2000;droga=0;}}break;
	default:wxMessageBox("Felicidades, comprado correctamente");money-=precioshiper[precioproc[0]]; textil++;
	}
	//Poner viejos botones
	Mcomprar->SetLabel("Comprar productos");
	Mvender->SetLabel("Vender productos");
	Mtransformarmateria->SetLabel("Transformar m.prima");
	Mvendermateria->SetLabel("Vender m.prima");
	estadoMercado=0;}else{
	if(textil>0){wxMessageBox("Has vendido correctamente"); money+=precioshiper[precioproc[0]]; textil--;}
	Mcomprar->SetLabel("Comprar productos");
	Mvender->SetLabel("Vender productos");
	Mtransformarmateria->SetLabel("Transformar m.prima");
	Mvendermateria->SetLabel("Vender m.prima");
	estadoMercado=0;

	}
}
void Mercado::VenderMateria(wxCommandEvent& event)
{
	if(estadoMercado==0){
	if(prima>0){
	srand(time(NULL));
	int lazar=rand()%4+1;
	switch(lazar){
	case 1: wxMessageBox("Te han dado 400 $"); prima--; money+=400;break;
	case 2: wxMessageBox("Te han dado 200 $"); prima--; money+=200;break;
	case 3: wxMessageBox("Te han dado 50 $"); prima--; money+=50;break;
	case 4: wxMessageBox("La materia prima no tenia valor, la pierdes y no recibes nada"); prima--;break;

	}}else{wxMessageBox("No tienes materia prima");}





	}else if(estadoMercado==1){
	srand(time(NULL));
	int lazar=rand()%10+1;
	switch(lazar){
	case 1:wxMessageBox("Te dan una caja extrana, hay droga, creo que es ilegal...");money-=precioshiper[precioproc[0]]; droga++;break;
	case 2:{if(droga!=0){wxMessageBox("Tenias droga y la policía te ha visto. Pierdes la droga y debes pagar 2000 $");money-=2000;droga=0;}}break;
	case 3:wxMessageBox("Te ha tocado ropa de moda");money-=precioshiper[precioproc[0]]; textil++;break;
	case 4:wxMessageBox("Te ha tocado un movil Android");money-=precioshiper[precioproc[0]]; electro++;break;
	case 5:wxMessageBox("Te ha tocado una gran paella");money-=precioshiper[precioproc[0]]; food++;break;
	default:wxMessageBox("Te ha tocado un producto lujoso, pero inutil");money-=precioshiper[precioproc[0]]; rich++;

	}	Mcomprar->SetLabel("Comprar productos");
	Mvender->SetLabel("Vender productos");
	Mtransformarmateria->SetLabel("Transformar m.prima");
	Mvendermateria->SetLabel("Vender m.prima");
	estadoMercado=0;}else{

if(droga>0){wxMessageBox("Has vendido droga correctamente"); money+=precioshiper[precioproc[0]]; droga--;}
	Mcomprar->SetLabel("Comprar productos");
	Mvender->SetLabel("Vender productos");
	Mtransformarmateria->SetLabel("Transformar m.prima");
	Mvendermateria->SetLabel("Vender m.prima");
	estadoMercado=0;





	}
}
