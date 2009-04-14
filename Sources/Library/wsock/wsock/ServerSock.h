/* 
	Author				: Bill Kim (kjh_900@hanmail.net, kjh_900@hotmail.com, BillKim@joyon.com)	
	Release Date		: 2009. 04. 08.
	File Name			: Server Socket
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 3.4 Ghz, RAM - 2 GB Graphic - NVIDIA Geforce 7800 GT
	Test OS				: Windows XP Home Professional + SP2
	Test Application	: Visual Studio 2003 + DirectX SDK 9.0c(Dec, 2006)
	
	Contents

	Server Socket Header

	2009 ¨Ï Copyright MIS Corporation. All Rights Reserved.
*/ 

#pragma once

#include "afxsock.h"

#define WM_SERVER_ACCEPT	WM_USER + 0

HWND g_ServerhWnd;

class _DLL CServerSock : public CAsyncSocket
{
// Operations
public:
	CServerSock();
	virtual ~CServerSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSock)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};
