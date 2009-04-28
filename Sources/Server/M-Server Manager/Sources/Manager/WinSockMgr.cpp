#include "stdafx.h"
#include "WinSockMgr.h"

CWinSockMgr::CWinSockMgr()
{
	
}	

CWinSockMgr::~CWinSockMgr()
{
	ReleaseWinSockMgr();
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

HRESULT CWinSockMgr::AddMServer(MSERVERINFO MServerInfo)
{
	m_mapMServer.insert(MSERVERINFO_MAP_VALUE(m_nMServerCount++, MServerInfo));

	return S_OK;
}

HRESULT CWinSockMgr::DelMServer(char* pszIP)
{
	MSERVERINFO_MAP_IT it = m_mapMServer.begin();

	for( ; it != m_mapMServer.end(); it++)
	{
		if(strcmp(it->second.szIP, pszIP) == 0)
		{
			it->second.pSock->Close();
			SAFE_DELETE(it->second.pSock);
			m_mapMServer.erase(it);

			return S_OK;
		}
	}

	return E_FAIL;
}

void CWinSockMgr::ClearMServer()
{
	MSERVERINFO_MAP_IT it = m_mapMServer.begin();

	for( ; it != m_mapMServer.end(); it++)
	{
		it->second.pSock->Close();
		SAFE_DELETE(it->second.pSock);
	}

	m_mapMServer.clear();
}

HRESULT CWinSockMgr::InitWinSockMgr()
{
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, "소켓 관리자 초기화 작업 시작...");

	m_bServerRun = false;

	InitServerSock();

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, "소켓 관리자 초기화 작업 끝...");

	m_nMServerCount = 0;

	return S_OK;
}

void CWinSockMgr::ReleaseWinSockMgr()
{
	ClearMServer();
	CloseServerSock();
}

void CWinSockMgr::OnAccept()
{
	CClientSock* pClientSock = new CClientSock;

	// M-Server 접속 받음
	m_ServerSock.Accept(*pClientSock);

	CString strIP;	
	int nPort;

	pClientSock->GetPeerName(strIP, (UINT &) nPort);

	CString str;

	str.Format("SOCKET : [%d] - (%s : %d) M-Server 접속됨", pClientSock->m_hSocket, strIP, nPort);
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, str.GetBuffer(0));

	MSERVERINFO MServerInfo;

	MServerInfo.pSock = pClientSock;
	strcpy(MServerInfo.szIP, strIP);

	AddMServer(MServerInfo);

	str.Format("SOCKET : [%d] - (%s : %d) M-Server 정보 생성 완료", pClientSock->m_hSocket, strIP, nPort);
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, str.GetBuffer(0));
}