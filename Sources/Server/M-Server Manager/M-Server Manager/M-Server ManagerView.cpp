
// M-Server ManagerView.cpp : CMServerManagerView 클래스의 구현
//

#include "stdafx.h"
#include "M-Server Manager.h"

#include "M-Server ManagerDoc.h"
#include "M-Server ManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMServerManagerView

IMPLEMENT_DYNCREATE(CMServerManagerView, CFormView)

BEGIN_MESSAGE_MAP(CMServerManagerView, CFormView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CMServerManagerView 생성/소멸

CMServerManagerView::CMServerManagerView()
	: CFormView(CMServerManagerView::IDD)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMServerManagerView::~CMServerManagerView()
{
}

void CMServerManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMServerManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMServerManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CRect rcClient;
	GetClientRect(&rcClient);
	GetParentFrame()->RecalcLayout();
	// 스크롤 크기를 뷰의 크기로 맞추어 줌.
	SetScaleToFitSize(rcClient.Size());

	m_Brush.CreateSolidBrush(RGB(64, 64, 64)); 
}

void CMServerManagerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMServerManagerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMServerManagerView 진단

#ifdef _DEBUG
void CMServerManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMServerManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMServerManagerDoc* CMServerManagerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMServerManagerDoc)));
	return (CMServerManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMServerManagerView 메시지 처리기

HBRUSH CMServerManagerView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	//return hbr;
	return m_Brush;
}
