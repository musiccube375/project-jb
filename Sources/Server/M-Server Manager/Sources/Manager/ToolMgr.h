/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Tool Manager
	Version				: 1.00.02

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Tool Manager Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "Log.h"
#include "WinSockMgr.h"
#include "DialogMgr.h"
#include "SQLMgr.h"

/*
	Class : Tool Manager Class

	Release Date		: 2008. 04. 15.
	Version				: 1.00.02
*/

class CToolMgr
{
private:
	HWND m_hWnd;
	bool m_bRun;

	char m_szUserID[256];
	bool m_AccountActived;

	CLog m_Log;
	CWinSockMgr m_WinSockMgr;
	CDialogMgr m_DialogMgr;
	CSQLMgr m_SQLMgr;

public:
	inline HWND GethWnd() { return m_hWnd; }
	inline bool GetRun() { return m_bRun; }

	inline CLog* GetLog() { return &m_Log; }
	inline CWinSockMgr* GetWinSockMgr() { return &m_WinSockMgr; }
	inline CDialogMgr* GetDialogMgr() { return &m_DialogMgr; }
	inline CSQLMgr* GetSQLMgr() { return &m_SQLMgr; }

	inline char* GetUserID() { return m_szUserID; }

public:
	void SetLogView(bool bLogView);
	void SetRun(bool bRun);

	void SetUserID(char* szID);
	void SetAccountActived(bool bActive);

public:
	bool IsAccountActived();

public:
	void InitVariable();
	HRESULT	InitToolMgr(HWND hWnd);
	void ReleaseToolMgr();
};