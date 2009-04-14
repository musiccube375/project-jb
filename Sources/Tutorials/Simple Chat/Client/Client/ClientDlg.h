
// ClientDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ClientSock.h"

#define SERVER_PORT		5555

// CClientDlg 대화 상자
class CClientDlg : public CDialog
{
// 생성입니다.
public:
	CClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CClientDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	CClientSock m_Client;
	bool m_bConnected;

	LRESULT OnClientConnected(WPARAM wParam, LPARAM lParam);
	LRESULT OnClientReceive(WPARAM wParam, LPARAM lParam);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_editIP;
	CListBox m_listboxText;
	CEdit m_editText;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnUpdateEdit2();
	CEdit m_editNickName;
	afx_msg void OnBnClickedButton2();
};
