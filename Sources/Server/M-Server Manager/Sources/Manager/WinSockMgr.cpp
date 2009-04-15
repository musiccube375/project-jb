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
	m_ServerSock.Close();
	m_ServerSock.Create(MAIN_SERVER_PORT);
	m_ServerSock.Listen();

	m_bServerRun = true;
}

void CWinSockMgr::CloseServerSock()
{
	m_ServerSock.Close();

	m_bServerRun = false;
}

HRESULT CWinSockMgr::InitWinSockMgr()
{
	m_bServerRun = false;

	InitServerSock();

	return S_OK;
}