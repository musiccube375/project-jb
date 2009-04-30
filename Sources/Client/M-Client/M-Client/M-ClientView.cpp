
// M-ClientView.cpp : CMClientView 클래스의 구현
//

#include "stdafx.h"
#include "M-Client.h"

#include "M-ClientDoc.h"
#include "M-ClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CMClientView::CheckMSG(MSG_RET ret)
{
	if(ret == MSG_CONNECT_FAIL)
	{
		AfxMessageBox("서버 접속에 실패하였습니다.");
		g_sToolMgr.m_bConnected = false;
	}
	else if(ret == MSG_CONNECT_SUCCESS)
	{
		AfxMessageBox("서버 접속에 성공하였습니다.");
		g_sToolMgr.m_bConnected = true;
	}
	else if(ret == MSG_RET_ERROR)
	{
		AfxMessageBox("받은 메시지 형식이 이상합니다.");
	}
	else if(ret == MSG_PARSING_ID_CHECK_OK)
	{
		AfxMessageBox("사용 가능합니다.");
		g_sToolMgr.GetDialogMgr()->m_RegisterNewUserDlg.m_bCheckID = true;
	}
	else if(ret == MSG_PARSING_ID_CHECK_FAIL)
	{
		AfxMessageBox("이미 같은 ID가 존재합니다.");
		g_sToolMgr.GetDialogMgr()->m_RegisterNewUserDlg.m_bCheckID = false;
	}
	else if(ret == MSG_PARSING_ADD_ID_OK)
	{
		AfxMessageBox("새로운 계정 생성을 성공하였습니다.");
	}
	else if(ret == MSG_PARSING_ADD_ID_FAIL)
	{
		AfxMessageBox("새로운 계정 생성에 실패하였습니다.");
	}
	else if(ret == MSG_PARSING_LOGIN_OK)
	{
		AfxMessageBox("로그인에 성공하였습니다.");

		CString strID;

		m_editID.GetWindowTextA(strID);
		g_sToolMgr.SetLoginID(strID.GetBuffer(0));

		SetLoginStatus(false);
	}
	else if(ret == MSG_PARSING_LOGIN_FAIL)
	{
		AfxMessageBox("아이디 또는 비밀번호가 틀렸습니다.");
	}
}

// CMClientView

IMPLEMENT_DYNCREATE(CMClientView, CFormView)

BEGIN_MESSAGE_MAP(CMClientView, CFormView)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT1, &CMClientView::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMClientView::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMClientView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMClientView::OnBnClickedButton2)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_MESSAGE(WM_CLIENT_RECEIVE, OnClientReceive)
	ON_MESSAGE(WM_CLIENT_CONNECT, OnClientConnect)
	ON_MESSAGE(WM_CLIENT_CLOSE, OnClientClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CMClientView::OnBnClickedButton3)
	ON_COMMAND(ID_32771, &CMClientView::OnLogOut)
END_MESSAGE_MAP()

// CMClientView 생성/소멸

CMClientView::CMClientView()
	: CFormView(CMClientView::IDD)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMClientView::~CMClientView()
{
	MSG_Exit_Server_Req(g_sToolMgr.GetLoginID());
	g_sToolMgr.ReleaseToolMgr();
}

void CMClientView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editID);
	DDX_Control(pDX, IDC_EDIT2, m_editPW);
	DDX_Control(pDX, IDC_BUTTON1, m_btnRegisterID);
	DDX_Control(pDX, IDC_BUTTON2, m_CheckID);
	DDX_Control(pDX, IDC_CHECK2, m_chkboxRememberID);
	DDX_Control(pDX, IDC_CHECK1, m_chkboxOffline);
	DDX_Control(pDX, IDC_BUTTON3, m_btnLogin);
}

BOOL CMClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMClientView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CRect rcClient;
	GetClientRect(&rcClient);
	GetParentFrame()->RecalcLayout();
	// 스크롤 크기를 뷰의 크기로 맞추어 줌.
	SetScaleToFitSize(rcClient.Size());

	m_Brush.CreateSolidBrush(RGB(192, 192, 192)); 

	Init();
	SetLoginStatus(true);
}

void CMClientView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMClientView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMClientView 진단

#ifdef _DEBUG
void CMClientView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMClientView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMClientDoc* CMClientView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMClientDoc)));
	return (CMClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CMClientView 메시지 처리기

HBRUSH CMClientView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	int nRet = pWnd->GetDlgCtrlID();

	if(nRet == IDC_STATIC_ID ||
	   nRet == IDC_STATIC_PASSWORDS)
	{
		pDC->SetTextColor(RGB(32, 32, 32));

		hbr = (HBRUSH) GetStockObject(NULL_BRUSH);
		SetBkMode(pDC->m_hDC, TRANSPARENT);
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;

	//return m_Brush;
}

void CMClientView::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMClientView::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMClientView::SetLoginStatus(bool bLogin)
{
	if(!bLogin)
	{
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_PASSWORDS)->ShowWindow(false);

		m_editID.ShowWindow(false);
		m_editPW.ShowWindow(false);

		m_btnRegisterID.ShowWindow(false);
		m_CheckID.ShowWindow(false);
		m_btnLogin.ShowWindow(false);

		m_chkboxOffline.ShowWindow(false);
		m_chkboxRememberID.ShowWindow(false);

		GetDlgItem(IDC_STATIC_LOGIN_ID)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_LOGIN_ID)->SetWindowTextA(g_sToolMgr.GetLoginID());
	}
	else
	{
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_PASSWORDS)->ShowWindow(true);

		m_editID.ShowWindow(true);
		m_editPW.ShowWindow(true);

		m_editPW.SetWindowTextA("");

		m_btnRegisterID.ShowWindow(true);
		m_CheckID.ShowWindow(true);
		m_btnLogin.ShowWindow(true);

		m_chkboxOffline.ShowWindow(true);
		m_chkboxRememberID.ShowWindow(true);

		GetDlgItem(IDC_STATIC_LOGIN_ID)->ShowWindow(false);
	}
}

