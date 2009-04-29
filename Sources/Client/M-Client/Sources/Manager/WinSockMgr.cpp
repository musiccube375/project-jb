#include "stdafx.h"
#include "WinSockMgr.h"

CWinSockMgr::CWinSockMgr()
{
	
}	

CWinSockMgr::~CWinSockMgr()
{
	ReleaseWinSockMgr();
}

void CWinSockMgr::CloseServerSock()
{
	m_ServerSock.Close();

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 소켓 닫음...");

	m_bConnected = false;
}

HRESULT CWinSockMgr::InitWinSockMgr()
{
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, "소켓 관리자 초기화 작업 시작...");

	m_nServerCount = 0;
	m_bConnected = false;
	m_bConnectTry = true;

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, "소켓 관리자 초기화 작업 끝...");

	return S_OK;
}

void CWinSockMgr::ReleaseWinSockMgr()
{
	CloseServerSock();
}

bool CWinSockMgr::ConnectToServer()
{
	if(!m_bConnectTry || m_bConnected) return false;

	CloseServerSock();
	m_ServerSock.m_Tag = TAG_CLIENT;
	m_ServerSock.Create();
	m_ServerSock.Connect(g_sToolMgr.m_ServerList[m_nServerCount].szServerIP, MIDDLE_SERVER_PORT);

	int nRet = m_ServerSock.Send("CONNECT_REQ", 16);

	if(nRet <= SOCKET_ERROR)
	{
		if(++m_nServerCount > MAX_SERVER_COUNT)
		{
			m_nServerCount = 0;
			m_bConnectTry = false;
			m_bConnected = false;
			AfxMessageBox("No server to connect now...");

			g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 접속 최종 실패...");
		}
	}

	return true;
}

MSG_RET CWinSockMgr::OnReceive(SOCKET Socket, int nTag)
{
	char recv[512];

	int nRet = m_ServerSock.Receive(recv, 512);

	if(nRet <= SOCKET_ERROR) 
	{	
		return MSG_RET_ERROR;
	}

	if(strlen(recv) <= 32)
	{
		if(strcmp(recv, "ACCEPT_DENY") == 0)
		{
			if(++m_nServerCount > MAX_SERVER_COUNT)
			{
				m_nServerCount = 0;
				m_bConnectTry = false;
				m_bConnected = false;
				AfxMessageBox("No server to connect now...");

				g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 접속 최종 실패...");
			}

			return MSG_CONNECT_FAIL;
		}
		else if(strcmp(recv, "ACCEPT_OK") == 0)
		{
			char buff[512];
			sprintf(buff, "(%s : %d) 서버 접속 성공...", g_sToolMgr.m_ServerList[m_nServerCount].szServerIP, MAIN_SERVER_PORT);
			g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, buff);

			//AfxMessageBox(buff);

			m_bConnected = true;

			return MSG_CONNECT_SUCCESS;
		}
	}
	else
	{
		m_MSGParser.ParseMSG(recv);

		return m_CMDHandlerMgr.CMD_Main_Handle(m_MSGParser.m_msgData);
	}

	return MSG_RET_NONE;
}