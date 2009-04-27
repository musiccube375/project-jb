/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: WinSock Manager
	Version				: 1.00.01

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

	Release Date		: 2009. 04. 15.
	Version				: 1.00.01
*/

class CWinSockMgr
{
private:
	bool m_bServerRun;
	CServerSock m_ServerSock;			// Main Server Socket
	
	int	m_nClientSockCount;				// Client socket map counter
	CLIENTSOCK_MAP m_mapClientSock;		// Client socket map for middle server

public:
	inline CServerSock* GetServerSock() { return &m_ServerSock; }

public:
	void InitServerSock();
	void CloseServerSock();

public:
	HRESULT InitWinSockMgr();

public:
	// The basic constructor
	CWinSockMgr();

	// The basic destructor
	~CWinSockMgr();
};