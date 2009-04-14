// ChatSDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ChatS.h"
#include "ChatSDlg.h"
#include "AdduserDlg.h"
#include "Data.h"
#include "Mgr.h"
#include "flag.h"
#include ".\chatsdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
int clntNumber=0;
#endif


// CChatSDlg 대화 상자


CChatSDlg::CChatSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatSDlg::IDD, pParent)
	, m_strList2(_T(""))
	, m_strList1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_LBString(pDX, IDC_LIST2, m_strList2);
	DDX_LBString(pDX, IDC_LIST1, m_strList1);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList1);
	DDX_Control(pDX, IDC_LIST2, m_ctrlList2);
}

BEGIN_MESSAGE_MAP(CChatSDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// CChatSDlg 메시지 처리기

BOOL CChatSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, FALSE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, TRUE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 프로그램 실행시. (하나만 실행)
	HANDLE hMutex = CreateMutex(NULL, TRUE, "메신저 서버");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		AfxMessageBox("프로그램이 이미 실행중입니다.", MB_ICONSTOP);
		//return FALSE;
		ExitProcess(1);
	}

	// 리스트박스 초기화
	m_ctrlList2.InsertColumn(0,"아이디",LVCFMT_LEFT,60);
	m_ctrlList2.InsertColumn(1,"대화명",LVCFMT_LEFT,99); 
	m_ctrlList2.InsertColumn(2,"상태",LVCFMT_LEFT,60);
	m_ctrlList2.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 서버소켓 초기화 (현재객체,포트번호)
	m_ServerSocket.Init(this,3666);
	m_ctrlList1.AddString(_T("*** 서버가 실행되었습니다 ***"));

	// 멤버 리스트
	list.Init(this); // 멤버리스트 초기화

	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CChatSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatSDlg::OnBnClickedButton1() // 사용자 추가
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAdduserDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		if(list.Addmember(dlg.m_strId,dlg.m_strPass,dlg.m_strName)){
			// 멤버추가가 됐을 경우 다이얼로그에 표시..
			m_ctrlList2.InsertItem(list.m_Membernum-1, dlg.m_strId);
			m_ctrlList2.SetItemText(list.m_Membernum-1, 1, dlg.m_strName);
			m_ctrlList2.SetItemText(list.m_Membernum-1, 2, "오프라인");
		}
		else
		{
			AfxMessageBox(_T("같은 아이디가 이미 존재합니다."));
		}
	}
}
void CChatSDlg::OnBnClickedButton2() // 사용자 삭제
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	POSITION pos = m_ctrlList2.GetFirstSelectedItemPosition();

	if(!pos)
	{
		AfxMessageBox(_T("삭제할 아이디를 선택해주십시오."));
	}
	else 
	{
		UpdateData(TRUE);
		
		int nSel = m_ctrlList2.GetNextSelectedItem(pos);
		CString id = list.GetMemberID(nSel);

		CString str; str.Format("%s - 정말 삭제하시겠습니까?", id);
		if(AfxMessageBox(str,MB_YESNO) == IDYES){
			if(list.Delmember(id)){
				//삭제가 성공할경우
				//화면에서 삭제
				while(pos = m_ctrlList2.GetFirstSelectedItemPosition()){
					int nSelItem = m_ctrlList2.GetNextSelectedItem(pos);
					m_ctrlList2.DeleteItem(nSelItem);
				}
				
			}
			else
			{
				AfxMessageBox(_T("아이디 삭제 실패"));
			}
		}
	}
}

void CChatSDlg::ShowMember(int i, CString id, CString name)
{
	m_ctrlList2.InsertItem(i, id);
	m_ctrlList2.SetItemText(i, 1, name);
	m_ctrlList2.SetItemText(i, 2, "오프라인");
}

