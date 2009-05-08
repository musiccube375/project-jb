
// M-ServerView.h : CMServerView 클래스의 인터페이스
//


#pragma once
#include "afxwin.h"
#include "resource.h"
#include "M-ServerDoc.h"

class CMServerView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMServerView();
	DECLARE_DYNCREATE(CMServerView)

public:
	enum{ IDD = IDD_MSERVER_FORM };

// 특성입니다.
public:
	CMServerDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg LONG OnClientReceive(UINT wParam, LONG lParam);
	afx_msg LONG OnClientConnect(UINT wParam, LONG lParam);
	afx_msg LONG OnClientClose(UINT wParam, LONG lParam);
	afx_msg LONG OnClientAccept(UINT wParam, LONG lParam);
	afx_msg LONG OnClientNetDown(UINT wParam, LONG lParam);

public:
	void Init();
	void InitControls();

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editIP;
	CButton m_btnConnect;
	CButton m_btnDisconnect;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_editUserCount;
};

#ifndef _DEBUG  // M-ServerView.cpp의 디버그 버전
inline CMServerDoc* CMServerView::GetDocument() const
   { return reinterpret_cast<CMServerDoc*>(m_pDocument); }
#endif

