// ServerSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatS.h"
#include "ServerSocket.h"
#include "ChatSDlg.h"

// CServerSocket

CServerSocket::CServerSocket()
{
}
CServerSocket::CServerSocket(CChatSDlg * dlg)
{
	m_pDlg = dlg;
}
CServerSocket::~CServerSocket()
{
}


// CServerSocket 멤버 함수입니다.

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_pDlg->OnAccept();

	CSocket::OnAccept(nErrorCode);
}

void CServerSocket::Init(CChatSDlg *dlg, int nPortNum)
{
	m_pDlg = dlg;
	Create(nPortNum); // 서버소켓생성
	Listen(); // 연결대기
}
