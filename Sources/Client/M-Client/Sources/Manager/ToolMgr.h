/* 
	Author				: 김정훈(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Tool Manager
	Version				: 1.00.04

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Tool Manager Header

	2009 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "Log.h"
#include "WinSockMgr.h"
#include "DialogMgr.h"
#include "BasicConfig.h"

#define MAX_SERVER_LIST		64

typedef struct _SERVERLIST
{
	char	szServerIP[64];
}SERVERLIST, *PSERVERLIST;

/*
	Class : Tool Manager Class

	Release Date		: 2009. 04. 15.
	Version				: 1.00.04
*/

class CToolMgr
{
private:
	HWND m_hWnd;
	
	CLog m_Log;
	CWinSockMgr m_WinSockMgr;
	CDialogMgr m_DialogMgr;

public:
	bool m_bConnected;
	char m_ServerIP[64];
	SERVERLIST m_ServerList[MAX_SERVER_LIST];	// 서버 아이피 리스트

private:
	char m_szLoginID[64];
	USER_STATE m_UserState;	// 유저 상태

public:
	inline HWND GethWnd() { return m_hWnd; }

	inline CLog* GetLog() { return &m_Log; }
	inline CWinSockMgr* GetWinSockMgr() { return &m_WinSockMgr; }
	inline CDialogMgr* GetDialogMgr() { return &m_DialogMgr; }

	inline char* GetServerIP() { return m_ServerIP; }
	inline char* GetLoginID() { return m_szLoginID; }

public:
	void SetLogView(bool bLogView);

	void SetLoginID(const char* pszID);
	void SetUserState(USER_STATE UserState);

public:
	HRESULT	InitToolMgr(HWND hWnd);
	void ReleaseToolMgr();
};