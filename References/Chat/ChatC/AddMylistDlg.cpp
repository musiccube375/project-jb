// AddMylistDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatC.h"
#include "AddMylistDlg.h"
#include ".\addmylistdlg.h"


// CAddMylistDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddMylistDlg, CDialog)
CAddMylistDlg::CAddMylistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddMylistDlg::IDD, pParent)
	, m_strId(_T(""))
{
}

CAddMylistDlg::~CAddMylistDlg()
{
}

void CAddMylistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strId);
}


BEGIN_MESSAGE_MAP(CAddMylistDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CAddMylistDlg 메시지 처리기입니다.

void CAddMylistDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if(strlen(m_strId) < 3)
	{
		AfxMessageBox(_T("필요한 정보를 입력하지 않았습니다."));
		return;
	}
	OnOK();
}
