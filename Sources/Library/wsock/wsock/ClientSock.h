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

#define WM_CLIENT_RECEIVE		0x0002
#define WM_CLIENT_SEND			0x0003
#define WM_CLIENT_CONNECT		0x0004
#define WM_CLIENT_CLOSE			0x0005
#define WM_CLIENT_NETDOWN		0x0006
#define WM_CLIENT_SEND_ERROR	0x0007

class _DLL CClientSock : public CAsyncSocket
{
// Attributes
public:
	int		m_Tag;			// 소켓 정보를 위한 태그
	bool	m_bConnect;		// 접속 여부 확인

	HWND	m_hWnd;

// Operations
public:
	CClientSock();
	CClientSock(HWND hWnd);
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