/* 
	Author				: Bill Kim (kjh_900@hanmail.net, kjh_900@hotmail.com, BillKim@joyon.com)	
	Release Date		: 2009. 04. 08.
	File Name			: Client Socket
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 3.4 Ghz, RAM - 2 GB Graphic - NVIDIA Geforce 7800 GT
	Test OS				: Windows XP Home Professional + SP2
	Test Application	: Visual Studio 2003 + DirectX SDK 9.0c(Dec, 2006)
	
	Contents

	Client Socket Header

	2009 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/ 

#pragma once

#include "afxsock.h"

#define WM_CLIENT_RECEIVE		WM_USER + 1
#define WM_CLIENT_SEND			WM_USER + 2
#define WM_CLIENT_CONNECT		WM_USER + 3
#define WM_CLIENT_CLOSE			WM_USER + 4
#define WM_CLIENT_NETDOWN		WM_USER + 5
#define WM_CLIENT_SEND_ERROR	WM_USER + 6

HWND g_ClienthWnd;

class _DLL CClientSock : public CAsyncSocket
{
// Attributes
public:
	int		m_Tag;			// 소켓 정보를 위한 태그
	bool	m_bConnect;		// 접속 여부 확인

// Operations
public:
	CClientSock();
	virtual ~CClientSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSock)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};