// TestDlg.h : header file
//

#pragma once

#include "SkinDialog.h"
#include "afxwin.h"

#include "SkinButton.h"

// CTestDlg dialog
class CTestDlg : public CSkinDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CSkinButton m_btnOk;
	CSkinButton m_btnCancel;

// Implementation
protected:
	HICON m_hIcon;

	BOOL m_bInitialized;

	void RelocationControls();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
