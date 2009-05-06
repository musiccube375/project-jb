/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: WinSock Manager
	Version				: 1.00.03

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
#include "CMD_Handler.h"

/*
	Class : WinSock Manager Class

	Release Date		: 2009. 04. 15.
	Version				: 1.00.03
*/

class CWinSockMgr
{
private:
	bool m_bConnectTry;					// ¡¢º” Ω√µµ ø©∫Œ	

	bool m_bConnected;
	CClientSock	m_ServerSock;			// The server socket to connect

	CMSGParser m_MSGParser;
	CCMDHandlerMgr m_CMDHandlerMgr;

public:
	int m_nServerCount;					// º≠πˆ¿« ¿Œµ¶Ω∫

public:
	inline CClientSock* GetServerSock() { return &m_ServerSock; }
	inline int GetServerCount() { return m_nServerCount; }
	inline CMSGParser* GetMSGParser() { return &m_MSGParser; }

public:
	bool ConnectToServer();
	void CloseServerSock();

public:
	HRESULT InitWinSockMgr();
	void ReleaseWinSockMgr();

public:
	MSG_RET OnReceive(SOCKET Socket, int nTag);

public:
	// The basic constructor
	CWinSockMgr();

	// The basic destructor
	~CWinSockMgr();
};