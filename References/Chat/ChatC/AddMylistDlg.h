#pragma once


// CAddMylistDlg 대화 상자입니다.

class CAddMylistDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddMylistDlg)

public:
	CAddMylistDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddMylistDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADDMYLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strId;
	afx_msg void OnBnClickedOk();
};
