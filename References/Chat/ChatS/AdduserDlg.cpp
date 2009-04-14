// AdduserDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatS.h"
#include "AdduserDlg.h"


// CAdduserDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAdduserDlg, CDialog)
CAdduserDlg::CAdduserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdduserDlg::IDD, pParent)
	, m_strId(_T(""))
	, m_strPass(_T(""))
	, m_strName(_T(""))
{
}

CAdduserDlg::~CAdduserDlg()
{
}

void CAdduserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strId);
	DDX_Text(pDX, IDC_EDIT2, m_strPass);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
}


BEGIN_MESSAGE_MAP(CAdduserDlg, CDialog)
END_MESSAGE_MAP()


// CAdduserDlg 메시지 처리기입니다.

void CAdduserDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	UpdateData(TRUE);

	if(m_strId.IsEmpty() || m_strPass.IsEmpty() || m_strName.IsEmpty())
	{
		AfxMessageBox(_T("필요한 정보를 입력하지 않았습니다."));
	}
	else if(strlen(m_strId)>20 || strlen(m_strId)<3){
		AfxMessageBox(_T("아이디는 3자 이상, 20자 이하로 입력해주십시오."));
	}
	else if(strlen(m_strPass)>20 || strlen(m_strPass)<3){
		AfxMessageBox(_T("비밀번호는 3자 이상, 20자 이하로 입력해주십시오."));
	}
	else if(strlen(m_strName)>100){
		AfxMessageBox(_T("대화명은 100자 이하로 입력해주십시오."));
	}
	else{
		CDialog::OnOK();
	}
}