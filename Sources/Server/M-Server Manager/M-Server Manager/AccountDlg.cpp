// AccountDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "M-Server Manager.h"
#include "AccountDlg.h"


// CAccountDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAccountDlg, CDialogSkin)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialogSkin(CAccountDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CAccountDlg::~CAccountDlg()
{
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSkin::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editUserID);
	DDX_Control(pDX, IDC_EDIT2, m_editUserPasswords);
	DDX_Control(pDX, IDC_EDIT3, m_editAccountID);
	DDX_Control(pDX, IDC_EDIT4, m_editPasswords);
	DDX_Control(pDX, IDC_EDIT7, m_editPasswords2);
}


BEGIN_MESSAGE_MAP(CAccountDlg, CDialogSkin)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOMMAND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CAccountDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CAccountDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CAccountDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CAccountDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CAccountDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT7, &CAccountDlg::OnEnChangeEdit7)
END_MESSAGE_MAP()


// CAccountDlg 메시지 처리기입니다.

void CAccountDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogSkin::OnPaint()을(를) 호출하지 마십시오.

	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogSkin::OnPaint();
	}
}

BOOL CAccountDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogSkin::OnEraseBkgnd(pDC);
}

BOOL CAccountDlg::OnInitDialog()
{
	CDialogSkin::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAccountDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogSkin::OnSysCommand(nID, lParam);
}

HBRUSH CAccountDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	/*HBRUSH hbr = CDialogSkin::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;*/

	pDC->SetBkMode(TRANSPARENT); 

	HBRUSH hbr = CDialogSkin::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	int nRet = pWnd->GetDlgCtrlID();

	if(nRet == IDC_STATIC)
	{
		CRect rc;
		//m_chkboxRefresh.GetClientRect(rc);

		//pDC->BitBlt(0, 0, rc.right - rc.left, rc.bottom - rc.top, pWnd->GetDC(), rc.left, rc.top, SRCCOPY);
		//HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);

		pDC->SetTextColor(RGB(255, 255, 255));
		//pDC->SetBkColor(RGB(255, 255, 255));

		hbr = (HBRUSH) GetStockObject(NULL_BRUSH);
		SetBkMode(pDC->m_hDC, TRANSPARENT);

		//return (HBRUSH) hBrush;
	}
	else if(nRet == IDC_STATIC_ACCOUNT ||
		    nRet == IDC_STATIC_NEW_ACCOUNT)
	{
		//pDC->SetTextColor(RGB(255, 255, 255));

		//hbr = (HBRUSH) GetStockObject(NULL_BRUSH);
		//SetBkMode(pDC->m_hDC, TRANSPARENT);

		SetTextColor(pDC->m_hDC, RGB(0, 128, 255));
		SetBkMode(pDC->m_hDC, TRANSPARENT);
		//hbr = (HBRUSH) GetStockObject(WHITE_BRUSH);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CAccountDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strID, strPW;

	m_editUserID.GetWindowTextA(strID);
	m_editUserPasswords.GetWindowTextA(strPW);

	if(strID == "")
	{
		AfxMessageBox("Enter the ID");
		return;
	}

	if(!g_sToolMgr.GetSQLMgr()->IsValidIDFromDB(strID))
	{
		AfxMessageBox("Cannot find ID");
	}
	else
	{
		if(!g_sToolMgr.GetSQLMgr()->IsValidPWFromDB(strID, strPW))
			AfxMessageBox("Incorrect passwords");
		else
		{
			CString strID;
			m_editUserID.GetWindowTextA(strID);

			g_sToolMgr.GetDialogMgr()->m_StatusDlg.OnRun(strID);

			g_sToolMgr.SetUserID(strID.GetBuffer(0));
			g_sToolMgr.SetAccountActived(true);

			g_sToolMgr.SetRun(true);

			OnOK();
		}
	}
}

void CAccountDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogSkin::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_editUserID.Invalidate();
}

void CAccountDlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogSkin::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_editUserPasswords.Invalidate();
}

void CAccountDlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogSkin::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_editAccountID.Invalidate();
}

void CAccountDlg::OnEnChangeEdit4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogSkin::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_editPasswords.Invalidate();
}

void CAccountDlg::OnEnChangeEdit7()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogSkin::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_editPasswords2.Invalidate();
}
