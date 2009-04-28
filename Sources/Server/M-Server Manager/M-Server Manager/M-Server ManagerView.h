
// M-Server ManagerView.h : CMServerManagerView 클래스의 인터페이스
//


#pragma once

#include "LogDlg.h"
#include "UserDlg.h"
#include "afxwin.h"

class CMServerManagerView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMServerManagerView();
	DECLARE_DYNCREATE(CMServerManagerView)

public:
	enum{ IDD = IDD_MSERVERMANAGER_FORM };

// 특성입니다.
public:
	CMServerManagerDoc* GetDocument() const;

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
	virtual ~CMServerManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMFCTabCtrl	m_mfcTab;

	void OnTabColor(); 

	afx_msg LONG OnClientReceive(UINT wParam, LONG lParam);
	afx_msg LONG OnClientConnect(UINT wParam, LONG lParam);
	afx_msg LONG OnClientClose(UINT wParam, LONG lParam);
	afx_msg LONG OnClientAccept(UINT wParam, LONG lParam);
	afx_msg LONG OnClientNetDown(UINT wParam, LONG lParam);

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_stcTab;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAccountManage();
	afx_msg void OnButtonAccountManage256();
	afx_msg void OnButtonRun();
	afx_msg void OnButtonStop();
};

#ifndef _DEBUG  // M-Server ManagerView.cpp의 디버그 버전
inline CMServerManagerDoc* CMServerManagerView::GetDocument() const
   { return reinterpret_cast<CMServerManagerDoc*>(m_pDocument); }
#endif

