#pragma once
#include "afxwin.h"


// CAccountDlg 대화 상자입니다.

class CAccountDlg : public CDialogSkin
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAccountDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_ACCOUNT };

	HICON m_hIcon;

	bool m_bActived;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	CEdit m_editUserID;
	CEdit m_editUserPasswords;
	CEdit m_editAccountID;
	CEdit m_editPasswords;
	CEdit m_editPasswords2;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit7();
};
