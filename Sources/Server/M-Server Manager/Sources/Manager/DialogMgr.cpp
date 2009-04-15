#include "stdafx.h"
#include "DialogMgr.h"

CDialogMgr::CDialogMgr()
{
	//m_bShowCfgDlg = false;
}

CDialogMgr::~CDialogMgr()
{
	
}

HRESULT InitDialogMgr()
{
	m_LogDlg.Create(CLogDlg::IDD, &m_mfcTab);
	m_UserDlg.Create(CUserDlg::IDD, &m_mfcTab);

	return S_OK;
}
