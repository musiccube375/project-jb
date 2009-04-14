// ServerSock.cpp : implementation file
//

#include "stdafx.h"
#include "ServerSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSock

CServerSock::CServerSock()
{
}

CServerSock::~CServerSock()
{

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CServerSock) 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSock member functions

void CServerSock::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(nErrorCode == 0) SendMessage(g_ServerhWnd, WM_SERVER_ACCEPT, (WPARAM) m_hSocket, 0);

	CAsyncSocket::OnAccept(nErrorCode);
}
