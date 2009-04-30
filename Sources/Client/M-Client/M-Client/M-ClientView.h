
// M-ClientView.h : CMClientView 클래스의 인터페이스
//


#pragma once
#include "afxwin.h"

#define IDC_ID_AXIS_X 0.258883248730
#define IDC_ID_AXIS_Y 0.051912568306


class CMClientView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMClientView();
	DECLARE_DYNCREATE(CMClientView)

public:
	enum{ IDD = IDD_MCLIENT_FORM };

// 특성입니다.
public:
	CMClientDoc* GetDocument() const;

// 작업입니다.
public:
	CBrush m_Brush;

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg LONG OnClientReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnClientConnect(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnClientClose(WPARAM wParam, LPARAM lParam);

	void CheckMSG(MSG_RET ret);

public:
	void Init();
	HRESULT LoadServerConfig();

public:
	void SetLoginStatus(bool bLogin);

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_editID;
	CEdit m_editPW;
	CButton m_btnRegisterID;
	CButton m_CheckID;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_chkboxRememberID;
	CButton m_chkboxOffline;
	CButton m_btnLogin;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	void RePositionControl(int x, int y);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLogOut();
};

#ifndef _DEBUG  // M-ClientView.cpp의 디버그 버전
inline CMClientDoc* CMClientView::GetDocument() const
   { return reinterpret_cast<CMClientDoc*>(m_pDocument); }
#endif

