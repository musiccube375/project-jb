// UserDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "M-Server Manager.h"
#include "UserDlg.h"


// CUserDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUserDlg, CDialog)

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
END_MESSAGE_MAP()


// CUserDlg 메시지 처리기입니다.
