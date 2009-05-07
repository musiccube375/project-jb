#pragma once
#include "afxwin.h"


// CAddFriendDlg dialog

class CAddFriendDlg : public CDialogSkin
{
	DECLARE_DYNAMIC(CAddFriendDlg)

public:
	CAddFriendDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddFriendDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_FRIEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	CEdit m_editFriendID;
	afx_msg void OnBnClickedIDCheck();
	CEdit m_editMessage;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
};
