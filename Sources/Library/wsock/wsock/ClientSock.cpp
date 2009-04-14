// ClientSock.cpp : implementation file
//

#include "stdafx.h"
#include "ClientSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSock

CClientSock::CClientSock()
{
	m_bConnect = false;
	m_Tag = -1;
}

CClientSock::~CClientSock()
{
	
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSock member functions

void CClientSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(nErrorCode == 0) SendMessage(g_ClienthWnd, WM_CLIENT_RECEIVE, (WPARAM) m_hSocket, (LPARAM) m_Tag);
	else if(nErrorCode == WSAENETDOWN)
	{
		SendMessage(g_ClienthWnd, WM_CLIENT_NETDOWN, (WPARAM) m_hSocket, (LPARAM) m_Tag);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSock::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(nErrorCode == 0) SendMessage(g_ClienthWnd, WM_CLIENT_SEND, (WPARAM) m_hSocket, (LPARAM) m_Tag);
	else if(nErrorCode == WSAENETDOWN)
	{
		SendMessage(g_ClienthWnd, WM_CLIENT_SEND_ERROR, (WPARAM) m_hSocket, (LPARAM) m_Tag);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSock::OnConnect(int nErrorCode) 
{
	if(nErrorCode == 0) 
	{
		SendMessage(g_ClienthWnd, WM_CLIENT_CONNECT, (WPARAM) m_hSocket, 0);

		m_bConnect = true;
	}
	//else m_bConnect = false;

	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSock::OnClose(int nErrorCode) 
{
	if(nErrorCode == 0) 
	{
		SendMessage(g_ClienthWnd, WM_CLIENT_CLOSE, (WPARAM) m_hSocket, (LPARAM) m_Tag);

		m_bConnect = false;
	}

	CAsyncSocket::OnClose(nErrorCode);
}