// LogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "M-Server Manager.h"
#include "LogDlg.h"


// CLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLogDlg, CDialog)

CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
{

}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrlLog);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CLogDlg 메시지 처리기입니다.

void CLogDlg::Init()
{
	m_listctrlLog.m_bColor = true;

	m_listctrlLog.InsertColumn(0, "Time", LVCFMT_CENTER, 150);
	m_listctrlLog.InsertColumn(1, "Type", LVCFMT_CENTER, 150);
	m_listctrlLog.InsertColumn(2, "Context", LVCFMT_CENTER, 700);
}

void CLogDlg::AddList(int nIndex, char* pszTime, char* pszType, char* pszContext)
{
	m_listctrlLog.SetRedraw(FALSE);

	DelList(nIndex);

	if(nIndex < 0 || nIndex > m_listctrlLog.GetItemCount()) return;

	m_listctrlLog.InsertItem(nIndex, pszTime, 0);

	m_listctrlLog.SetItemText(nIndex, 1, pszType);
	m_listctrlLog.SetItemText(nIndex, 2, pszContext);

	m_listctrlLog.SetRedraw(TRUE);
	m_listctrlLog.Invalidate();
}

void CLogDlg::DelList(int nIndex)
{
	if(nIndex < 0 || nIndex > m_listctrlLog.GetItemCount()) return;

	m_listctrlLog.DeleteItem(nIndex);

	m_listctrlLog.SetRedraw(TRUE);
	m_listctrlLog.Invalidate();
}

void CLogDlg::ClearList()
{
	m_listctrlLog.DeleteAllItems();
}

BOOL CLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CLogDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialog::OnEraseBkgnd(pDC);
}
