//dialogbox.cpp
#include "Librerias.h"


extern int mision,money;
int breadypan;



DialogBox::DialogBox()
: wxDialog(NULL, wxID_ANY, wxT("Bread & Pan"), wxPoint(-1,-1), wxSize(400,400))
{
	diagpanel=new wxPanel(this);
	if(mision==16){
	line1=new wxStaticText(diagpanel, wxID_ANY, "-Veo que traes los panes, no es cierto", wxPoint(-1,-1));





	}	
	wxButton* next=new wxButton(diagpanel, ID_NEXT, "Siguiente", wxPoint(175,350));
	Connect(ID_NEXT,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(DialogBox::Next));
	breadypan=1;

}

void DialogBox::Next(wxCommandEvent& event)
{
	if(mision==16){
		switch(breadypan){
			case 1: line2=new wxStaticText(diagpanel, wxID_ANY, "-Si, traigo los panes que pidio en Azpazeta",wxPoint(-1, 10)); breadypan++;break;
			case 2: line3=new wxStaticText(diagpanel, wxID_ANY, "-Vale, te pagare 100 $",wxPoint(-1, 20)); breadypan++; money+=100;break;
			case 3: line4=new wxStaticText(diagpanel, wxID_ANY, "Tienes madera de vendededor, querrias serlo",wxPoint(-1, 30)); breadypan++;break;

			case 4: line5=new wxStaticText(diagpanel, wxID_ANY, "-Por supuesto, necesitare casa",wxPoint(-1, 40)); breadypan++;break;
			case 5: line6=new wxStaticText(diagpanel, wxID_ANY, "-Te la dare, pero me deberas pagar 100.000 $",wxPoint(-1, 50)); breadypan++;break;
			case 6: line7=new wxStaticText(diagpanel, wxID_ANY, "Sal a fuera y consigue los 100.000 $",wxPoint(-1, 60)); breadypan++;break;
			case 7: line8=new wxStaticText(diagpanel, wxID_ANY, "Cuando los tengas, vienes y te dare una sorpresa",wxPoint(-1, 70)); breadypan++;break;
			case 8: line9=new wxStaticText(diagpanel, wxID_ANY, "-Vale, trato hecho, a conseguir 100.000",wxPoint(-1, 80)); breadypan++;break;
			case 9: mision++; this->Destroy();

		}




		}

}
