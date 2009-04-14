// ChatCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ChatC.h"
#include "ChatCDlg.h"
#include "Connectdlg.h"
#include "Data.h"
#include "flag.h"
#include "ChangeNameDlg.h"
#include "AddMylistDlg.h"
#include "joindlg.h"
#include "ChatWinDlg.h"
#include "AboutDlg.h"
#include ".\chatcdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatCDlg 대화 상자



CChatCDlg::CChatCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatCDlg::IDD, pParent)
	, m_strEdit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_CHANGENAME, m_ctrlChangename);
	DDX_Control(pDX, ID_CONNECT, m_ctrlConnect);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList1);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEdit1);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	DDX_Control(pDX, ID_ADDMYLIST, m_ctrlAddmylist);
	DDX_Control(pDX, ID_JOIN, m_ctrlJoin);
	DDX_Control(pDX, ID_DELMYLIST, m_ctrlDelmylist);
}

BEGIN_MESSAGE_MAP(CChatCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_CONNECT, OnConnect)
	ON_BN_CLICKED(ID_CHANGENAME, OnChangename)
	ON_BN_CLICKED(ID_ADDMYLIST, OnAddmylist)
	ON_BN_CLICKED(ID_JOIN, OnJoin)
	ON_BN_CLICKED(ID_LOGOUT, OnLogout)
	ON_BN_CLICKED(ID_DELMYLIST, OnDelmylist)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CChatCDlg 메시지 처리기

BOOL CChatCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, FALSE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, TRUE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitLogout();

	m_ctrlList1.InsertColumn(0,_T("아이디"),LVCFMT_LEFT,60);
	m_ctrlList1.InsertColumn(1,_T("대화명"),LVCFMT_LEFT,99);
	m_ctrlList1.InsertColumn(2,_T("상태"),LVCFMT_LEFT,60);
	m_ctrlList1.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_pDataSocket = new CDataSocket(this);

	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatCDlg::OnPaint() 
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
HCURSOR CChatCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatCDlg::OnConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 접속 ip 아이디 비번을 입력하는 대화상자
	CConnectDlg dlg;
	if(dlg.DoModal() != IDOK) return;

	// 클라이언트 소켓 생성
	if(!m_pDataSocket->Create())
	{
		AfxMessageBox(_T("클라이언트 소켓 생성 실패"));
		return;
	}

	// 서버에 접속 요청
	if(!m_pDataSocket->Connect(dlg.m_strServerIP, 3666)) // 서버아이피와 포트번호
	{
		AfxMessageBox(_T("서버를 찾을 수 없습니다."));
		m_pDataSocket->Close();
		return;
	}

	// 클라이언트 소켓 초기화
	m_pDataSocket->Init(this);

	// ID와 비밀번호 확인
	Send_LOGIN(dlg.m_strId,dlg.m_strPass);
}

void CChatCDlg::OnChangename()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CChangeNameDlg dlg;

	if(dlg.DoModal() != IDOK) return;

	// 화면에 대화명 변경
	m_strName = dlg.m_strName;
	CString str; str.Format(_T("%s - %s"), m_strId, m_strName);
	m_strEdit1 = str;
	UpdateData(FALSE);

	// 서버에도 전송
	Send_MOD_NAME(dlg.m_strName);
}

void CChatCDlg::OnAddmylist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAddMylistDlg dlg;

	if(dlg.DoModal() != IDOK) return;

	// 리스트 추가 서버에 전송
	if(m_mylistnum < 100)
	{
		Send_ADD_MYLIST(dlg.m_strId);
	}
	else
	{
		AfxMessageBox(_T("대화상대 목록이 꽉 차서 더 이상 추가할 수 없습니다."));
	}
}

