#include "stdAfx.h"
#include "ToolMgr.h"

void CToolMgr::InitVariable()
{
	m_hWnd = NULL;
	m_bRun = false;
	m_AccountActived = false;
}

HRESULT	CToolMgr::InitToolMgr(HWND hWnd)
{
	InitVariable();

	m_hWnd = hWnd;

	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 매니저 툴 초기화 작업 시작...");

	m_WinSockMgr.InitWinSockMgr();
	m_SQLMgr.InitSQLMgr();

	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 매니저 툴 초기화 작업 끝...");

	return S_OK;
}

void CToolMgr::ReleaseToolMgr()
{
	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 매니저 툴 릴리즈...");

	m_SQLMgr.ReleaseSQLMgr();

	sToolMgr.DestroyInstance();
}

void CToolMgr::SetLogView(bool bLogView)
{
	if(bLogView) m_Log.EnableLog();
	else m_Log.DisableLog();
}

void CToolMgr::SetRun(bool bRun)
{
	m_bRun = bRun;
}

void CToolMgr::SetUserID(char* szID)
{
	strcpy(m_szUserID, szID);
}

void CToolMgr::SetAccountActived(bool bActive)
{
	m_AccountActived = bActive;
}

bool CToolMgr::IsAccountActived()
{	
	return m_AccountActived;
}