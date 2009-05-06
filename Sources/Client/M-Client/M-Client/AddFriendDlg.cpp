// AddFriendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "M-Client.h"
#include "AddFriendDlg.h"


// CAddFriendDlg dialog

IMPLEMENT_DYNAMIC(CAddFriendDlg, CDialogSkin)

CAddFriendDlg::CAddFriendDlg(CWnd* pParent /*=NULL*/)
	: CDialogSkin(CAddFriendDlg::IDD, pParent)
{

}

CAddFriendDlg::~CAddFriendDlg()
{
}

void CAddFriendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSkin::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editFriendID);
}


BEGIN_MESSAGE_MAP(CAddFriendDlg, CDialogSkin)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CAddFriendDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddFriendDlg::OnBnClickedIDCheck)
END_MESSAGE_MAP()


// CAddFriendDlg message handlers

BOOL CAddFriendDlg::OnInitDialog()
{
	CDialogSkin::OnInitDialog();

	// TODO:  Add extra initialization here

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAddFriendDlg::OnPaint()
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

BOOL CAddFriendDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogSkin::OnEraseBkgnd(pDC);
}

HBRUSH CAddFriendDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CAddFriendDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CString strID;

	m_editFriendID.GetWindowTextA(strID);

	MSG_Add_Friend_Req(g_sToolMgr.GetLoginID(), strID);
}

void CAddFriendDlg::OnBnClickedIDCheck()
{
	// TODO: Add your control notification handler code here
}
