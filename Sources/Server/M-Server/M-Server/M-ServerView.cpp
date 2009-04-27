
// M-ServerView.cpp : CMServerView 클래스의 구현
//

#include "stdafx.h"
#include "M-Server.h"

#include "M-ServerDoc.h"
#include "M-ServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMServerView

IMPLEMENT_DYNCREATE(CMServerView, CFormView)

BEGIN_MESSAGE_MAP(CMServerView, CFormView)
	ON_MESSAGE(WM_CLIENT_RECEIVE, OnClientReceive)
	ON_MESSAGE(WM_CLIENT_CONNECT, OnClientConnect)
	ON_MESSAGE(WM_CLIENT_CLOSE, OnClientClose)
	ON_MESSAGE(WM_SERVER_ACCEPT, OnClientAccept)
END_MESSAGE_MAP()

// CMServerView 생성/소멸

CMServerView::CMServerView()
	: CFormView(CMServerView::IDD)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMServerView::~CMServerView()
{
}

void CMServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	Init();
}

void CMServerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMServerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMServerView 진단

#ifdef _DEBUG
void CMServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMServerDoc* CMServerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMServerDoc)));
	return (CMServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMServerView 메시지 처리기

LRESULT CMServerView::OnClientReceive(WPARAM wParam, LPARAM lParam)
{

	return S_OK;
}

LRESULT CMServerView::OnClientConnect(WPARAM wParam, LPARAM lParam)
{

	return S_OK;
}

LRESULT CMServerView::OnClientClose(WPARAM wParam, LPARAM lParam)
{

	return S_OK;
}

LRESULT CMServerView::OnClientAccept(WPARAM wParam, LPARAM lParam)
{

	return S_OK;
}

LRESULT CMServerView::OnClientNetDown(WPARAM wParam, LPARAM lParam)
{

	return S_OK;
}

void CMServerView::Init()
{
	g_sToolMgr.InitToolMgr(m_hWnd);
}