void CChatSDlg::OnAccept()
{
	// 데이터소켓 생성
	m_pDataSocket = new CDataSocket(this);

	// 서버소켓과 데이터소켓을 연결시켜 줌
	if(!m_ServerSocket.Accept(*m_pDataSocket))
	{
		AfxMessageBox(_T("클라이언트 접속 실패"));
		return;
	}

	// 리스트에 소켓추가..
	m_ListDataSocks.AddTail(m_pDataSocket);

	// 데이터소켓, archive 초기화
	m_pDataSocket->Init(this);

	// 알림
	CString str;
	str.Format("* 새로운 클라이언트가 접속했습니다.");
	m_ctrlList1.AddString(str);
	m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);

	return;
}
void CChatSDlg::OnReceive(CDataSocket *pDataSocket)
{
	// 통신 버퍼에 있는 데이터를 전부 수신할 때까지 반복
	do {
		//데이터 수신
		CData data;
		*pDataSocket >> data;

		CString str;

		//수신된 데이터 처리
		switch(data.m_flag)
		{
		case D_LOGIN:
			//////// 로그인 요청
			str.Format("%s - 서버 접속 성공", data.m_strId);
			m_ctrlList1.AddString(str);
			m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);
			Receive_LOGIN(pDataSocket, &data);
			break;

		case D_MOD_NAME:
			//////// 대화명 변경 요청
			str.Format("%s - 대화명 변경", data.m_strId);
			m_ctrlList1.AddString(str);
			m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);
			Receive_MOD_NAME(pDataSocket, data.m_strId, data.m_strName);
			break;

		case D_JOIN_MEMBER:
			//////// 회원가입 요청
			str.Format("%s - 가입요청", data.m_strId);
			m_ctrlList1.AddString(str);
			m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);
			Receive_JOIN_MEMBER(pDataSocket, data.m_strId, data.m_strPass, data.m_strName);
			break;

		case D_MESSAGE:
			//////// 채팅 메시지를 보낸 경우
			Receive_MESSAGE(pDataSocket, &data);
			break;

		case D_ADD_MYLIST :
			//////// 대화상대 추가를 한 경우
			Receive_ADD_MYLIST(pDataSocket, data.m_strId, data.m_strDestId);
			break;

		case D_DEL_MYLIST:
			//////// 대화상대 삭제를 한 경우
			Receive_DEL_MYLIST(pDataSocket, &data);
			break;

		default : 
			break;
		}
	} while(!(*pDataSocket).m_pArIn -> IsBufferEmpty());
	return;
}

void CChatSDlg::OnDisconnectClient(CDataSocket* pDataSocket){

	// 클라이언트의 연결이 끊겼을 때 처리

	// 데이터소켓 리스트에서 찾기
	POSITION pos;
	pos=m_ListDataSocks.Find(pDataSocket);
	CString id = pDataSocket->m_id;

	if(pDataSocket->m_id != ""){
		// 상태창에 로그아웃 표시
		CString str;
		str.Format("%s - 로그아웃",id);
		m_ctrlList1.AddString(str);
		m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);

		// 리스트에 오프라인 표시
		int nSel = list.ExistMember(id);
		m_ctrlList2.SetItemText(nSel,2,"오프라인");

		// 멤버정보를 오프라인 상태로 변경
		list.SetMemberOnline(id, false, NULL);

		// 접속된 사람들에게 로그아웃 알림
		Send_LOGOUT_MEMBER(id);
	}
	// 데이터소켓 리스트에서 삭제
	m_ListDataSocks.RemoveAt(pos);
}

void CChatSDlg::Receive_LOGIN(CDataSocket * pDataSocket, CData * pData)
{
	//////// 로그인 요청
	CString str;
	bool tf=false;
	int nSel = list.ExistMember(pData->m_strId);
	if (nSel == -1)
	{
		// 아이디가 존재하지 않을 경우 (접속취소)
		CString str;
		str.Format("%s - 로그인 실패(존재하지 않는 아이디)", pData->m_strId);
		m_ctrlList1.AddString(str);
		m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);
		// 실패메시지 세팅
		(*pData).Setdata(D_LOGIN_RESULT,false);
	}
	else {
		// 아이디가 존재할 경우
		//비번 검사
		if(list.CheckPass(pData->m_strId, pData->m_strPass))
		{
			if(list.GetMemberOnline(pData->m_strId) == false)
			{
				str.Format("%s - 로그인 성공", pData->m_strId);
				tf=true;
			}
			else
			{
				// 이미 로그인 되어 있는 경우..
				// 먼저 로그인 되어 있는 접속을 해제
				Send_LOGOUT(pData->m_strId);

				str.Format("%s - 중복 로그인, 이전 접속 해제", pData->m_strId);
				tf=true;
			}
		}
		else
		{
			str.Format("%s - 로그인 실패(잘못된 비밀번호)", pData->m_strId);
		}
	}

	///// 결과 처리
	if(tf) // 로그인 성공
	{
		// 데이터소켓 리스트에 추가
		pDataSocket->m_id = pData->m_strId;

		// 멤버정보를 온라인 상태로 변경
		list.SetMemberOnline(pData->m_strId, true, pDataSocket);

		// 리스트에 표시
		nSel = list.ExistMember(pData->m_strId);
		m_ctrlList2.SetItemText(nSel,2,"온라인");

		// 성공 결과 세팅
		CString id=pData->m_strId;
		(*pData).Setdata( D_LOGIN_RESULT, true, id, list.GetMemberName(id) );

	}
	else // 로그인 실패
	{
		// 실패 결과 세팅
		(*pData).Setdata(D_LOGIN_RESULT,false);
	}
	m_ctrlList1.AddString(str); // 상태창에 출력
	m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);
	Send_LOGIN_RESULT(pDataSocket, pData); // 결과 전송
}

