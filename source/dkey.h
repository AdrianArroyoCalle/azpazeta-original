//Divel Key en Azpazeta
#ifndef DKEY_H_
#define DKEY_H_
#include "Librerias.h"


class DivelKey : public wxDialog
{
public:
	DivelKey();
	void OnQuit(wxCommandEvent& event);
	void OnObtener(wxCommandEvent& event);
	void OnAceptar(wxCommandEvent& event);
	void VerTrucos(wxCommandEvent& event);


};

enum{
	ID_KEY1 = 1124,
	ID_KEY2 = 1125,
	ID_KEY3 = 1126,
	ID_KEY4 = 1127,
	ID_KEY5 = 1128
};



#endif
