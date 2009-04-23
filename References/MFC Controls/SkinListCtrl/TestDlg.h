// TestDlg.h : header file
//

#pragma once

#include "SkinDialog.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "SkinButton.h"

#include "XListCtrl.h"

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

	CImageList *m_pImageList;

	CSkinButton m_btnOk;
	CSkinButton m_btnCancel;

	CXListCtrl m_list;

// Implementation
protected:
	HICON m_hIcon;

	BOOL m_bInitialized;

	void InitList(CXListCtrl &list, const TCHAR **pszTitle);
	void ResizeListColumn(CXListCtrl &list, const int *arrWidth);

	void RelocationControls();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};
