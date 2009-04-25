#pragma once

#include "resource.h"

// CUserDlg 대화 상자입니다.

class CUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUserDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
