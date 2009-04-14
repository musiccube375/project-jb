// ServerSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatC.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
: m_pWnd(NULL)
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 멤버 함수입니다.

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	m_pWnd->SendMessage(UM_ACCEPT);

	CSocket::OnAccept(nErrorCode);
}

void CServerSocket::Init(CWnd* pWnd, int nPortNum)
{
	m_pWnd=pWnd;
	Create(nPortNum);
	Listen();
}