void CChatSDlg::Send_LOGIN_RESULT(CDataSocket * pDataSocket, CData * pData)
{
	int nSel;
	if(pData->m_result == true)
	{
		nSel = list.ExistMember(pData->m_strId);
		int listnum = list.GetMemberMylistnum(nSel);
		// 대화상대 리스트 데이터 세팅
		pData->m_mylistnum = listnum;
		for(int i=0;i<listnum ; i++)
		{
			pData->m_mylist[i] = list.GetMemberMylist(nSel, i);
		}
	}
	
	// 로그인 결과 전송
	*pDataSocket << *pData;

	// 로그인이 성공했을때 추가 작업
	if(pData->m_result == true)
	{
		// 지금 로그인한 멤버에게, 이미 로그인 되어있는 멤버 알림
		Send_LOGIN_MEMBER_INIT(pDataSocket);

		// 대화상대의 접속자에게 로긴사실을 알림
		Send_LOGIN_MEMBER(pDataSocket, pData->m_strId, list.GetMemberName(nSel));
	}
}

void CChatSDlg::Receive_MESSAGE(CDataSocket * pDataSocket, CData * pData)
{
	//////// 채팅 메시지를 보내려는 경우

	// 대상 아이디가 온라인인지 확인
	if( list.GetMemberOnline(pData->m_strDestId) ) 
	{
		// 온라인일때
		Send_MESSAGE(pData->m_strId, pData->m_strName, pData->m_strData, pData->m_strDestId);
	}
	else
	{
		// 온라인이 아닐때
		Send_MESSAGE_FAIL(pDataSocket);
	}
}

void CChatSDlg::Receive_MOD_NAME(CDataSocket * pDataSocket, CString id, CString name)
{
	// 멤버 찾기
	int nSel = list.ExistMember(id);
	if (nSel != -1)
	{
		// 데이터 변경
		list.ModMemberName(nSel, name);

		// 리스트에 대화명 변경
		m_ctrlList2.SetItemText(nSel,1,name);

		// 변경사실 알림..
		Send_LOGIN_MEMBER(pDataSocket, id, name);
	}
}

void CChatSDlg::Send_MESSAGE(CString id, CString name, CString message, CString destid)
{
	////////// 채팅 메시지 전송!
	CDataSocket * pDataSocket;
	CData data;

	CString str; str.Format("%s : %s",id, message);
	m_ctrlList1.AddString(str);
	m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);
	
	// 대상 멤버의 데이터소켓 구함 -_-;;
	if( (pDataSocket=list.GetMemberSocket(destid)) != NULL)
	{
		data.Setdata(D_MESSAGE, true, id, name, message, destid);
		*pDataSocket << data;
	}
}

void CChatSDlg::Send_MESSAGE_FAIL(CDataSocket * pDataSocket)
{
	CData data;
	data.Setdata(D_MESSAGE_FAIL);
	*pDataSocket << data;
}

void CChatSDlg::Send_LOGIN_MEMBER_INIT(CDataSocket * pDataSocket)
{
	//////// 자신의 대화상대 중, 로긴되어있는 멤버의 데이터소켓 구함 -_-;;
	CDataSocket * p;
	CData data;
	// 로긴되어있는 멤버의 데이터소켓 구함 -_-;;
	for(int i=0;i<list.m_Membernum;i++)
	{
		// 새로 로긴한 사람에게 이미 온라인인 사람들의 리스트를 보냄.
		p=list.GetMemberSocket(i);
		if((p != NULL) && (p!=pDataSocket))
		{
			data.Setdata(D_LOGIN_MEMBER, true, list.GetMemberID(i), list.GetMemberName(i));
			*pDataSocket << data;
		}
	}
}

