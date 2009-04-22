#include "stdafx.h"
#include "WinSockMgr.h"

CWinSockMgr::CWinSockMgr()
{
	
}	

CWinSockMgr::~CWinSockMgr()
{

}

void CWinSockMgr::InitServerSock()
{
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 소켓 초기화...");

	m_ServerSock.Close();
	m_ServerSock.Create(MAIN_SERVER_PORT);
	m_ServerSock.Listen();

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 가동 시작...");

	m_bServerRun = true;
}

void CWinSockMgr::CloseServerSock()
{
	m_ServerSock.Close();

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 소켓 닫음...");

	m_bServerRun = false;
}

bool CWinSockMgr::ConnectToServerMgr()
{
	if(m_bServerMgrConnect) 
	{
		g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "이미 서버 매니저에 접속 되어 있으므로 접속 시도를 취소함...");

		return false;
	}

	CloseServerMgrSock();

	if(m_ServerMgrSock.Connect(m_szServerMgrIP, MAIN_SERVER_PORT) != SOCKET_ERROR)
	{
		g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 매니저에 접속 성공...");
		m_bServerMgrConnect = true;
	}
	else g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 매니저에 접속 실패...");

	return true;
}

void CWinSockMgr::CloseServerMgrSock()
{
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 매니저 접속 소켓 닫음...");

	m_ServerMgrSock.Close();
	m_bServerMgrConnect = false;
}

HRESULT CWinSockMgr::InitWinSockMgr(char* pszServerMgrIP)
{
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, "소켓 관리자 초기화 작업 시작...");

	m_bServerRun = false;

	InitServerSock();

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, "소켓 관리자 초기화 작업 끝...");

	strcpy(m_szServerMgrIP, pszServerMgrIP);

	m_bServerMgrConnect = false;

	return S_OK;
}