#include "stdAfx.h"
#include "ToolMgr.h"

HRESULT	CToolMgr::InitToolMgr(HWND hWnd)
{
	m_hWnd = hWnd;

	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 매니저 툴 초기화 작업 시작...");

	m_WinSockMgr.InitWinSockMgr();
	m_DialogMgr.InitDialogMgr();

	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 매니저 툴 초기화 작업 끝...");

	m_bConnected = false;

	return S_OK;
}

void CToolMgr::ReleaseToolMgr()
{
	m_Log.AddLog(LOG_TYPE_TOOLWORK, "서버 매니저 툴 릴리즈...");

	sToolMgr.DestroyInstance();
}

void CToolMgr::SetLogView(bool bLogView)
{
	if(bLogView) m_Log.EnableLog();
	else m_Log.DisableLog();
}