void CChatSDlg::Send_LOGIN_MEMBER(CDataSocket * pDataSocket, CString id, CString name)
{
	//////// 대화상대의 접속자들에게 로긴사실을 알림
	CDataSocket * p;
	CData data;
	// 로긴되어있는 멤버의 데이터소켓 구함 -_-;;
	for(int i=0;i<list.m_Membernum;i++)
	{
		p=list.GetMemberSocket(i);
		if( (p != NULL) && (p!=pDataSocket) )
		{
			// 이미 온라인인 사람들에게 방금 로그인 한것을 알림.
			data.Setdata(D_LOGIN_MEMBER, true, id, name);
			*p << data;
		}
	}
}

void CChatSDlg::Send_LOGOUT_MEMBER(CString id)
{
	CDataSocket * p;
	CData data;
	// 로긴되어있는 멤버의 데이터소켓 구함 -_-;;
	for(int i=0;i<list.m_Membernum;i++)
	{
		p=list.GetMemberSocket(i);
		if(p != NULL)
		{
			// 이미 온라인인 사람들에게 방금 로그아웃 한것을 알림.
			data.Setdata(D_LOGOUT_MEMBER,true,id);
			*p << data;
		}
	}
}

void CChatSDlg::Send_LOGOUT(CString id)
{
	// 해당 아이디의 연결을 강제로 해제
	CDataSocket * p;
	CData data;
	
	for(int i=0;i<list.m_Membernum;i++)
	{
		if(list.GetMemberID(i) == id)
		{
			// 로그아웃하라는 메시지 전달
			p = list.GetMemberSocket(i);
			data.Setdata(D_LOGOUT,true);
			*p << data;
			break;
		}
	}
}

void CChatSDlg::Receive_ADD_MYLIST(CDataSocket * pDataSocket, CString id, CString destid)
{
	// 멤버 찾기
	int nSel = list.ExistMember(id);
	int nSel2 = list.ExistMember(destid);
	int nSel3 = list.GetMemberMylistExist(nSel, destid);
	CData data;

	CString str;
	str.Format("%s - 대화상대 %s 추가 요청", id, destid);
	m_ctrlList1.AddString(str);
	m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);

	if (nSel != -1 && nSel2 != -1 && nSel3 == -1 && nSel != nSel2)
	{
		str.Format("%s - 대화상대 %s 추가 성공", id, destid);
		m_ctrlList1.AddString(str);
		m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);

		// 데이터 변경
		list.AddMemberMylist(nSel, destid);

		// 대화상대 추가 성공 결과 세팅
		data.Setdata(D_ADD_MYLIST, true, destid);
		*pDataSocket << data;

		// 새로 추가한 대화상대가 로그인 되어있는 경우, 대화상대가 로그인했다고 전송
		if(list.GetMemberOnline(nSel2))
		{
			data.Setdata(D_LOGIN_MEMBER, true, list.GetMemberID(nSel2), list.GetMemberName(nSel2));
			*pDataSocket << data;
		}
	}
	else 
	{
		// 아이디가 존재하지 않는 경우 또는 대화상대를 이미 추가했던 경우.
		// 실패 결과 세팅
		data.Setdata(D_ADD_MYLIST,false);
		*pDataSocket << data;
	}
}

void CChatSDlg::Receive_DEL_MYLIST(CDataSocket * pDataSocket, CData * pData)
{
	// 멤버 찾기
	int nSel = list.ExistMember(pData->m_strId);
	int nSel3 = list.GetMemberMylistExist(nSel, pData->m_strDestId);

	if (nSel != -1 && nSel3 != -1)
	{
		CString str;
		str.Format("%s - 대화상대 %s 삭제", pData->m_strId, pData->m_strDestId);
		m_ctrlList1.AddString(str);
		m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);

		// 데이터 변경
		list.DelMemberMylist(nSel, pData->m_strDestId);
	}
}
void CChatSDlg::Receive_JOIN_MEMBER(CDataSocket * pDataSocket, CString id, CString pass, CString name)
{
	/// 회원가입 요청시..
	CData data;

	if(list.Addmember(id,pass,name)){
		// 멤버추가가 됐을 경우 다이얼로그에 표시..
		m_ctrlList2.InsertItem(list.m_Membernum-1, id);
		m_ctrlList2.SetItemText(list.m_Membernum-1, 1, name);
		m_ctrlList2.SetItemText(list.m_Membernum-1, 2, "오프라인");
		data.Setdata(D_JOIN_RESULT,true,id);

		CString str; str.Format("%s - 회원가입", id);
		m_ctrlList1.AddString(str);
		m_ctrlList1.SetCurSel(m_ctrlList1.GetCount()-1);
	}
	else
	{
		data.Setdata(D_JOIN_RESULT,false,id);
	}
	* pDataSocket << data;
}
