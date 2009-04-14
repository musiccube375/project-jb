// JoinDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatC.h"
#include "JoinDlg.h"
#include ".\joindlg.h"


// CJoinDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CJoinDlg, CDialog)
CJoinDlg::CJoinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJoinDlg::IDD, pParent)
	, pass(_T(""))
	, id(_T(""))
	, name(_T(""))
	, serverip(_T(""))
{
	CFile file;
	if(file.Open(_T("serverip.conf"), CFile::modeRead))
	{
		CArchive ar(&file, CArchive::load);
		ar >> serverip;
		ar.Close();
	}
	else
	{
		serverip = "127.0.0.1";
	}
}

CJoinDlg::~CJoinDlg()
{
}

void CJoinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, 1006, pass);
	DDX_Text(pDX, 1005, id);
	DDX_Text(pDX, 1007, name);
	DDX_Text(pDX, IDC_EDIT1, serverip);
}


BEGIN_MESSAGE_MAP(CJoinDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CJoinDlg 메시지 처리기입니다.

void CJoinDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if(id.IsEmpty() || pass.IsEmpty() || name.IsEmpty())
	{
		AfxMessageBox(_T("필요한 정보를 입력하지 않았습니다."));
	}
	else if(strlen(id)>20 || strlen(id)<3){
		AfxMessageBox(_T("아이디는 3자 이상, 20자 이하로 입력해주십시오."));
	}
	else if(strlen(pass)>20 || strlen(pass)<3){
		AfxMessageBox(_T("비밀번호는 3자 이상, 20자 이하로 입력해주십시오."));
	}
	else if(strlen(name)>100){
		AfxMessageBox(_T("대화명은 100자 이하로 입력해주십시오."));
	}
	else{
		CDialog::OnOK();
	}
}
