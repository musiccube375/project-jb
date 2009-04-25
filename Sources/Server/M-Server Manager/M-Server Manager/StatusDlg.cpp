// StatusDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "M-Server Manager.h"
#include "StatusDlg.h"


// CStatusDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStatusDlg, CDialog)

CStatusDlg::CStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatusDlg::IDD, pParent)
{

}

CStatusDlg::~CStatusDlg()
{
}

void CStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editStatus);
	DDX_Control(pDX, IDC_EDIT2, m_editLoginID);
	DDX_Control(pDX, IDC_EDIT3, m_editLoginTime);
}


BEGIN_MESSAGE_MAP(CStatusDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CStatusDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CStatusDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CStatusDlg::OnEnChangeEdit3)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CStatusDlg 메시지 처리기입니다.

void CStatusDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CStatusDlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CStatusDlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BOOL CStatusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_editStatus.SetWindowTextA("Server is not running...");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CStatusDlg::OnRun(CString strID)
{
	CTime Time;

	Time = CTime::GetCurrentTime();

	CString strTime;

	strTime.Format("%d년 %d월 %d일 - %d시 : %d분 : %d초", Time.GetYear(), Time.GetMonth(), Time.GetDay(), Time.GetHour(), Time.GetMinute(), Time.GetSecond());

	m_editStatus.SetWindowTextA("Server is running...");
	m_editLoginID.SetWindowTextA(strID);
	m_editLoginTime.SetWindowTextA(strTime);

	CString strLog;

	strLog.Format("%s is just loged in...", strID);
	g_sToolMgr.GetLog()->AddLog(LOG_TYPE_TOOLWORK, strLog);
}

HBRUSH CStatusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	int nRet = pWnd->GetDlgCtrlID();

	if(nRet == IDC_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 255));

		hbr = (HBRUSH) GetStockObject(NULL_BRUSH);
		SetBkMode(pDC->m_hDC, TRANSPARENT);
	}
	else if(nRet == IDC_STATIC_SERVER_STATUS)
	{
		SetTextColor(pDC->m_hDC, RGB(0, 128, 255));
		pDC->SetBkColor(RGB(255, 255, 255));
		//SetBkMode(pDC->m_hDC, TRANSPARENT);
		//hbr = (HBRUSH) GetStockObject(WHITE_BRUSH);
	}

	return hbr;
}

BOOL CStatusDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
	GetClientRect(rt);

	pDC->FillSolidRect(rt, RGB(80, 80, 80));
	
	return true;

	//return CDialog::OnEraseBkgnd(pDC);
}
