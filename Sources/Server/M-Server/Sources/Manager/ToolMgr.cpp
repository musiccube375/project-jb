#include "stdAfx.h"
#include "ToolMgr.h"

HRESULT	CToolMgr::InitToolMgr(HWND hWnd, const char* pszIP)
{
	m_hWnd = hWnd;

	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 툴 초기화 작업 시작...");

	m_WinSockMgr.InitWinSockMgr(pszIP);

	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 툴 초기화 작업 끝...");

	m_bConnected = false;

	return S_OK;
}

void CToolMgr::ReleaseToolMgr()
{
	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 툴 릴리즈...");

	sToolMgr.DestroyInstance();
}

void CToolMgr::SetLogView(bool bLogView)
{
	if(bLogView) m_Log.EnableLog();
	else m_Log.DisableLog();
}

void CToolMgr::SetConnected(bool bConnected)
{
	m_bConnected = bConnected;
}

bool CToolMgr::IsConnected()
{
	return m_bConnected;
}