#include "stdafx.h"
#include "DialogMgr.h"

CDialogMgr::CDialogMgr()
{
	//m_bShowCfgDlg = false;
}

CDialogMgr::~CDialogMgr()
{
	
}

HRESULT CDialogMgr::InitDialogMgr(CMFCTabCtrl* pTab)
{
	m_LogDlg.Create(CLogDlg::IDD, pTab);
	m_UserDlg.Create(CUserDlg::IDD, pTab);
	m_StatusDlg.Create(CStatusDlg::IDD, pTab);

	return S_OK;
}
