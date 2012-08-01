#ifndef CHR_TASKBAR_H
#define CHR_TASKBAR_H 1

#include "wx/wx.h"
#include "wx/taskbar.h"
#include "wx/menu.h"
#include "wx/icon.h"

class ChrTaskBarIcon : public wxTaskBarIcon {
 public:
  ChrTaskBarIcon();
  void OnMenuExit(wxCommandEvent& event);

  virtual wxMenu* CreatePopupMenu();

  wxIcon* m_ok;

 private:
  DECLARE_EVENT_TABLE()
}; 
#endif
