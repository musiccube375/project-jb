/* 
	Author				: 김정훈(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: WinSock Manager
	Version				: 1.00.05

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	WinSock Manager Header

	2009 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "Common_Define.h"
#include "MSG_Parser.h"
#include "CMD_Handler.h"

/*
	Class : WinSock Manager Class

	Release Date		: 2009. 04. 15.
	Version				: 1.00.05
*/

class CWinSockMgr
{
private:
	bool m_bServerRun;
	CServerSock m_ServerSock;			// Main Server Socket
	
	int	m_nMServerCount;				// M-Server socket map counter
	MSERVERINFO_MAP m_mapMServer;		// M-Server socket map for middle server

	int m_nMSUserInfoCount;
	MSUSERINFO_MAP m_mapMSUserInfo;		// 메인 서버에 등록되는 유저들 정보

	CMSGParser m_MSGParser;
	CCMDHandlerMgr m_CMDHandlerMgr;

public:
	inline CServerSock* GetServerSock() { return &m_ServerSock; }
	inline int GetMSUserInfoCount() { return m_mapMSUserInfo.size(); }

public:
	void InitServerSock();
	void CloseServerSock();

public:
	HRESULT AddMServer(MSERVERINFO MServerInfo);
	HRESULT DelMServer(char* pszIP);
	void ClearMServer();

	HRESULT AddMSUserInfo(MSUSERINFO MSUserInfo);
	HRESULT DelMSUserInfo(const char* pszID);
	void ClearMSUserInfo();

public:
	HRESULT InitWinSockMgr();
	void ReleaseWinSockMgr();

	void OnAccept();
	void OnReceive(SOCKET Socket, int nTag);
	void OnClose(SOCKET Socket, int nTag);

public:
	// The basic constructor
	CWinSockMgr();

	// The basic destructor
	~CWinSockMgr();
};