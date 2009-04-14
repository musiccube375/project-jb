// ChangeNameDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatC.h"
#include "ChangeNameDlg.h"


// CChangeNameDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChangeNameDlg, CDialog)
CChangeNameDlg::CChangeNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeNameDlg::IDD, pParent)
	, m_strName(_T(""))
{
}

CChangeNameDlg::~CChangeNameDlg()
{
}

void CChangeNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
}


BEGIN_MESSAGE_MAP(CChangeNameDlg, CDialog)
END_MESSAGE_MAP()


// CChangeNameDlg 메시지 처리기입니다.
