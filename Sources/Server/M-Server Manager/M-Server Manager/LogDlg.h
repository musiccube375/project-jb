#pragma once
#include "afxcmn.h"
#include "resource.h"
#include "CustomControl.h"

// CLogDlg 대화 상자입니다.

class CLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	bool m_bColor;

	void Init();
	void AddList(int nIndex, char* pszTime, char* pszType, char* pszContext);
	void DelList(int nIndex);
	void ClearList();

public:
	CColorListCtrl m_listctrlLog;
	virtual BOOL OnInitDialog();
};
