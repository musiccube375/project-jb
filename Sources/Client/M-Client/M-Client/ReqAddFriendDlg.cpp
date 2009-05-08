// ReqAddFriendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "M-Client.h"
#include "ReqAddFriendDlg.h"


// CReqAddFriendDlg dialog

IMPLEMENT_DYNAMIC(CReqAddFriendDlg, CDialogSkin)

CReqAddFriendDlg::CReqAddFriendDlg(CWnd* pParent /*=NULL*/)
	: CDialogSkin(CReqAddFriendDlg::IDD, pParent)
{

}

CReqAddFriendDlg::~CReqAddFriendDlg()
{
}

void CReqAddFriendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSkin::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_editMessage);
	DDX_Control(pDX, IDOK, m_btnAccept);
	DDX_Control(pDX, IDCANCEL, m_btnDeny);
	DDX_Control(pDX, IDC_BUTTON1, m_btnLater);
}


BEGIN_MESSAGE_MAP(CReqAddFriendDlg, CDialogSkin)
	ON_BN_CLICKED(IDOK, &CReqAddFriendDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReqAddFriendDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CReqAddFriendDlg::OnBnClickedLater)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT2, &CReqAddFriendDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CReqAddFriendDlg message handlers

void CReqAddFriendDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	g_sToolMgr.GetDialogMgr()->DestroyReqAddFriendDlg();

	MSG_Update_Friend_Req(g_sToolMgr.GetLoginID(), m_szReqID, true, false);

	//OnOK();
}

void CReqAddFriendDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	MSG_Delete_Friend_Req(g_sToolMgr.GetLoginID(), m_szReqID);

	g_sToolMgr.GetDialogMgr()->DestroyReqAddFriendDlg();

	//OnCancel();
}

void CReqAddFriendDlg::OnBnClickedLater()
{
	// TODO: Add your control notification handler code here

	g_sToolMgr.GetDialogMgr()->DestroyReqAddFriendDlg();
}

BOOL CReqAddFriendDlg::OnInitDialog()
{
	CDialogSkin::OnInitDialog();

	// TODO:  Add extra initialization here

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CReqAddFriendDlg::OnPaint()
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

BOOL CReqAddFriendDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogSkin::OnEraseBkgnd(pDC);
}

HBRUSH CReqAddFriendDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	/*HBRUSH hbr = CDialogSkin::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;*/

	pDC->SetBkMode(TRANSPARENT); 

	HBRUSH hbr = CDialogSkin::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	int nRet = pWnd->GetDlgCtrlID();

	if(nRet == IDC_STATIC ||
	   nRet == IDC_STATIC_ID)
	{
		CRect rc;

		pDC->SetTextColor(RGB(255, 255, 255));

		hbr = (HBRUSH) GetStockObject(NULL_BRUSH);
		SetBkMode(pDC->m_hDC, TRANSPARENT);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CReqAddFriendDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogSkin::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CReqAddFriendDlg::Init(char* pszMessage)
{
	char id[16];
	char msg[256];
	char buff[256];

	MSG_Seperator(0, pszMessage, id);
	MSG_Seperator(1, pszMessage, buff);

	int i;

	for(i = 0; i < strlen(buff); i++)
	{
		if(buff[i] == 'E' || buff[i] == '0')
			break;

		msg[i] = buff[i];
	}

	msg[i] = NULL;

	for(i = 0; i < strlen(id); i++)
	{
		buff[i] = id[i+1];
	}

	buff[i] = NULL;

	for(i = 0; i <strlen(buff); i++)
	{
		m_szReqID[i] = buff[i];
	}

	GetDlgItem(IDC_STATIC_ID)->SetWindowTextA(buff);
	m_editMessage.SetWindowTextA(msg);
}