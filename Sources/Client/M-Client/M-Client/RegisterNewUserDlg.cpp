// RegisterNewUserDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "M-Client.h"
#include "RegisterNewUserDlg.h"


// CRegisterNewUserDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRegisterNewUserDlg, CDialogSkin)

CRegisterNewUserDlg::CRegisterNewUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogSkin(CRegisterNewUserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CRegisterNewUserDlg::~CRegisterNewUserDlg()
{
}

void CRegisterNewUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSkin::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editID);
	DDX_Control(pDX, IDC_EDIT2, m_editPasswords);
	DDX_Control(pDX, IDC_EDIT3, m_editPasswords2);
}


BEGIN_MESSAGE_MAP(CRegisterNewUserDlg, CDialogSkin)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegisterNewUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CRegisterNewUserDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRegisterNewUserDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &CRegisterNewUserDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CRegisterNewUserDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CRegisterNewUserDlg::OnEnChangeEdit3)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOMMAND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRegisterNewUserDlg 메시지 처리기입니다.

void CRegisterNewUserDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	// Check ID

	CString strID;
	m_editID.GetWindowTextA(strID);

	if(strID == "") 
	{
		AfxMessageBox("ID 를 입력하십시요.");
		return;
	}

	MSG_ID_Check_Req(strID.GetBuffer(0));

	//m_bCheckID = true;
}

void CRegisterNewUserDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	// 계정 추가

	if(!g_sToolMgr.m_bConnected) return;
	
	if(!m_bCheckID)
	{
		AfxMessageBox("ID 체크를 하십시요.");
		return;
	}

	CString strID;
	CString strPW1, strPW2;

	m_editID.GetWindowTextA(strID);
	m_editPasswords.GetWindowTextA(strPW1);
	m_editPasswords2.GetWindowTextA(strPW2);

	if(strPW1 == "")
	{
		AfxMessageBox("비밀번호를 입력하세요.");
		return;
	}

	if(strPW1 != strPW2)
	{
		AfxMessageBox("비밀번호가 맞지 않습니다.");
		return;
	}

	MSG_Add_ID_Req(strID.GetBuffer(0), strPW1.GetBuffer(0));

	OnOK();
}

void CRegisterNewUserDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CRegisterNewUserDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	m_bCheckID = false;
	m_editID.Invalidate();
}

void CRegisterNewUserDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	m_editPasswords.Invalidate();
}

void CRegisterNewUserDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	m_editPasswords2.Invalidate();
}

BOOL CRegisterNewUserDlg::OnInitDialog()
{
	CDialogSkin::OnInitDialog();

	// TODO:  Add extra initialization here

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_bCheckID = false;
	m_editPasswords.SetLimitText(MAX_PASSWORD_SIZE);
	m_editPasswords2.SetLimitText(MAX_PASSWORD_SIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRegisterNewUserDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogSkin::OnPaint() for painting messages

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

BOOL CRegisterNewUserDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogSkin::OnEraseBkgnd(pDC);
}

void CRegisterNewUserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogSkin::OnSysCommand(nID, lParam);
}

HBRUSH CRegisterNewUserDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

		pDC->SetTextColor(RGB(255, 255, 255));

		hbr = (HBRUSH) GetStockObject(NULL_BRUSH);
		SetBkMode(pDC->m_hDC, TRANSPARENT);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}