void CChatCDlg::OnReceive(CDataSocket *pDataSocket)
{
	// 통신 버퍼에 있는 데이터를 전부 수신할 때까지 반복
	do {
		CString str;
		CData data;
		*pDataSocket >> data; //데이터 수신

		//수신된 데이터 표시
		///////////////////////////
		switch(data.m_flag){
		case D_LOGIN_RESULT :
			///////// 로그인 요청 결과
			Receive_LOGIN_RESULT(&data);
			break;

		case D_LOGIN_MEMBER :
			///////// 대화상대 로그인 알림
			Receive_LOGIN_MEMBER(data.m_strId, data.m_strName);
			break;

		case D_LOGOUT_MEMBER :
			///////// 대화상대 로그아웃 알림
			Receive_LOGOUT_MEMBER(data.m_strId);
			break;

		case D_MOD_NAME :
			///////// 대화상대 대화명 변경
			Receive_LOGIN_MEMBER(data.m_strId, data.m_strName);
			break;

		case D_MESSAGE :
			///////// 대화 메시지 수신
			Receive_MESSAGE(data.m_strId, data.m_strName, data.m_strData);
			break;

		case D_ADD_MYLIST :
			if(data.m_result){
				// 대화상대추가에 성공했을 경우..
				Receive_ADD_MYLIST(data.m_strId);}
			else { AfxMessageBox(_T("대화상대 추가를 하지 못했습니다")); }
			break;

		case D_LOGOUT :
			///////// 강제 로그아웃
			str.Format(_T("다른 곳에서 로그인 하였으므로 로그아웃 됩니다."));
			AfxMessageBox(str);
			OnDisconnectClient(pDataSocket);
			break;

		case D_JOIN_RESULT :
			///////// 회원 가입 요청 결과
			if(data.m_result)
			{
				str.Format(_T("%s : 회원 가입에 성공했습니다."),data.m_strId);
				AfxMessageBox(str);
			}
			else
			{
				str.Format(_T("%s : 회원 가입에 실패했습니다.\n이미 존재하는 아이디입니다."),data.m_strId);
				AfxMessageBox(str);
			}

			break;

		case D_MESSAGE_FAIL :
			AfxMessageBox(_T("메시지 전송 실패"));
			break;

		default :
			AfxMessageBox(_T("알 수 없는 데이터를 수신했습니다."));
			break;
		}
	} while(!(*pDataSocket).m_pArIn->IsBufferEmpty());
}

void CChatCDlg::OnDisconnectClient(CDataSocket* pDataSocket)
{
	m_pDataSocket->Close();

	InitLogout();
}

void CChatCDlg::Send_LOGIN(CString id, CString pass)
{
	CData data;
	data.SetLogindata(D_LOGIN, id, pass);

	*m_pDataSocket << data;
}

void CChatCDlg::Receive_LOGIN_RESULT(CData * pData)
{
	if(pData->m_result) 
	{
		// 로그인 성공

		for(int i=0;i<100;i++)
		{
			m_pDlg[i] = NULL;
			m_mylistonline[i]=false;
		}

		// 버튼,목록 활성화
		InitLogin();

		// 자기 아이디, 이름 저장
		m_strId = pData->m_strId;
		m_strName = pData->m_strName;

		// 화면에 자기 대화명 표시
		CString str; str.Format(_T("%s - %s"), m_strId, m_strName);
		m_strEdit1 = str;
		UpdateData(FALSE);

		// 등록 멤버 리스트 보이기
		m_mylistnum = pData->m_mylistnum;
		for(int i=0;i<m_mylistnum;i++){
			m_mylist[i] = pData->m_mylist[i]; // 리스트에 저장..
			m_ctrlList1.InsertItem(i, pData->m_mylist[i]);
			m_ctrlList1.SetItemText(i, 1, "");
			m_ctrlList1.SetItemText(i, 2, _T("오프라인"));
		}
	}
	else
	{
		// 로그인 실패
		AfxMessageBox(_T("로그인 실패"));
		m_pDataSocket->Close();
	}
}

void CChatCDlg::Receive_MESSAGE(CString id, CString name, CString message)
{
	// 인덱스 구함
	int nSel=-1;
	for(int i=0;i<m_mylistnum;i++)
	{
		if(m_mylist[i] == id)
		{
			nSel = i;
			break;
		}
	}

	//////// 상대방이 내 리스트에 없을 경우
	if(nSel==-1)
	{
		CString str;
		// 대화상대가 꽉 찼을 경우는 대화상대 등록을 묻지 않고 그냥 보여준다..
		if(m_mylistnum>=100)
		{
			str.Format(_T("%s ...님의 말:\n%s"),id,message);
			AfxMessageBox(str);
			return;
		}

		str.Format(_T("%s 로부터 메시지를 수신했습니다.\n대화 상대로 등록하시겠습니까?"), id);
		if(AfxMessageBox(str,MB_YESNO) != IDYES)
		{
			// 대화상대로 등록하지 않았을 경우.. 메시지를 단순히 보여준다.
			str.Format(_T("%s ...님의 말:\n%s"),id,message);
			AfxMessageBox(str);
			return;
		}

		/// 서버에 대화상대 추가 저장..
		Send_ADD_MYLIST(id);

		// 임시로 대화창 세팅;
		nSel = m_mylistnum;
		m_mylist[nSel] = id;
		m_mylistonline[nSel] = true;
		m_pDlg[nSel] = NULL;
	}

	/////// 창 만듬..
	CreateChatWin(nSel);

	// 화면에 메시지 뿌림..
	m_pDlg[nSel]->ViewMessage(name,message);

	// 포커스
	m_pDlg[nSel]->SetFocus();
}

