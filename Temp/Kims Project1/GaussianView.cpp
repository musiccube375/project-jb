// GaussianView.cpp : CGaussianView 클래스의 구현
//

#include "stdafx.h"
#include "Gaussian.h"
#include "Dib.h"

#include "GaussianDoc.h"
#include "GaussianView.h"

#include "RGBBYTE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGaussianView

IMPLEMENT_DYNCREATE(CGaussianView, CScrollView)

BEGIN_MESSAGE_MAP(CGaussianView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_SELECTSAVE_SELECT, &CGaussianView::OnSelectsaveSelect)
END_MESSAGE_MAP()

// CGaussianView 생성/소멸

CGaussianView::CGaussianView()
:	rect_start(TRUE)
,	m_rtMouse(0)
,	left(0)
,	top(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGaussianView::~CGaussianView()
{
}

BOOL CGaussianView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CGaussianView 그리기

void CGaussianView::OnDraw(CDC* pDC)
{
	CGaussianDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if( pDoc->m_Dib.IsValid() )
		pDoc->m_Dib.Draw(pDC->m_hDC);

	RenderMouseRect(pDC);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CGaussianView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	CGaussianDoc* pDoc = GetDocument();
	if( pDoc->m_Dib.IsValid() )
	{
		sizeTotal.cx = pDoc->m_Dib.GetWidth();
		sizeTotal.cy = pDoc->m_Dib.GetHeight();
	}
	else
		sizeTotal.cx = sizeTotal.cy = 50;

	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);
}


// CGaussianView 인쇄

BOOL CGaussianView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGaussianView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGaussianView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGaussianView 진단

#ifdef _DEBUG
void CGaussianView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGaussianView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGaussianDoc* CGaussianView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGaussianDoc)));
	return (CGaussianDoc*)m_pDocument;
}
#endif //_DEBUG


// CGaussianView 메시지 처리기
void CGaussianView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if( nFlags == MK_LBUTTON )
	{
		LONG tx, ty;
		if( point.x > left && point.y > top )
		{
			m_rtMouse.left = left;
			m_rtMouse.top = top;
			m_rtMouse.right = point.x;
			m_rtMouse.bottom = point.y;
		}
		else if(left > point.x && point.y > top )
		{
			m_rtMouse.left = point.x;
			m_rtMouse.right = left;
			m_rtMouse.top = top;
			m_rtMouse.bottom = point.y;
		}
		else if( left > point.x && top > point.y )
		{
			m_rtMouse.left = point.x;
			m_rtMouse.right = left;
			m_rtMouse.top = point.y;
			m_rtMouse.bottom = top;
		}
		else
		{
			m_rtMouse.left = left;
			m_rtMouse.right = point.x;
			m_rtMouse.top = point.y;
			m_rtMouse.bottom = top;

		}

		InvalidateRect(NULL, false);
	}	

	CScrollView::OnMouseMove(nFlags, point);
}

void CGaussianView::RenderMouseRect(CDC* pDC)
{ 
	pDC->MoveTo(m_rtMouse.left, m_rtMouse.top);
	pDC->LineTo(m_rtMouse.right, m_rtMouse.top);
	pDC->LineTo(m_rtMouse.right, m_rtMouse.bottom);
	pDC->LineTo(m_rtMouse.left, m_rtMouse.bottom);
	pDC->LineTo(m_rtMouse.left, m_rtMouse.top);
}

void CGaussianView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	left = point.x;
	top = point.y;

	CScrollView::OnLButtonDown(nFlags, point);
}

void CGaussianView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_rtMouse = 0;
	Invalidate(FALSE);

	CScrollView::OnRButtonDown(nFlags, point);
}

void CGaussianView::RectImageCoordinate()
{
	if( m_rtMouse == 0 )
	{
		AfxMessageBox(_T("저장하고 싶은 사각 공간을 선택하십시오."));
		return;
	}

	CGaussianDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	register int i, j;
	int w = m_rtMouse.Width();
	int h = m_rtMouse.Height();

	CDib dib2;
	dib2 = pDoc->m_Dib;
	if( dib2.GetBitCount() == 8 )
	{
		m_View_Dib.CreateGrayImage(w, h);

		BYTE** ptr1 = m_View_Dib.GetPtr();
		BYTE** ptr2 = dib2.GetPtr();

		for( j = 0; j < h; j++ )
		for( i = 0; i < w; i++ )
		{
			ptr1[j][i] = ptr2[m_rtMouse.top+j][m_rtMouse.left+i];
		}
	}
	else if( dib2.GetBitCount() == 24 )
	{
		m_View_Dib.CreateRGBImage(w, h);

		RGBBYTE** ptr1 = m_View_Dib.GetRGBPtr();
		RGBBYTE** ptr2 = dib2.GetRGBPtr();

		for( j = 0; j < h; j++ )
		for( i = 0; i < w; i++ )
		{
			ptr1[j][i].r = ptr2[m_rtMouse.top+j][m_rtMouse.left+i].r;
			ptr1[j][i].g = ptr2[m_rtMouse.top+j][m_rtMouse.left+i].g;
			ptr1[j][i].b = ptr2[m_rtMouse.top+j][m_rtMouse.left+i].b;
		}
	}
}
BOOL CGaussianView::OnEraseBkgnd(CDC* pDC)
{
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	FillOutsideRect(pDC, &br);

	return TRUE;
}

void CGaussianView::OnSelectsaveSelect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	RectImageCoordinate();

	CGaussianDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	AfxNewImage(m_View_Dib);

	CDib dib = pDoc->m_Dib;
	pDoc->m_Dib = m_View_Dib;

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_SAVE_AS);

	pDoc->m_Dib = dib;

}
