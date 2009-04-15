#include "stdAfx.h"
#include "ToolMgr.h"

HRESULT	CToolMgr::InitToolMgr(HWND hWnd)
{
	m_hWnd = hWnd;

	m_Log.AddLog("서버 매니저 툴 초기화 작업 시작...");

	m_Log.AddLog("서버 매니저 툴 초기화 작업 끝...");

	return S_OK;
}

void CToolMgr::ReleaseToolMgr()
{
	sToolMgr.DestroyInstance();
}