void CMClientView::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// Register ID
	g_sToolMgr.GetDialogMgr()->m_RegisterNewUserDlg.DoModal();
}

void CMClientView::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BOOL CMClientView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
	GetClientRect(rt);

	pDC->FillSolidRect(rt, RGB(192, 192, 192));

	return true;

	//return CFormView::OnEraseBkgnd(pDC);
}

void CMClientView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	//RECT rt;

	//GetClientRect(&rt);
	////GetWindowRect(GetDesktopWindow(), &rt);

	//int nWidth = rt.right - rt.left;
	//int nHeight = rt.bottom - rt.top;

	//int nX = rt.left + nWidth / 2 - (CFG_DIALOG_WIDTH / 2);

	RePositionControl(cx, cy);
}

void CMClientView::RePositionControl(int x, int y)
{
	if(GetDlgItem(IDC_STATIC_ID) != NULL)
	GetDlgItem(IDC_STATIC_ID)->SetWindowPos(NULL, IDC_ID_AXIS_X*x, 
		IDC_ID_AXIS_Y*y, 0, 0, SWP_NOSIZE);
	/*GetDlgItem(IDC_STATIC_PASSWORDS	)->SetWindowPos(	NULL, , , 0, 0, SWP_NOSIZE);*/
	//GetDlgItem(IDC_EDIT1				)->SetWindowPos(	NULL, , , 0, 0, SWP_NOSIZE);
	//GetDlgItem(IDC_EDIT2				)->SetWindowPos(	NULL, , , 0, 0, SWP_NOSIZE);
	//GetDlgItem(IDC_CHECK2				)->SetWindowPos(	NULL, , , 0, 0, SWP_NOSIZE);
	//GetDlgItem(IDC_CHECK1				)->SetWindowPos(	NULL, , , 0, 0, SWP_NOSIZE);
	//GetDlgItem(IDC_BUTTON3			)->SetWindowPos(	NULL, , , 0, 0, SWP_NOSIZE);
	//GetDlgItem(IDC_BUTTON1			)->SetWindowPos(	NULL, , , 0, 0, SWP_NOSIZE);
	//GetDlgItem(IDC_BUTTON2			)->SetWindowPos(	NULL, , , 0, 0, SWP_NOSIZE);

}

LRESULT CMClientView::OnClientReceive(WPARAM wParam, LPARAM lParam)
{
	MSG_RET ret = g_sToolMgr.GetWinSockMgr()->OnReceive((SOCKET) wParam, (int) lParam);

	CheckMSG(ret);

	return S_OK;
}

LRESULT CMClientView::OnClientConnect(WPARAM wParam, LPARAM lParam)
{

	return S_OK;
}

LRESULT CMClientView::OnClientClose(WPARAM wParam, LPARAM lParam)
{

	return S_OK;
}

void CMClientView::Init()
{
	g_sToolMgr.InitToolMgr(m_hWnd);//Log 기록

	LoadServerConfig();

	SetTimer(1, 1000, NULL);//서버 접속
}

HRESULT CMClientView::LoadServerConfig()
{
	/*char buff[256];
	char temp[256];

	GetStringFromConfig("Server_Config", "INFO", "COUNT", buff);

	for(int i = 0; i < atoi(buff); i++)
	{
		sprintf(temp, "SERVER#%d", i + 1);

		GetStringFromConfig("Server_Config", "LISTS", temp, buff);

		strcpy(g_sToolMgr.m_ServerList[i].szServerIP, buff);
	}*/

	strcpy(g_sToolMgr.m_ServerList[0].szServerIP, "127.0.0.1");

	return S_OK;
}

void CMClientView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if(!g_sToolMgr.m_bConnected)
	{
		g_sToolMgr.GetWinSockMgr()->ConnectToServer();
	}

	CFormView::OnTimer(nIDEvent);
}

void CMClientView::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here

	// Login

	CString strID, strPW;

	m_editID.GetWindowTextA(strID);
	m_editPW.GetWindowTextA(strPW);

	if(strID == "")
	{
		AfxMessageBox("아이디를 입력하십시요.");
		return;
	}
	else if(strPW == "")
	{
		AfxMessageBox("비밀번호를 입력하십시요.");
		return;
	}

	MSG_Login_Req(strID.GetBuffer(0), strPW.GetBuffer(0));
}

void CMClientView::OnLogOut()
{
	// TODO: Add your command handler code here

	MSG_Exit_Server_Req(g_sToolMgr.GetLoginID());
	// 로그아웃시의 적절한 요청 메시지 작성 필요
	SetLoginStatus(true);
}
