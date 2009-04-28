// RegisterNewUserDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "M-Client.h"
#include "RegisterNewUserDlg.h"


// CRegisterNewUserDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRegisterNewUserDlg, CDialog)

CRegisterNewUserDlg::CRegisterNewUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterNewUserDlg::IDD, pParent)
{
	m_bCheckID = false;
}

CRegisterNewUserDlg::~CRegisterNewUserDlg()
{
}

void CRegisterNewUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editID);
	DDX_Control(pDX, IDC_EDIT2, m_editPasswords);
	DDX_Control(pDX, IDC_EDIT3, m_editPasswords2);
}


BEGIN_MESSAGE_MAP(CRegisterNewUserDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegisterNewUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CRegisterNewUserDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRegisterNewUserDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &CRegisterNewUserDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CRegisterNewUserDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CRegisterNewUserDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CRegisterNewUserDlg 메시지 처리기입니다.

void CRegisterNewUserDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	// Check ID
	MSG_ID_Check_Req();
}

void CRegisterNewUserDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	if(!g_sToolMgr.m_bConnected) return;

	/*char msg[256];

	MSG_Generator(msg, UNKNOWNED_USER, UNKNOWNED_USER, MSG_CLIENT_TO_MIDDLE, 
		          CLIENT_CMD, CC_ADD_ID_REQ_TO_MIDDLE);

	g_sToolMgr.GetWinSockMgr()->GetServerSock()->Send(msg, strlen(msg));*/

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
