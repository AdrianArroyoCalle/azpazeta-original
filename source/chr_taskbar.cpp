#include "wx/wx.h"

#include "chr_taskbar.h"
#include "Librerias.h"


BEGIN_EVENT_TABLE(ChrTaskBarIcon, wxTaskBarIcon)
  EVT_MENU(ID_APAGAR, ChrTaskBarIcon::OnMenuExit)
END_EVENT_TABLE()

ChrTaskBarIcon::ChrTaskBarIcon() {
  m_ok = new wxICON(sample);
}

void ChrTaskBarIcon::OnMenuExit(wxCommandEvent& event) {
}

wxMenu* ChrTaskBarIcon::CreatePopupMenu() {
  wxMenu* menu = new wxMenu();

  menu->Append(ID_APAGAR, wxT("E&xit"));

  return menu;
} 
