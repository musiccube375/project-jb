// ChatWinDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatC.h"
#include "ChatWinDlg.h"
#include "ChatCDlg.h"
#include "DataSocket.h"
#include ".\chatwindlg.h"


// CChatWinDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChatWinDlg, CDialog)
CChatWinDlg::CChatWinDlg(CChatCDlg* pParent /*=NULL*/)
	: CDialog(CChatWinDlg::IDD, pParent)
	, m_strDestid(_T(""))
	, m_strData(_T(""))
	, m_strEdit(_T(""))
{
}

CChatWinDlg::~CChatWinDlg()
{
}

void CChatWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEdit);
	DDX_Control(pDX, IDC_EDIT2, m_ctrlEdit2);
	DDX_Control(pDX, ID_CHATDATA, m_ctrlData);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
	DDX_Text(pDX, IDC_EDIT2, m_strEdit2);
}


BEGIN_MESSAGE_MAP(CChatWinDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_SEND, OnSend)
END_MESSAGE_MAP()


// CChatWinDlg 메시지 처리기입니다.

void CChatWinDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 모달리스 대화상자 닫기
	DestroyWindow();
}

void CChatWinDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 동적으로 할당 받은 메모리 해제

	((CChatCDlg *)AfxGetMainWnd()) -> ChatWinDestroy(this);
	delete this;

	CDialog::PostNcDestroy();
}


void CChatWinDlg::OnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	// 입력 내용이 있는지 확인
	if(m_strEdit == "") return;

	// 서버에 메시지 전송
	((CChatCDlg *)AfxGetMainWnd()) -> Send_MESSAGE(m_strDestid, m_strEdit);

	// 자신의 창에 표시
	ViewMessage(m_strName, m_strEdit);

	// 에디트박스초기화
	m_strEdit = "";
	UpdateData(FALSE);

	// 에디트박스로 포커스
	m_ctrlEdit.SetFocus();
}

void CChatWinDlg::ViewMessage(CString name, CString message)
{
	// 위치를 맨 아래로.
	int n = m_ctrlData.GetWindowTextLength();
	m_ctrlData.SetSel(n,n);

	// 출력
	CString str; str.Format("　* %s ..님의 말 :", name); 
	m_ctrlData.ReplaceSel(str);
	m_ctrlData.ReplaceSel("\r\n"); // 개행
	m_ctrlData.ReplaceSel(message);
	m_ctrlData.ReplaceSel("\r\n"); // 개행
	UpdateData(FALSE);

	// 위치를 맨 아래로.
	n = m_ctrlData.GetWindowTextLength();
	m_ctrlData.SetSel(n,n);
}
