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

}

CRegisterNewUserDlg::~CRegisterNewUserDlg()
{
}

void CRegisterNewUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegisterNewUserDlg, CDialog)
END_MESSAGE_MAP()


// CRegisterNewUserDlg 메시지 처리기입니다.
