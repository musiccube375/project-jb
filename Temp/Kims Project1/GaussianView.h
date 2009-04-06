// GaussianView.h : CGaussianView 클래스의 인터페이스
//


#pragma once


class CGaussianView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CGaussianView();
	DECLARE_DYNCREATE(CGaussianView)

// 특성입니다.
public:
	CGaussianDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGaussianView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	BOOL rect_start;

	CRect m_rtMouse;

	void RenderMouseRect(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

public:
	void RectImageCoordinate();	

	CDib m_View_Dib;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSelectsaveSelect();

public:
	LONG left, top;
};

#ifndef _DEBUG  // GaussianView.cpp의 디버그 버전
inline CGaussianDoc* CGaussianView::GetDocument() const
   { return reinterpret_cast<CGaussianDoc*>(m_pDocument); }
#endif

