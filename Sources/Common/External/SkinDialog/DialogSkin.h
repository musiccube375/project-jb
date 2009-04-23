#pragma once

#include "memdc.h"

// CDialogSkin dialog

class CDialogSkin : public CDialog
{
	DECLARE_DYNAMIC(CDialogSkin)

public:
	CDialogSkin(CWnd* pParent = NULL);   // standard constructor
	CDialogSkin(UINT uResourceID, CWnd* pParent);
	virtual ~CDialogSkin();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	CRect m_rtTop; //타이틀 렉트
	CRect m_rtLeft; //왼쪽 보더 렉트
	CRect m_rtRight; //오른쪽 보더 렉트
	CRect m_rtBottom; //하단 보더 렉트

	CBitmap m_frmLeftOfTitle, m_frmCenterOfTitle, m_frmRightOfTitle; //타이틀에 쓰일 비트맵 이미지
	BITMAP m_bmLeftOfTitle, m_bmCenterOfTitle, m_bmRightOfTitle; //타이틀에 쓰일 비트맵 이미지 정보

	CBitmap m_frmLeftBorder, m_frmRightBorder; //왼쪽 오른쪽 보더에 쓰일 비트맵 이미지
	CBitmap m_frmLeftOfBottom, m_frmCenterOfBottom, m_frmRightOfBottom;
	CBitmap frmGrayLeft, frmGrayCen, frmGrayRight;
	CBitmap m_frmGrayLeftBorder, m_frmGrayRightBorder;
	CBitmap frmGrayBottomLeft, frmGrayBottomCen, frmGrayBottomRight;

	//각 시스템 버튼 비트맵이미지
	CBitmap m_btnNormal[4];   //0 : Min  1 : Max  2 : Close  3 : Max In Maximize
	CBitmap m_btnActive[4];  //0 : Min  1 : Max  2 : Close  3 : Max In Maximize
	CBitmap m_btnOver[4];    //0 : Min  1 : Max  2 : Close  3 : Max In Maximize
	CBitmap m_btnDisable[4]; //0 : Min  1 : Max  2 : Close  3 : Max In Maximize
	
	//각 시스템 버튼 비트맵 정보
	BITMAP bmClose, bmMin, bmMax;
	//각 시스템 버튼 영역정보
	HRGN m_hRgnClose, m_hRgnMin, m_hRgnMax;

	LONG m_WindowStyle; //윈도우의 스타일은? (시스템버튼 크기등등)

	BOOL m_IsUseXPTheme; //엑스피 테마를 쓰는가

	int m_nBorderThickness;
	int m_nCaptionThickness;

public:
	bool m_bActive; //윈도우가 액티브상태인가.

	int m_x, m_y;
	unsigned short m_nNcButtonOver; //어떤 시스템버튼위에 마우스가 올라가있는가
	unsigned short m_bBtnActive; //어떤시스템 버튼이 눌렸는가 None  : 0  Min   : 1  Max   : 2   Close : 3

	CString m_szWindowText;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnPaint();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void SetLoadImage(void);
	void DrawMinMaxCloseButton(CMemDCEx *pMemDC);

protected:
	int GetThemeType(void);
};
