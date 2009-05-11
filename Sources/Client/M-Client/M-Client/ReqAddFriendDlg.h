#pragma once
#include "afxwin.h"


// CReqAddFriendDlg dialog

class CReqAddFriendDlg : public CDialogSkin
{
	DECLARE_DYNAMIC(CReqAddFriendDlg)

public:
	CReqAddFriendDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReqAddFriendDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_REQ_ADD_FRIEND };

	int m_nIndex;

	void Init(char* pszMessage);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;

	int m_nDialogIndex;
	char m_szReqID[16];

public:
	CEdit m_editMessage;
	CButton m_btnAccept;
	CButton m_btnDeny;
	CButton m_btnLater;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLater();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEdit2();
};
