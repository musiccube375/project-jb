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
	USERINFO_MAP m_mapUserSock;			// User map for middle server

	char m_szServerMgrIP[32];
	bool m_bServerMgrConnect;

public:
	inline CServerSock* GetServerSock() { return &m_ServerSock; }

public:
	void InitServerSock();
	void CloseServerSock();

	bool ConnectToServerMgr();
	void CloseServerMgrSock();

public:
	HRESULT AddUser(USERINFO UserInfo);
	HRESULT DelUser(int nIndex);
	void ClearUser();

public:
	void OnAccept();

public:
	HRESULT InitWinSockMgr(char* pszServerMgrIP = LOCAL_HOST_IP);
	void ReleaseWinSockMgr();

public:
	// The basic constructor
	CWinSockMgr();

	// The basic destructor
	~CWinSockMgr();
};