void CChatCDlg::Send_MESSAGE(CString dest_id, CString message)
{
	CData data;
	data.Setdata(D_MESSAGE, true, m_strId, m_strName, message, dest_id);
	*m_pDataSocket << data;
}

void CChatCDlg::Send_MOD_NAME(CString name)
{
	CData data;
	data.Setdata(D_MOD_NAME , true , m_strId, name);
	*m_pDataSocket << data;
}


void CChatCDlg::Send_ADD_MYLIST(CString dest_id)
{
	CData data;
	data.Setdata(D_ADD_MYLIST, true, m_strId, "" , "" , dest_id);
	*m_pDataSocket << data;
}

void CChatCDlg::Send_DEL_MYLIST(CString dest_id)
{
	CData data;
	data.Setdata(D_DEL_MYLIST, true, m_strId, "" , "" , dest_id);
	*m_pDataSocket << data;
}

void CChatCDlg::Receive_ADD_MYLIST(CString id)
{
	// 회원추가에 성공했을 경우..

	// 리스트에 추가
	m_mylist[m_mylistnum] = id;

	// 화면에 표시
	m_ctrlList1.InsertItem(m_mylistnum, id);
	m_ctrlList1.SetItemText(m_mylistnum, 1, "");
	m_ctrlList1.SetItemText(m_mylistnum, 2, _T("오프라인"));

	m_mylistnum++; // 인덱스 증가..
}

void CChatCDlg::OnChatting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CChatCDlg::Receive_LOGIN_MEMBER(CString id, CString name)
{
	int nSel=0;
	// 인덱스 찾기
	
	for(int i=0;i<m_mylistnum;i++){
		if(m_mylist[i] == id)
		{
			nSel = i;
			m_mylistonline[nSel]=true;
			// 화면에 표시
			m_ctrlList1.SetItemText(nSel, 1, name);
			m_ctrlList1.SetItemText(nSel, 2, _T("온라인"));
			break;
		}
	}
}

void CChatCDlg::Receive_LOGOUT_MEMBER(CString id)
{
	int nSel=0;
	// 인덱스 찾기
	for(int i=0;i<m_mylistnum;i++){
		if(m_mylist[i] == id)
		{
			nSel=i;
			m_mylistonline[nSel]=false;
			// 화면에 표시
			m_ctrlList1.SetItemText(nSel, 1, "");
			m_ctrlList1.SetItemText(nSel, 2, _T("오프라인"));
			
			// 대화창이 켜져있을 경우 대화창 비활성화
			if(m_pDlg[nSel] != NULL) m_pDlg[nSel]->m_ctrlEdit.EnableWindow(FALSE);
			break;
		}
	}
}

void CChatCDlg::OnLogout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(AfxMessageBox(_T("로그아웃 하시겠습니까?"),MB_YESNO) == IDYES)
	{
		OnDisconnectClient(m_pDataSocket);
	}
}

void CChatCDlg::OnJoin()// 회원가입
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CJoinDlg dlg;

	if(dlg.DoModal() != IDOK) return;

	Send_JOIN_MEMBER(dlg.id, dlg.pass, dlg.name, dlg.serverip);
}

void CChatCDlg::OnDelmylist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	if(!pos)
	{
		AfxMessageBox(_T("삭제할 아이디를 선택해주십시오."));
	}
	else 
	{
		UpdateData(TRUE);
		
		int nSel = m_ctrlList1.GetNextSelectedItem(pos);
		CString id = m_mylist[nSel];

		CString str; str.Format(_T("%s - 정말 삭제하시겠습니까?"), id);
		if(AfxMessageBox(str,MB_YESNO) == IDYES)
		{
			// 삭제작업 (서버)
			Send_DEL_MYLIST(id);

			// 리스트에서 삭제
			for(int i=nSel;i<m_mylistnum-1;i++)
			{
				m_mylist[i] = m_mylist[i+1];
			}
			m_mylistnum--;

			// 화면에서 삭제
			while(pos = m_ctrlList1.GetFirstSelectedItemPosition()){
				int nSelItem = m_ctrlList1.GetNextSelectedItem(pos);
				m_ctrlList1.DeleteItem(nSelItem);
			}
		}
	}
}

