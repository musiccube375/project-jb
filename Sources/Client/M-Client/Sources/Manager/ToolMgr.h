/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Tool Manager
	Version				: 1.00.00

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

/*
	Class : Tool Manager Class

	Release Date		: 2008. 04. 15.
	Version				: 1.00.00
*/

class CToolMgr
{
private:
	HWND m_hWnd;

	CLog m_Log;
	CWinSockMgr m_WinSockMgr;
	CDialogMgr m_DialogMgr;

public:
	inline HWND GethWnd() { return m_hWnd; }

	inline CLog* GetLog() { return &m_Log; }
	inline CWinSockMgr* GetWinSockMgr() { return &m_WinSockMgr; }
	inline CDialogMgr* GetDialogMgr() { return &m_DialogMgr; }

public:
	void SetLogView(bool bLogView);

public:
	HRESULT	InitToolMgr(HWND hWnd);
	void ReleaseToolMgr();
};