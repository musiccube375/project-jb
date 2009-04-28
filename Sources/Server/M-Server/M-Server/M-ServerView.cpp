
// M-ServerView.cpp : CMServerView 클래스의 구현
//

#include "stdafx.h"
#include "M-Server.h"

#include "M-ServerDoc.h"
#include "M-ServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMServerView

IMPLEMENT_DYNCREATE(CMServerView, CFormView)

BEGIN_MESSAGE_MAP(CMServerView, CFormView)
	ON_MESSAGE(WM_CLIENT_RECEIVE, OnClientReceive)
	ON_MESSAGE(WM_CLIENT_CONNECT, OnClientConnect)
	ON_MESSAGE(WM_CLIENT_CLOSE, OnClientClose)
	ON_MESSAGE(WM_SERVER_ACCEPT, OnClientAccept)
	ON_BN_CLICKED(IDC_BUTTON1, &CMServerView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMServerView::OnBnClickedButton2)
END_MESSAGE_MAP()

// CMServerView 생성/소멸

CMServerView::CMServerView()
	: CFormView(CMServerView::IDD)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMServerView::~CMServerView()
{
	g_sToolMgr.ReleaseToolMgr();
}

void CMServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editIP);
	DDX_Control(pDX, IDC_BUTTON1, m_btnConnect);
	DDX_Control(pDX, IDC_BUTTON2, m_btnDisconnect);
}

BOOL CMServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CRect rcClient;
	GetClientRect(&rcClient);
	GetParentFrame()->RecalcLayout();
	// 스크롤 크기를 뷰의 크기로 맞추어 줌.
	SetScaleToFitSize(rcClient.Size());

	Init();
	InitControls();
}

void CMServerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMServerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMServerView 진단

#ifdef _DEBUG
void CMServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMServerDoc* CMServerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMServerDoc)));
	return (CMServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMServerView 메시지 처리기

LONG CMServerView::OnClientReceive(UINT wParam, LONG lParam)
{
	MSG_RET ret = g_sToolMgr.GetWinSockMgr()->OnReceive((SOCKET) wParam, (int) lParam);

	if(ret == MSG_CONNECT_SUCCESS)
	{
		m_editIP.EnableWindow(false);
		m_btnConnect.EnableWindow(false);
		m_btnDisconnect.EnableWindow(true);
	}

	return S_OK;
}

LONG CMServerView::OnClientConnect(UINT wParam, LONG lParam)
{
	/*g_sToolMgr.SetConnected(true);
	g_sToolMgr.GetWinSockMgr()->SetServerRun(true);

	m_btnConnect.EnableWindow(false);
	m_btnDisconnect.EnableWindow(true);

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 매니저에 접속 성공...");*/

	return S_OK;
}

LONG CMServerView::OnClientClose(UINT wParam, LONG lParam)
{
	/*g_sToolMgr.SetConnected(false);
	g_sToolMgr.GetWinSockMgr()->SetServerRun(false);

	m_btnConnect.EnableWindow(true);
	m_btnDisconnect.EnableWindow(false);

	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_CONN, "서버 매니저에 접속 실패...");*/

	return S_OK;
}

LONG CMServerView::OnClientAccept(UINT wParam, LONG lParam)
{
	//if(!g_sToolMgr.IsConnected()) return E_FAIL;

	g_sToolMgr.GetWinSockMgr()->OnAccept();

	return S_OK;
}

LONG CMServerView::OnClientNetDown(UINT wParam, LONG lParam)
{

	return S_OK;
}

void CMServerView::Init()
{
	g_sToolMgr.InitToolMgr(m_hWnd, LOCAL_HOST_IP);
}

void CMServerView::InitControls()
{
	m_editIP.SetWindowTextA("127.0.0.1");
	m_btnConnect.EnableWindow(true);
	m_btnDisconnect.EnableWindow(false);
}

void CMServerView::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	// Connect to the M-Server Manager

	CString strIP;
	m_editIP.GetWindowTextA(strIP);

	g_sToolMgr.GetWinSockMgr()->ConnectToServerMgr(strIP);

	//g_sToolMgr.GetWinSockMgr()->GetServerSock()->Connect(strIP, MAIN_SERVER_PORT);
}

void CMServerView::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	// Disconnect to the M-Server Manager

	g_sToolMgr.GetWinSockMgr()->CloseServerMgrSock();

	m_editIP.EnableWindow(true);
	m_btnConnect.EnableWindow(true);
	m_btnDisconnect.EnableWindow(false);
}
