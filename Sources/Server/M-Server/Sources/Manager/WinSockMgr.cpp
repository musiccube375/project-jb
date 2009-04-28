#include "stdafx.h"
#include "WinSockMgr.h"

CWinSockMgr::CWinSockMgr()
{
	
}	

CWinSockMgr::~CWinSockMgr()
{
	ReleaseWinSockMgr();
}

void CWinSockMgr::SetServerRun(bool bServerRun)
{

}

void CWinSockMgr::InitServerSock()
{
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 소켓 초기화...");

	m_ServerSock.Close();
	m_ServerSock.Create(MIDDLE_SERVER_PORT);
	m_ServerSock.Listen();

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 가동 시작...");

	m_bServerRun = false;
}

void CWinSockMgr::CloseServerSock()
{
	m_ServerSock.Close();

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 소켓 닫음...");

	m_bServerRun = false;
}

bool CWinSockMgr::ConnectToServerMgr(const char* pszIP)
{
	if(m_bServerRun) 
	{
		g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "이미 서버 매니저에 접속 되어 있으므로 접속 시도를 취소함...");

		return false;
	}

	strcpy(m_szServerMgrIP, pszIP);

	CloseServerMgrSock();
	m_ServerMgrSock.m_Tag = TAG_MAIN_SERVER;
	m_ServerMgrSock.Create();
	m_ServerMgrSock.Connect(m_szServerMgrIP, MAIN_SERVER_PORT);

	m_ServerMgrSock.Send("CONNECT_REQ", 16);

	return true;
}

void CWinSockMgr::CloseServerMgrSock()
{
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 매니저 접속 소켓 닫음...");

	m_ServerMgrSock.Close();
	m_bServerMgrConnect = false;
	m_bServerRun = false;
}

HRESULT CWinSockMgr::InitWinSockMgr(const char* pszServerMgrIP)
{
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, "소켓 관리자 초기화 작업 시작...");

	m_bServerRun = false;

	InitServerSock();

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, "소켓 관리자 초기화 작업 끝...");

	strcpy(m_szServerMgrIP, pszServerMgrIP);

	m_bServerMgrConnect = false;
	m_nUserCount = 0;
	m_nUserQueryCount = 0;

	return S_OK;
}

void CWinSockMgr::ReleaseWinSockMgr()
{
	ClearUser();
	ClearUserQuery();
	CloseServerMgrSock();
	CloseServerSock();
}

HRESULT CWinSockMgr::AddUser(USERINFO UserInfo)
{
	if(m_nUserCount > MAX_INT_SIZE) m_nUserCount = 0;

	m_mapUserInfo.insert(USERINFO_MAP_VALUE(m_nUserCount++, UserInfo));

	return S_OK;
}

HRESULT CWinSockMgr::DelUser(int nIndex)
{
	USERINFO_MAP_IT it = m_mapUserInfo.begin();

	for( ; it != m_mapUserInfo.end(); it++)
	{
		/*if(it->second._ID == ID)
		{
			it->second._pSock->Close();
			SAFE_DELETE(it->second._pSock);
			m_mapWPInfo.erase(it);

			return S_OK;
		}*/
	}

	return E_FAIL;
}

void CWinSockMgr::ClearUser()
{
	USERINFO_MAP_IT it = m_mapUserInfo.begin();

	for( ; it != m_mapUserInfo.end(); it++)
	{
		SAFE_DELETE(it->second.pSock);
		/*if(it->second._ID == ID)
		{
			it->second._pSock->Close();
			SAFE_DELETE(it->second._pSock);
			m_mapWPInfo.erase(it);

			return;
		}*/
	}

	m_mapUserInfo.clear();
}

PUSERINFO CWinSockMgr::GetUser(char* pszID)
{
	USERINFO_MAP_IT it = m_mapUserInfo.begin();

	for( ; it != m_mapUserInfo.end(); it++)
	{
		if(strcmp(it->second.UserBase.szID, pszID) == 0)
			return &it->second;
	}

	return 0;
}

int CWinSockMgr::AddUserQuery(USERQUERYINFO UserQuery)
{
	if(m_nUserQueryCount > MAX_INT_SIZE) m_nUserQueryCount = 0;

	m_mapUserQuery.insert(USERQUERYINFO_MAP_VALUE(m_nUserQueryCount, UserQuery));

	return m_nUserQueryCount++;
}

HRESULT CWinSockMgr::DelUserQuery()
{
	USERQUERYINFO_MAP_IT it = m_mapUserQuery.begin();

	for( ; it != m_mapUserQuery.end(); it++)
	{
		/*if(it->second._ID == ID)
		{
			it->second._pSock->Close();
			SAFE_DELETE(it->second._pSock);
			m_mapWPInfo.erase(it);

			return S_OK;
		}*/
	}

	return E_FAIL;
}

void CWinSockMgr::ClearUserQuery()
{
	m_mapUserQuery.clear();
}

