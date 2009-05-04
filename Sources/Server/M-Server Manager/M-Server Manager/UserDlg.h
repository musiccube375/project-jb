#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

// CUserDlg 대화 상자입니다.

class CUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUserDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_USER };

public:
	void Init();

	void AddList(char* pszID, char* pszNick, char* pszState);
	void DelList(char* pszID);
	void UpdateList(char* pszID, char* pszNick, char* pszState);
	void ClearList();

	void SetUserCount(int nIndex);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CColorListCtrl m_listctrlUser;
	virtual BOOL OnInitDialog();
	CEdit m_editUserCount;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
