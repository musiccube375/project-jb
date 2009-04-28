/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 22.
	Project	Name		: WinSock Manager
	Version				: 1.00.02

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	WinSock Manager Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "Common_Define.h"
#include "MSG_Parser.h"

/*
	Structure : USER QUERY INFO Structure

	Release Date		: 2008. 04. 28.
	Version				: 1.00.00
*/

typedef struct _USERQUERYINFO
{
	CClientSock*	pSock;
	int nCommandData;
}USERQUERYINFO, *PUSERQUERYINFO;

typedef map<int, USERQUERYINFO>					USERQUERYINFO_MAP;
typedef map<int, USERQUERYINFO>::iterator		USERQUERYINFO_MAP_IT;
typedef map<int, USERQUERYINFO>::value_type		USERQUERYINFO_MAP_VALUE;

/*
	Class : WinSock Manager Class

	Release Date		: 2009. 04. 22.
	Version				: 1.00.02
*/

class CWinSockMgr
{
private:
	bool m_bServerRun;
	CServerSock m_ServerSock;			// Main Server Socket
	
	CClientSock m_ServerMgrSock;		// The socket for connecting to server manager

	int	m_nUserCount;					// User map counter
	USERINFO_MAP m_mapUserInfo;			// User map for middle server

	char m_szServerMgrIP[32];
	bool m_bServerMgrConnect;

	CMSGParser m_MSGParser;

	int m_nUserQueryCount;
	USERQUERYINFO_MAP m_mapUserQuery;

public:
	inline CServerSock* GetServerSock() { return &m_ServerSock; }
	inline bool IsServerRun() { return m_bServerRun; }

	void SetServerRun(bool bServerRun);

public:
	void InitServerSock();
	void CloseServerSock();

	bool ConnectToServerMgr(const char* pszIP);
	void CloseServerMgrSock();

public:
	HRESULT AddUser(USERINFO UserInfo);
	HRESULT DelUser(int nIndex);
	void ClearUser();

	HRESULT AddUserQuery(USERQUERYINFO UserQuery);
	HRESULT DelUserQuery();
	void ClearUserQuery();

	void ProcessQuery();

public:
	void OnAccept();
	MSG_RET OnReceive(SOCKET Socket, int nTag);

protected:
	MSG_RET OnReceiveFromServerMgr(SOCKET Socket);
	MSG_RET OnReceiveFromClient(SOCKET Socket);

public:
	HRESULT InitWinSockMgr(const char* pszServerMgrIP = LOCAL_HOST_IP);
	void ReleaseWinSockMgr();

public:
	// The basic constructor
	CWinSockMgr();

	// The basic destructor
	~CWinSockMgr();
};