PUSERQUERYINFO CWinSockMgr::GetUserQuery(int nIndex)
{
	USERQUERYINFO_MAP_IT it = m_mapUserQuery.begin();

	for(int i = 0; it != m_mapUserQuery.end(); it++, i++)
	{
		if(i == nIndex)
			return &it->second;
	}	

	return 0;
}

int CWinSockMgr::UnknownedQuery(MSG_DATA msgData, CClientSock* pSock)
{
	USERQUERYINFO Query;

	Query.pSock = pSock;
	Query.nCommandData = m_MSGParser.m_msgData.msgHeader.nCommandData;

	return AddUserQuery(Query);

	// 서버 매니저로 쿼리 전송
	// 쿼리를 전송할 때 메시지 부분에 쿼리 맵 인덱스를 넣어서 보냄

	//MSG_ID_Check_Req(nIndex);   
}

void CWinSockMgr::KnownedQuery(MSG_DATA msgData)
{

}

void CWinSockMgr::ProcessQuery()
{
	USERQUERYINFO_MAP_IT it = m_mapUserQuery.begin();

	for( ; it != m_mapUserQuery.end(); it++)
	{
		//if(it->second.pSock == 
	}
}

void CWinSockMgr::OnAccept()
{
	CClientSock* pClientSock = new CClientSock;

	pClientSock->m_Tag = TAG_CLIENT;

	// 유저 클라이언트 접속 받음
	m_ServerSock.Accept(*pClientSock);

	CString strIP;	
	int nPort;

	pClientSock->GetPeerName(strIP, (UINT &) nPort);

	CString str;

	str.Format("SOCKET : [%d] - (%s : %d) 유저 접속됨", pClientSock->m_hSocket, strIP, nPort);
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, str.GetBuffer(0));

	USERINFO UserInfo;

	UserInfo.pSock = pClientSock;

	AddUser(UserInfo);

	str.Format("SOCKET : [%d] - (%s : %d) 유저 정보 생성 완료", pClientSock->m_hSocket, strIP, nPort);
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, str.GetBuffer(0));

	// 정해진 유저 수가 넘으면 접속을 취소한다
	if(m_mapUserInfo.size() >= MAX_CLIENT_COUNT) 
	{
		pClientSock->Send("ACCEPT_DENY", 16);

		pClientSock->Close();
		SAFE_DELETE(pClientSock);

		return;
	}
	else
	{
		pClientSock->Send("ACCEPT_OK", 16);
	}
}

MSG_RET CWinSockMgr::OnReceive(SOCKET Socket, int nTag)
{
	if(nTag == TAG_MAIN_SERVER)
	{
		return OnReceiveFromServerMgr(Socket);
	}
	else if(nTag == TAG_CLIENT)
	{
		return OnReceiveFromClient(Socket);
	}
}

MSG_RET CWinSockMgr::OnReceiveFromServerMgr(SOCKET Socket)
{
	char recv[512];

	int nRet = m_ServerMgrSock.Receive(recv, 512);

	if(nRet <= SOCKET_ERROR)
	{
		return MSG_RET_ERROR;
	}

	if(strlen(recv) <= 32)
	{
		if(strcmp(recv, "CONNECT_ACK") == 0)
		{
			g_sToolMgr.SetConnected(true);
			SetServerRun(true);

			g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 매니저에 접속 성공...");

			return MSG_CONNECT_SUCCESS;	
		}
		else
		{
			return MSG_CONNECT_FAIL;
		}
	}
	else 
	{
		m_MSGParser.ParseMSG(recv);

		return MSG_PARSING_DATA;
	}

	return MSG_RET_NONE;
}

MSG_RET CWinSockMgr::OnReceiveFromClient(SOCKET Socket)
{
	char recv[512];

	USERINFO_MAP_IT it = m_mapUserInfo.begin();
  
	for(int i = 0; it != m_mapUserInfo.end(); i++, it++)
	{
		if(it->second.pSock->m_hSocket != Socket) continue;

		int nRet = it->second.pSock->Receive(recv, 512);

		if(nRet <= SOCKET_ERROR)
		{
			return MSG_RET_ERROR;
		}

		if(strlen(recv) <= 32)
		{

		}
		else 
		{
			m_MSGParser.ParseMSG(recv);

			if(strcmp(m_MSGParser.m_msgData.msgHeader.szFromID, UNKNOWNED_USER) == 0)
			{
				sprintf(m_MSGParser.m_msgData.msgMessage, "%d", UnknownedQuery(m_MSGParser.m_msgData, it->second.pSock));
			}
			/*else
			{
				KnownedQuery(m_MSGParser.m_msgData);
			}*/

			m_CMDHandlerMgr.CMD_Main_Handle(m_MSGParser.m_msgData);

			return MSG_PARSING_DATA;
		}
	}

	return MSG_RET_NONE;
}