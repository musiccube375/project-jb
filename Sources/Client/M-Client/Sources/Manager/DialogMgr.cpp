#include "stdafx.h"
#include "DialogMgr.h"

CDialogMgr::CDialogMgr()
{
	//m_bShowCfgDlg = false;
}

CDialogMgr::~CDialogMgr()
{
	
}

HRESULT CDialogMgr::InitDialogMgr()
{
	//m_LogDlg.Create(CLogDlg::IDD, &m_mfcTab);
	//m_UserDlg.Create(CUserDlg::IDD, &m_mfcTab);

	m_bShowReqAddFriendDlg = false;

	return S_OK;
}

void CDialogMgr::CreatReqAddFriendDlg(char* pszMessage)
{
	if(m_bShowReqAddFriendDlg) return;

	m_pReqAddFriendDlg = new CReqAddFriendDlg;
	m_pReqAddFriendDlg->Create(IDD_DIALOG_REQ_ADD_FRIEND);

	RECT rt = g_ClientRect;

	int nWidth = rt.right - rt.left;
	int nHeight = rt.bottom - rt.top;

	m_pReqAddFriendDlg->MoveWindow(rt.left + nWidth / 2 - (REQADDFRINED_DIALOG_WIDTH / 2), 
									rt.top + nHeight / 2 - (REQADDFRINED_DIALOG_HEIGHT / 2), 
									REQADDFRINED_DIALOG_WIDTH, REQADDFRINED_DIALOG_HEIGHT);

	m_pReqAddFriendDlg->ShowWindow(SW_SHOW); 

	m_bShowReqAddFriendDlg = true;

	m_pReqAddFriendDlg->Init(pszMessage);
}

void CDialogMgr::DestroyReqAddFriendDlg()
{
	if(m_pReqAddFriendDlg != NULL)   
	{
		m_pReqAddFriendDlg->DestroyWindow();
		SAFE_DELETE(m_pReqAddFriendDlg);
	}

	m_bShowReqAddFriendDlg = false;
}