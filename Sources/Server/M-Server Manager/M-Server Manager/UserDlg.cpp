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
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CUserDlg 메시지 처리기입니다.

BOOL CUserDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialog::OnEraseBkgnd(pDC);
}
