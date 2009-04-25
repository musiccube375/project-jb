#pragma once
#include "afxwin.h"


// CStatusDlg 대화 상자입니다.

class CStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatusDlg)

public:
	CStatusDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStatusDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_STATUS };

	void OnRun(CString strID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editStatus;
	CEdit m_editLoginID;
	CEdit m_editLoginTime;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
