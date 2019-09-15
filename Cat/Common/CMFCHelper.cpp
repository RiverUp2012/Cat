
#include "stdafx.h"
#include "CMFCHelper.h"

bool CMFCHelper::attachDialogControl(CDialog * dlg, CWnd * control, const int controlID) {
	if (dlg && control) {
		CWnd * wnd = dlg->GetDlgItem(controlID);
		if (wnd) {
			control->Attach(wnd->GetSafeHwnd());
			return true;
		}
	}
	return false;
}
