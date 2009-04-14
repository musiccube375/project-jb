#pragma once
#include "afxwin.h"


// CAdduserDlg 대화 상자입니다.

class CAdduserDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdduserDlg)

public:
	CAdduserDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAdduserDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADDUSERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnOK();

public:
	CString m_strId;
	CString m_strPass;
	CString m_strName;
};