void CChatCDlg::InitLogin(void)
{
	//// 로그인 상태일 때의 화면
	// 메뉴 변경
	CMenu *pMenu = GetMenu();
	pMenu->EnableMenuItem(ID_LOGOUT,FALSE);
	pMenu->EnableMenuItem(ID_CHANGENAME,FALSE);
	pMenu->EnableMenuItem(ID_ADDMYLIST,FALSE);
	pMenu->EnableMenuItem(ID_CONNECT,TRUE);
	pMenu->EnableMenuItem(ID_JOIN,TRUE);

	// 버튼,목록 변경
	m_ctrlConnect.ShowWindow(FALSE);
	m_ctrlJoin.ShowWindow(FALSE);
	m_ctrlChangename.ShowWindow(TRUE);
	m_ctrlAddmylist.ShowWindow(TRUE);
	m_ctrlDelmylist.ShowWindow(TRUE);
	m_ctrlList1.ShowWindow(TRUE);
	m_ctrlEdit1.ShowWindow(TRUE);
}

void CChatCDlg::InitLogout()
{
	//// 로그아웃 상태일 때의 화면
	// 메뉴 변경
	CMenu *pMenu = GetMenu();
	pMenu->EnableMenuItem(ID_LOGOUT,TRUE);
	pMenu->EnableMenuItem(ID_CHANGENAME,TRUE);
	pMenu->EnableMenuItem(ID_ADDMYLIST,TRUE);
	pMenu->EnableMenuItem(ID_CONNECT,FALSE);
	pMenu->EnableMenuItem(ID_JOIN,FALSE);
	
	// 목록 지우기
	m_ctrlList1.DeleteAllItems();

	// 버튼,목록 변경
	m_ctrlConnect.ShowWindow(TRUE);
	m_ctrlJoin.ShowWindow(TRUE);
	m_ctrlChangename.ShowWindow(FALSE);
	m_ctrlAddmylist.ShowWindow(FALSE);
	m_ctrlDelmylist.ShowWindow(FALSE);
	m_ctrlList1.ShowWindow(FALSE);
	m_ctrlEdit1.ShowWindow(FALSE);
}

void CChatCDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();
	int nSel = m_ctrlList1.GetNextSelectedItem(pos);

	// 오프라인 대화상대를 클릭하면 아무일도 일어나지 않음.
	if(m_mylistonline[nSel] == false) return;

	// 창 만듬..
	CreateChatWin(nSel);

	*pResult = 0;
}
void CChatCDlg::ChatWinDestroy(CChatWinDlg * p)
{
	for(int i=0;i<100;i++)
	{
		if(p == m_pDlg[i])
		{
			m_pDlg[i] = NULL;
			break;
		}
	}
}
void CChatCDlg::CreateChatWin(int nSel)
{
	if(m_pDlg[nSel] != NULL && m_mylistonline[nSel]==true)
	{
		// 대화상자가 이미 출력되어 있는 경우
		m_pDlg[nSel]->SetFocus();
	}
	else if(m_mylistonline[nSel]==true)
	{
		// 대화상자가 출력되어 있지 않은 경우
		m_pDlg[nSel] = new CChatWinDlg;
		m_pDlg[nSel]->Create(IDD_CHATWIN, this);
		m_pDlg[nSel]->m_nSel = nSel;
		m_pDlg[nSel]->m_strId = m_strId;
		m_pDlg[nSel]->ShowWindow(SW_SHOW);
		m_pDlg[nSel]->m_strName = m_strName; // 내이름
		m_pDlg[nSel]->m_strDestid = m_mylist[nSel]; // 상대방아이디 저장
		m_pDlg[nSel]->m_strEdit2 = m_mylist[nSel]; // 상대방아이디 화면에 표시
		//상대방 아이디 창 제목에 표시
		m_pDlg[nSel]->SetWindowText(m_mylist[nSel]);
	}
	m_pDlg[nSel]->UpdateData(FALSE);
}

void CChatCDlg::OnAppAbout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAboutDlg dlg;
	dlg.DoModal();
}

void CChatCDlg::Send_JOIN_MEMBER(CString id, CString pass, CString name, CString serverip)
{
	CDataSocket sock;
	CData data;

	//////// 임시 서버 접속
	// 클라이언트 소켓 생성
	if(!sock.Create())
	{
		AfxMessageBox(_T("클라이언트 소켓 생성 실패"));
		return;
	}
	// 서버에 접속 요청
	if(!sock.Connect(serverip, 3666)) // 서버아이피와 포트번호
	{
		AfxMessageBox(_T("서버를 찾을 수 없습니다."));
		sock.Close();
		return;
	}
	// 클라이언트 소켓 초기화
	sock.Init(this);

	//////// 데이터 전송
	data.Setdata(D_JOIN_MEMBER, true, id, name, "", "", pass);
	sock << data;

	AfxMessageBox(_T("로그인 해 주세요.."));
	::Sleep(1000);

	// 접속해제
	sock.Close();
}

void CChatCDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	delete m_pDataSocket;
}
