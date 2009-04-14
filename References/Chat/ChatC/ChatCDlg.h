// ChatCDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

class CDataSocket;
class CData;
class CChatWinDlg;
class CDataSocket;

// CChatCDlg 대화 상자
class CChatCDlg : public CDialog
{
// 생성
public:
	CChatCDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_CHATC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnConnect();
	afx_msg void OnChangename();
	afx_msg void OnAddmylist();
	afx_msg void OnChatting();
	afx_msg void OnLogout();
	afx_msg void OnJoin();
	afx_msg void OnDelmylist();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	CButton m_ctrlJoin;
	CButton m_ctrlConnect;
	CButton m_ctrlChangename;
	CButton m_ctrlAddmylist;
	CButton m_ctrlDelmylist;
	CEdit m_ctrlEdit1;
	CListCtrl m_ctrlList1;

	CString m_strEdit1;
	CString m_strId;
	CString m_strName;
	CString m_strData;

	int m_mylistnum;


public:
	CDataSocket * m_pDataSocket;
	CChatWinDlg * m_pDlg[100]; // 채팅창 (모달리스)
	CString m_mylist[100];
	bool m_mylistonline[100];

	void OnReceive(CDataSocket * pDataSocket);
	void OnDisconnectClient(CDataSocket * pDataSocket);

	void Send_LOGIN(CString id, CString pass);
	void Send_MOD_NAME(CString name);
	void Send_ADD_MYLIST(CString dest_id);
	void Send_DEL_MYLIST(CString dest_id);
	void Send_MESSAGE(CString dest_id, CString message);

	void Receive_LOGIN_RESULT(CData * pData);
	void Receive_ADD_MYLIST(CString id);
	void Receive_LOGIN_MEMBER(CString id, CString name);
	void Receive_LOGOUT_MEMBER(CString id);
	void Receive_MESSAGE(CString id, CString name, CString message);
	void InitLogin(void);
	void InitLogout(void);
	void ChatWinDestroy(CChatWinDlg * p);
	void CreateChatWin(int nSel);
	afx_msg void OnAppAbout();
	void Send_JOIN_MEMBER(CString id, CString pass, CString name, CString serverip);
	afx_msg void OnDestroy();
};
