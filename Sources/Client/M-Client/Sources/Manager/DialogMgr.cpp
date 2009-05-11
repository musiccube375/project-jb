#include "stdafx.h"
#include "DialogMgr.h"

CDialogMgr::CDialogMgr()
{
	//m_bShowCfgDlg = false;
}

CDialogMgr::~CDialogMgr()
{
	ClearDialogMgr();
}

HRESULT CDialogMgr::InitDialogMgr()
{
	//m_LogDlg.Create(CLogDlg::IDD, &m_mfcTab);
	//m_UserDlg.Create(CUserDlg::IDD, &m_mfcTab);

	return S_OK;
}

void CDialogMgr::ClearDialogMgr()
{
	ClearReqAddFriendDlg();
}

// Add ReqAddFriendDialog

void CDialogMgr::AddReqAddFriendDlg(UINT nDialogID, RECT rt, char* pszMessage)
{
	ML_DIALOG<CReqAddFriendDlg> mlDialog;

	mlDialog.SetSize(REQADDFRINED_DIALOG_WIDTH, REQADDFRINED_DIALOG_HEIGHT);
	mlDialog.CreateMLDialog(nDialogID, rt, pszMessage);

	if(m_nReqAddFriendDlgCount > MAX_INT_SIZE) m_nReqAddFriendDlgCount = 0;

	if(mlDialog.pDialog == NULL) return;

	mlDialog.pDialog->m_nIndex = m_nReqAddFriendDlgCount;

	m_mapReqAddFriendDlg.insert(ML_REQ_ADD_FRINED_MAP_VALUE(m_nReqAddFriendDlgCount++, mlDialog));
}

void CDialogMgr::DelReqAddFriendDlg(int nIndex)
{
	ML_REQ_ADD_FRINED_MAP_IT it = m_mapReqAddFriendDlg.begin();

	for( ; it != m_mapReqAddFriendDlg.end(); it++)
	{
		if(it->second.pDialog->m_nIndex == nIndex)
		{
			it->second.DestroyMLDialog();	
			m_mapReqAddFriendDlg.erase(it);
			return;
		}
	}
}

void CDialogMgr::ClearReqAddFriendDlg()
{
	ML_REQ_ADD_FRINED_MAP_IT it = m_mapReqAddFriendDlg.begin();

	for( ; it != m_mapReqAddFriendDlg.end(); it++)
	{
		it->second.DestroyMLDialog();	
	}

	m_mapReqAddFriendDlg.clear();
}

// Add ReqAddFriendDialog

